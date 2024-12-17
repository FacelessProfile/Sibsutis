#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int get_borders(char* a,int n){
for (int i=0;i<=n;++i){
if (a[i]=='-'){

for (int x=a[i-1]+1;x<a[i+1];++x){
printf("%c ",x);
}
}

else if (a[i]==','){
;
}
else {
printf("%c ",a[i]);
}
}

}

int main(int argc, int *argv[]){
int n=strlen((char) argv[0])-1;
char* a=malloc(n*sizeof(char));
getchar();
fgets(a,n,stdin);
get_borders(a,n);
}
