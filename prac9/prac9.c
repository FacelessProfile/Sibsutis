#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void inputMatrix(int **matrix, int len){
    printf("Input elements one by one:\n");
    for (int i=0; i<len;i++){
        for (int j=0;j< len;j++){
            if (scanf("%d",&matrix[i][j])!=1){
                printf("input error!\n");
                exit(1);
            }
        }
    }
}

void randomMatrix(int **matrix,int len){
    srand(time(0));
    for (int i=0;i<len;i++){
        for (int j=0; j<len;j++){
            matrix[i][j] =rand()%10;
        }
    }
}

void printMatrix(int **matrix,int len){
    for (int i=0;i<len;i++){
        for (int j= 0;j<len;j++){
            printf("%d ",matrix[i][j]);
        }
        printf("\n");
    }
}

void transpose(int **matrix, int len){
    int zeroCount=0;
    int starta=-1, startb=-1;
    for (int a=0;a< len;a++){
        for (int b=len-1;b>=0;b--){
            if (matrix[a][b]== 0){
                zeroCount++;
                if (starta==-1 && startb==-1 && a<=b){
                    starta=a;
                    startb=len-b;
                }
            }
        }
    }

    printf("nul count: %d\n", zeroCount);

    if (zeroCount>len){
        for (int i =0;i< len;i++){
            for (int j =0;j <len;j++){
                if (matrix[i][j]==0){
                    matrix[i][j]=zeroCount;
                }
            }
        }
    }
    printf("starta:%d\nstartb:%d\n",starta,startb);
    if ( (starta!=-1) && (startb!=-1) ){
        printf("transPONed matrix with replacement:\n");
        for (int i=starta;i<len-1;i++){
            for (int j=startb;j<len;j++){
                    int temp=matrix[i][j];
                    matrix[i][j]=matrix[j][i];
                    matrix[j][i]=temp;
            }
        }
    }
	else{
	printf("!!!not transPONed!!!\n");
}
    printf("Output matrix:\n");
    printMatrix(matrix, len);
}

int main(){
    int len;
    printf("Input matrix size: ");
    if (scanf("%d", &len) != 1 || len <= 0){
        printf("Input error!.\n");
        exit(1);
    }

    int **matrix=(int **)malloc(len *sizeof(int *));
    if (matrix==NULL){
        printf("Malloc ERROR! PLEASE NOT AGAIN\n");
        exit(1);
    }

    for (int i=0; i<len; i++){
        matrix[i]=(int *)malloc(len * sizeof(int));
        if (matrix[i]==NULL){
            printf("Malloc error STOP IT ДРОП ЫЙД БЭЙС ой...%d!\n", i);
            exit(1);
        }
    }

    int choice;

    printf("choose the one method:\n1.input by urself \n2.Get a random one\n");
    if (scanf("%d",&choice)!=1 || (choice!=1 && choice!= 2)){
        printf("Not a one of the variants.\n");
        exit(1);
    }

    if (choice==1){
        inputMatrix(matrix, len);
    }
    else{
        randomMatrix(matrix,len);
        printf("pregenerated matrix:\n");
        printMatrix(matrix,len);
    }

    transpose(matrix,len);

    for (int i=0;i<len;i++){
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}
