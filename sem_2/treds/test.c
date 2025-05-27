#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#define MAX_THREADS 128
#define MAX_SIZE 2500

int **A, **B, **C;
int N, threads;
int current_row = 0;
pthread_mutex_t row_mutex;

void* multiply(void* arg) {
    while (1) {
        pthread_mutex_lock(&row_mutex);
        int row = current_row++;
        pthread_mutex_unlock(&row_mutex);

        if (row >= N) break;

        for (int j = 0; j < N; ++j) {
            int sum = 0;
            for (int k = 0; k < N; ++k) {
                sum += A[row][k] * B[k][j];
            }
            C[row][j] = sum;
        }
    }
    return NULL;
}

void allocate_and_fill() {
    A = malloc(N * sizeof(int*));
    B = malloc(N * sizeof(int*));
    C = malloc(N * sizeof(int*));
    for (int i = 0; i < N; ++i) {
        A[i] = malloc(N * sizeof(int));
        B[i] = malloc(N * sizeof(int));
        C[i] = malloc(N * sizeof(int));
        for (int j = 0; j < N; ++j) {
            A[i][j] = 1;
            B[i][j] = 1;
        }
    }
}

void free_matrices() {
    for (int i = 0; i < N; ++i) {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);
    free(B);
    free(C);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s <matrix_size> <threads>\n", argv[0]);
        return 1;
    }

    N = atoi(argv[1]);
    threads = atoi(argv[2]);
    if (N > MAX_SIZE || threads > MAX_THREADS) {
        printf("Too large N or thread count.\n");
        return 1;
    }

    allocate_and_fill();
    pthread_mutex_init(&row_mutex, NULL);

    pthread_t t[threads];

    struct timeval start, end;
    gettimeofday(&start, NULL);

    for (int i = 0; i < threads; ++i) {
        pthread_create(&t[i], NULL, multiply, NULL);
    }

    for (int i = 0; i < threads; ++i) {
        pthread_join(t[i], NULL);
    }

    gettimeofday(&end, NULL);
    long ms = (end.tv_sec - start.tv_sec) * 1000 + 
              (end.tv_usec - start.tv_usec) / 1000;

 //   printf("Matrix size: %d, Threads: %d, Time: %ld ms\n", N, threads, ms);

    if (N <= 5) {
        printf("Matrix A:\n");
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) printf("%d ", A[i][j]);
            printf("\n");
        }
        printf("Matrix B:\n");
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) printf("%d ", B[i][j]);
            printf("\n");
        }
        printf("Matrix C:\n");
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) printf("%d ", C[i][j]);
            printf("\n");
        }}

    FILE *f = fopen("results.csv", "a");
    if (!f) {
        perror("Cannot open results.csv");
        return 1;
    }

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    if (size == 0) {
        fprintf(f, "matrix_size,threads,time_ms\n");
    }

    fprintf(f, "%d,%d,%ld\n", N, threads, ms);
    fclose(f);

    printf("Matrix size: %d, Threads: %d, Time: %ld ms\n", N, threads, ms);


    pthread_mutex_destroy(&row_mutex);
    free_matrices();
    return 0;
}
