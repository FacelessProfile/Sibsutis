#include <stdio.h>
void main() {
    int height,i,j,k;
    printf("Input height: ");
    scanf("%d",&height);
    for (i=0;i<height;i++) {
        for (k=0;k<i;k++) {
            printf(" ");
        }
        for (j=0;j<height-i;j++) {
            printf("%c",65+i);
        }
        printf("\n");
    }
}

