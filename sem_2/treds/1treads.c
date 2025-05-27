#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_SIZE 50

void cleanup_handler(void* arg) {
    printf("Thread was terminated forcefully\n");
    fflush(stdout);
}

void* thread_func(void* arg) {
    char** messages = (char**)arg;

    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);

    pthread_cleanup_push(cleanup_handler, NULL);

    for (int i = 0; i < 5; ++i) {
        printf("%s\n", messages[i]);
        fflush(stdout);
        sleep(1);
    }

    pthread_cleanup_pop(0);
    return NULL;
}

void* sleep_sort_thread(void* arg) {
    int value = *(int*)arg;
    sleep(value);
    printf("%d ", value);
    fflush(stdout);
    free(arg);
    return NULL;
}

void sleep_sort(int* arr, int size) {
    pthread_t threads[MAX_SIZE];
    for (int i = 0; i < size; ++i) {
        int* val = malloc(sizeof(int));
        *val = arr[i];
        pthread_create(&threads[i], NULL, sleep_sort_thread, val);
    }
    for (int i = 0; i < size; ++i) {
        pthread_join(threads[i], NULL);
    }
    printf("\n");
    fflush(stdout);
}

int main() {
    pthread_t threads[4];

    char* msgs1[] = {"A1", "A2", "A3", "A4", "A5"};
    char* msgs2[] = {"B1", "B2", "B3", "B4", "B5"};
    char* msgs3[] = {"C1", "C2", "C3", "C4", "C5"};
    char* msgs4[] = {"D1", "D2", "D3", "D4", "D5"};
    char** all_msgs[] = {msgs1, msgs2, msgs3, msgs4};

    for (int i = 0; i < 4; ++i) {
        pthread_create(&threads[i], NULL, thread_func, all_msgs[i]);
    }

    sleep(2);

    for (int i = 0; i < 4; ++i) {
        pthread_cancel(threads[i]);
    }

    for (int i = 0; i < 4; ++i) {
        printf("Main: cancel sent to thread %d\n", i);
        fflush(stdout);
    }

    for (int i = 0; i < 4; ++i) {
        pthread_join(threads[i], NULL);
    }

    int size;
    int arr[MAX_SIZE];

    printf("\nEnter number of elements for SleepSort (max %d): ", MAX_SIZE);
    fflush(stdout);
    if (scanf("%d", &size) != 1 || size <= 0 || size > MAX_SIZE) {
        fprintf(stderr, "Error: invalid array size.\n");
        return 1;
    }

    printf("Enter %d positive integers (each ≤ 10):\n", size);
    fflush(stdout);
    for (int i = 0; i < size; ++i) {
        if (scanf("%d", &arr[i]) != 1 || arr[i] < 0 || arr[i] > 10) {
            fprintf(stderr, "Error: invalid value %d.\n", arr[i]);
            return 1;
        }
    }

    printf("Sorted output: ");
    fflush(stdout);
    sleep_sort(arr, size);

    return 0;
}

