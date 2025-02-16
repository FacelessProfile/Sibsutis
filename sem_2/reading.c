#include <stdio.h>
#define NEEDED 0    //YOUR LINE NUMBER
#define SIZE 64     //SIZE OF BUFFER
int main(){
int counter=0;
FILE *f = fopen("PATH.txt","r");
char buf[SIZE];
while(fgets(buf,SIZE,f)!=NULL){
	if (counter==NEEDED){
		int len=0;
		while (buf[len] != '\0'){
			len++;
		}
            	if (len>0 && buf[len-1] == '\n') {
                	buf[len-1] = '\0';
		}
		printf("%s",buf);
		break;
	}
	else{
	counter++;
	}
}


fclose(f);
}
