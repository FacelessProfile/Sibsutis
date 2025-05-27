#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

#define MAX_MSGS 10
#define MAX_LEN  128

typedef struct {
    char    buf[MAX_MSGS][MAX_LEN];
    int     head, tail, count;
    pthread_mutex_t mutex;
    pthread_cond_t  not_full;
    pthread_cond_t  not_empty;
    int     dropped;
} queue_t;

// send up to MAX_LEN chars, block if full
int msgSend(queue_t *q, const char *msg) {
    pthread_mutex_lock(&q->mutex);
    while (q->count == MAX_MSGS && !q->dropped) {
        pthread_cond_wait(&q->not_full, &q->mutex);
    }
    if (q->dropped) {
        pthread_mutex_unlock(&q->mutex);
        return -1;
    }
    // copy truncated message
    int len = strnlen(msg, MAX_LEN - 1);
    memcpy(q->buf[q->tail], msg, len);
    q->buf[q->tail][len] = '\0';
    q->tail = (q->tail + 1) % MAX_MSGS;
    q->count++;
    pthread_cond_signal(&q->not_empty);
    pthread_mutex_unlock(&q->mutex);
    return len;
}

// receive into buf[bufsize], block if empty
int msgRecv(queue_t *q, char *out, size_t bufsize) {
    pthread_mutex_lock(&q->mutex);
    while (q->count == 0 && !q->dropped) {
        pthread_cond_wait(&q->not_empty, &q->mutex);
    }
    if (q->dropped) {
        pthread_mutex_unlock(&q->mutex);
        return -1;
    }
    // take message
    char *src = q->buf[q->head];
    int len = strnlen(src, MAX_LEN);
    int copy_len = (len < (int)bufsize - 1) ? len : (int)bufsize - 1;
    memcpy(out, src, copy_len);
    out[copy_len] = '\0';
    q->head = (q->head + 1) % MAX_MSGS;
    q->count--;
    pthread_cond_signal(&q->not_full);
    pthread_mutex_unlock(&q->mutex);
    return copy_len;
}

// wake up all waiting senders/receivers
void msgDrop(queue_t *q) {
    pthread_mutex_lock(&q->mutex);
    q->dropped = 1;
    pthread_cond_broadcast(&q->not_empty);
    pthread_cond_broadcast(&q->not_full);
    pthread_mutex_unlock(&q->mutex);
}

// client (producer) thread
void *client_thread(void *arg) {
    queue_t *q = arg;
    char msg[MAX_LEN];
    int id = (int)(size_t)pthread_self();
    while (1) {
        usleep((rand() % 500 + 100) * 1000); // 100–600 ms
        snprintf(msg, sizeof(msg), "Client %d says hello at %ld", id, time(NULL));
        int sent = msgSend(q, msg);
        if (sent < 0) break;
        printf("[Client %d] sent %d chars to pentagone\n", id, sent);
    }
    return NULL;
}

// server (consumer) thread
void *server_thread(void *arg) {
    queue_t *q = arg;
    char buf[MAX_LEN];
    int id = (int)(size_t)pthread_self();
    while (1) {
        int rec = msgRecv(q, buf, sizeof(buf));
        if (rec < 0) break;
        printf("[Server %d] %s\n", id, buf);
        int ran=rand() % 5 + 1;
        printf("[Server %d] I will sleep %d seconds\n",id,ran);
        sleep(ran); // 1–2 s
    }
    return NULL;
}

int main() {
    srand(time(NULL));
    queue_t q = {0};
    pthread_mutex_init(&q.mutex, NULL);
    pthread_cond_init(&q.not_full, NULL);
    pthread_cond_init(&q.not_empty, NULL);

    const int N_CLIENTS = 3;
    const int N_SERVERS = 2;
    pthread_t clients[N_CLIENTS], servers[N_SERVERS];

    // start servers
    for (int i = 0; i < N_SERVERS; i++) {
        pthread_create(&servers[i], NULL, server_thread, &q);
    }
    // start clients
    for (int i = 0; i < N_CLIENTS; i++) {
        pthread_create(&clients[i], NULL, client_thread, &q);
    }

    // let them run for 10 seconds
    sleep(10);
    // drop all waiting threads and exit
    msgDrop(&q);

    // join threads
    for (int i = 0; i < N_CLIENTS; i++) {
        pthread_join(clients[i], NULL);
    }
    for (int i = 0; i < N_SERVERS; i++) {
        pthread_join(servers[i], NULL);
    }

    pthread_mutex_destroy(&q.mutex);
    pthread_cond_destroy(&q.not_full);
    pthread_cond_destroy(&q.not_empty);
    return 0;
}

