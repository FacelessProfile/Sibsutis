#include <stdio.h>
#include <math.h>

void main() {
    int n;
    int input;
    int minSeries; 

    scanf("%d", &n);
    int array_A[n];
    int prime_arr[n]; // var-s initialization + scanning length of arrays

    void input_array(int x, int Target[x]) {
        for (int i = 0; i < x; i++) {
            scanf("%d", &input);                //void to input data in target array
            Target[i] = input;
        }
    }

    void copy_array(int x, int Target[x], int dest[x]) {
        for (int i = 0; i < x; i++) {
            dest[i] = Target[i];                //void to copy data from target array to other
        }
    }

    void print_array(int x, int Target[x]) {
        for (int i = 0; i < x; i++) {
            printf("%d ", Target[i]);           // array to print each member of target array
        }
        printf("\n");
    }

    void find_series(int x, int Target[x]) {
        minSeries = x + 1;
        int temp = 0;
        for (int i = 0; i < x; i++) {
            if ((Target[i] % 2) != 0 && Target[i] != 0) {
                temp += 1;                                  //void t0 find smallest odd number series in target array
            } else {
                if (temp > 0 && minSeries > temp) {
                    minSeries = temp;
                }
                temp = 0;
            }
        }
        if (temp > 0 && minSeries > temp) {
            minSeries = temp;
        }
    }

    void find_prime(int x, int Target[x]) {
        int prime_count = 0;
        for (int i = 0; i < x; i++) {
            int is_prime = 1;
            if (Target[i] <= 1) continue;
            for (int del = 2; del <= sqrt(Target[i]); del++) {      //void to find prime numbers in target array and delete it
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
    printf("Original array: ");         //inputin array and printing it (for some reason)
    print_array(n, array_A);

    find_series(n, array_A);
    int initial_minSeries = minSeries;  //finding smallest series in prev array and piping it to initial_minSeries var 

    copy_array(n, array_A, prime_arr);
    find_prime(n, prime_arr);           //deleting prime numbers from the copy of 1 array

    printf("Array after removing first two prime numbers: ");
    print_array(n, prime_arr);          //printing copy with\ primes

    find_series(n, prime_arr);
    printf("Initial min series: %d\n", initial_minSeries); //logging the result
    printf("Updated min series: %d\n", minSeries);
}
