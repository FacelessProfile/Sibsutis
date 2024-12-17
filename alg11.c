#include <stdio.h>
void main(){
int k, m, n;
scanf("%d", &n);
for (k = 0, m = 1; m <= n; k++, m = m * 2);
printf("number %d is close to 2 in power of %d \n",n,k - 1);
}
