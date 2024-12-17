#include <stdio.h>
void main(){
int s = 0;
int a =0;
scanf("%d",&a);
for (int n=a; n!=0; n=n/10)
        {
	int k=n%10;
	 if (k>s) s=k;
	}
	printf("the biggest digit in number %d is:%d\n",a,s);
}
