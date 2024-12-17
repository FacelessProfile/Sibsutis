#include <stdio.h>
void main(){
int n = 0;
int s = 1;
scanf("%d",&n);
for (int i=1; i<=n; i++){
	 s = s * i;
	}
printf("%d! is equal to %d \n",n,s);
}
