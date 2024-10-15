#include <stdio.h>

void main(){
int a,bit,res;
res=0;
scanf("%d",&a);
for (int i=0;i<8;i++){
    if(i==0){
        a=a>>0;
    }
    else{
        a=a>>1;
    }
    printf("a %d = %d \n",i,a);
    bit=a&1;
    printf("bit %d = %d \n",i,bit);
    res =res|(bit<<(7-i));
}
printf("result is %d \n",res);
}
// 5
//a00000101 >> 0
//b00000001 & 1
//c10000000 1<<7
//a00000010 >> 1
//10100000
//