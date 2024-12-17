#include <stdio.h>
#include <math.h>

void main() {
    int n;
    int input;
    int minSeries;

    scanf("%d", &n);
    int array_A[n];
    int prime_arr[n];

    void input_array(int x, int Target[x]) {
        for (int i = 0; i < x; i++) {
            scanf("%d", &input);
            Target[i] = input;
        }
    }

    void copy_array(int x, int Target[x], int dest[x]) {
        for (int i = 0; i < x; i++) {
            dest[i] = Target[i];
        }
    }

    void print_array(int x, int Target[x]) {
        for (int i = 0; i < x; i++) {
            printf("%d ", Target[i]);
        }
        printf("\n");
    }

    void find_series(int x, int Target[x]) {
        minSeries = x + 1;
        for (int i = 0, temp = 0; i < x; i++) {
            if ((Target[i] % 2) != 0) {
                temp += 1;
                if (i == x - 1 && temp > 0 && minSeries > temp) {
                    minSeries = temp;
                }
            } else {
                if (temp > 0 && minSeries > temp) {
                    minSeries = temp;
                }
                temp = 0;
            }
        }
    }

    void find_prime(int x, int Target[x]) {
        int prime_count = 0;
        for (int i = 0; i < x; i++) {
            int is_prime = 1;
            if (Target[i] <= 1) continue;
            for (int del = 2; del <= sqrt(Target[i]); del++) {
                if (Target[i] % del == 0) {
                    is_prime = 0;
                    break;
                }
            }
            if (is_prime) {
                Target[i] = 0;
                prime_count++;
                if (prime_count == 2) break;
            }
        }
    }


    input_array(n, array_A);
    printf("Original array: ");
    print_array(n, array_A);

    find_series(n, array_A);
    int initial_minSeries = minSeries;

    copy_array(n, array_A, prime_arr);
    find_prime(n, prime_arr);

    printf("Array after removing first two prime numbers: ");
    print_array(n, prime_arr);

    copy_array(n, array_A, prime_arr);
    find_series(n, prime_arr);

    printf("Initial min series: %d\n", initial_minSeries);
    printf("Updated min series: %d\n", minSeries);
}

