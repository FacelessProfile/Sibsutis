#include <stdio.h>
#define LEN 15

int director(int len, int prev, int direction, int matrix[LEN][LEN]) {
    int a =(LEN-len)/2;

    if (direction== 0) {
        for (int x= a; x<len+a;x++) {
            matrix[a][x]=prev++;
        }
    } 
    else if (direction==1) {
        for (int x=a+1; x<len+a;x++) {
            matrix[x][len+a-1]=prev++;
        }
    } 
    else if (direction==2) {
        for (int x=len+a-2;x>=a;x--) {
            matrix[len+a-1][x]= prev++;
        }
    } 
    else if (direction==3) {
        for (int x=len+a-2;x>a;x--) {
            matrix[x][a]= prev++;
        }
    }
    return prev; 
}

void print_matrix(int matrix[LEN][LEN]) {
    for (int i= 0;i<LEN;i++) {
        for (int j=0;j<LEN;j++) {
            printf("%4d ",matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    int direction=0;
    int len=LEN;
    int matrix[LEN][LEN]={0};
    int prev=1;

    while (len>0) {
        for (int i=0;i<4;i++) {
            prev=director(len,prev,direction,matrix);
            direction =(direction+1) %4;
        }
        len-=2;
    }

    print_matrix(matrix);
    return 0;
}

