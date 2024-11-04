#include <stdio.h>
#include <math.h>
#define LEN 4		//CHANGE IF U WANNA OTHER LEN OF MATRIX

void copy_matrix(int source[][LEN], int destination[][LEN], int len);
int det(int len, double de, int matrix[len][len]);


void main() {
    int matrix[LEN][LEN]= {
        {2,5,4,1},
        {1,3,2,1},
        {2,10,9,7},
        {3,8,9,2}
    };
    int temp_kramer[LEN][LEN];
    copy_matrix(matrix,temp_kramer,LEN);
    int equation[]={20,11,40,37};
    double de=0.0;
    de=det(LEN,de,matrix);
    printf("Determinant delta: %f\n",de);
    for(int a=0;a<LEN;a++){
        copy_matrix(matrix,temp_kramer,LEN);
        for(int b=0;b<LEN;b++){
            temp_kramer[b][a]=equation[b];
        }
        printf("x[%d] = %lf\n",a,det(LEN,0,temp_kramer)/de);
    }
}

void copy_matrix(int source[][4], int destination[][4], int len) {
    for(int i=0;i<len;i++) {
        for(int j=0;j<len;j++) {
            destination[i][j]=source[i][j];
        }
    }
}

int det(int len, double de, int matrix[len][len]) {
    if(len==1) {
        return matrix[0][0];
    }
    if(len==2) {
        return (matrix[0][0]*matrix[1][1])-(matrix[1][0]*matrix[0][1]);
    }
    for(int row=0;row<len;row++) {
        int temp[len-1][len-1];
        for(int r=1;r<len;r++) {
            int extra_col=0;
            for(int c=0;c<len;c++) {
                if(c!=row) {
                    temp[r-1][extra_col++]=matrix[r][c];
                }
            }
        }
        de += (pow(-1,row)*matrix[0][row]*det(len-1,0,temp));
    }
    return de;
}