#include <stdio.h>

void main(){
int maxVal,input;
scanf("%d",&maxVal);
maxVal*=2;
int complex_A[maxVal];
int complex_B[maxVal];
int complex_C[maxVal];


void array_inp(int n, int complex_array[n]){
    for (int i=0;i<n;i++){
        scanf("%d",&input);
        complex_array[i] = input;
    }
}


void print_array(int n, int array[n]) {
    for (int i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}


void merge_array(int n, int First[n],int Second[n],int Final[n]){
    for (int i=0;i<n;i++){
        Final[i]=First[i]+Second[i];
    }
    printf("\n");
}

void max_real(int n,int prevMax, int Target[n]){
    prevMax = Target[0];
    for (int i=0; i<n;i+=2){
        if (prevMax<Target[i]){
            prevMax=Target[i];
        }
    }
    printf("%d",prevMax);
    printf("\n");
}

void less_zero(int n,int less_counter, int Target[n]){
    for (int i=1; i<n;i+=2){
        if (Target[i] <0){
            less_counter++;
        }
    }
    printf("%d",less_counter);
    printf("\n");
}

void avg(int n ,int counter,int Target[n]){
    for (int i=0 ; i<n; i++){
        counter+= Target[i];
    }
    printf("%f",(1.0*counter)/(n-1));
    printf("\n");
}

array_inp(maxVal,complex_A);
printf("array a:");
print_array(maxVal,complex_A);

printf("\n");

array_inp(maxVal,complex_B);
printf("array b:");
print_array(maxVal,complex_B);

merge_array(maxVal,complex_A,complex_B,complex_C);
printf("merged array:");
print_array(maxVal,complex_C);

printf("maxReal from a:");
max_real(maxVal,0,complex_A);
printf("Less than zero in image b:");
less_zero(maxVal,0,complex_B);

avg(maxVal,0,complex_C);
}
