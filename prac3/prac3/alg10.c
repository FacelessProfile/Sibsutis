#include <stdio.h>
void main(){
int a =0;
int s =0;
scanf("%d",&a);
for (int n=a; n!=0; n=n/10){
	int k=n%10;
	s=s*10+k;
	}
printf("number %d reversed: %d\n",a,s);
}
