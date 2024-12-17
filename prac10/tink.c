#include <stdio.h>
#include <string.h>

void main(){
char str[1000000];
fgets(str,1000000,stdin);
for (int i=0;i<strlen(str);i++){
	if (str[i]!="-"){
		printf("%c ",str[i]);
	}
	else{
		for (int x=(int)str[i-1];i<=(int)str[i+1];i++){
			printf("%c ",x);
		}
	}

}
}
