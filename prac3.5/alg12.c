#include <stdio.h>
void main(){
int a,n,s,k;
scanf("%d",&a);
for (n=a, s=0; n!=0; n=n/10)
      { k=n%10;
	s=s+k;
	}

printf("sum of all digits of %d is: %d\n",a,s);
}


