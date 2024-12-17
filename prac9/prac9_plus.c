#include <stdio.h>
#include <math.h>

double precision =pow(10,-3);
double znach=0;

int count=0;

double recurs(double x,int n,double precision,double result){

    double factorial =1;

    for (int i= 1;i<=2*n;i++){

        factorial*=i;
    }
    result=pow(-1,n)*pow(x,2*n)/factorial;

    znach+=result;

    count++;

    printf("step no.%d: %lf\n",count,result);
    if (fabs(result)<precision){
        printf("number of summands: %d\n", count);

        return znach;
    }
    recurs(x,n+1,precision,result);
}

int main(){

    double x;
    printf("enter the value of x: ");
    if (scanf("%lf", &x) != 1) {
        printf("Invalid input.\n");
        return 1;
    }
    double res = recurs(x,0,precision,0);
    printf("final result\n");
    printf("%lf\n",res);
    return 0;
}
