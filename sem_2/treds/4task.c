#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX 100

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int turn = 0;

void* synchronized_child(void* arg) {
    char** messages = (char**)arg;

    for (int i = 0; i < 5; ++i) {
        pthread_mutex_lock(&mutex);
        while (turn != 1) {
            pthread_cond_wait(&cond, &mutex);
        }
        printf("%s\n", messages[i]);
        turn = 0;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void synchronized_print() {
    pthread_t child;
    char* child_msgs[] = {"c1", "c2", "c3", "c4", "c5"};

    pthread_create(&child, NULL, synchronized_child, child_msgs);

    for (int i = 0; i < 5; ++i) {
        pthread_mutex_lock(&mutex);
        while (turn != 0) {
            pthread_cond_wait(&cond, &mutex);
        }
        printf("p%d\n", i + 1);
        turn = 1;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
    }

    pthread_join(child, NULL);
}

int N, THREADS;
int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];

void* multiply_rows(void* arg) {
    int thread_id = *(int*)arg;
    int rows_per_thread = N / THREADS;
    int start = thread_id * rows_per_thread;
    int end = (thread_id == THREADS - 1) ? N : start + rows_per_thread;

    for (int i = start; i < end; ++i) {
        for (int j = 0; j < N; ++j) {
            C[i][j] = 0;
            for (int k = 0; k < N; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return NULL;
}

void print_matrix(const char* name, int M[MAX][MAX], int size) {
    printf("%s:\n", name);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            printf("%d ", M[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void multiply_matrix_parallel() {
    pthread_t threads[MAX];
    int ids[MAX];

    for (int i = 0; i < THREADS; ++i) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, multiply_rows, &ids[i]);
    }

    for (int i = 0; i < THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Usage: %s <matrix_size> <num_threads>\n", argv[0]);
        return 1;
    }

    N = atoi(argv[1]);
    THREADS = atoi(argv[2]);

    if (N > MAX || THREADS > N || THREADS <= 0) {
        printf("Invalid matrix size or thread count.\n");
        return 1;
    }

    synchronized_print();

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j) {
            A[i][j] = 1;
            B[i][j] = 1;
        }

    multiply_matrix_parallel();

    if (N <= 5) {
        print_matrix("Matrix A", A, N);
        print_matrix("Matrix B", B, N);
        print_matrix("Matrix C", C, N);
    }

    return 0;
}

