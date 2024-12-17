#include <stdio.h>
#include <math.h>
void main(){

int n;
int input;
int minSeries;

scanf("%d",&n);
int array_A[n];
int prime_arr[n];

void input_array(int x, int Target[x]){
	for (int i=0;i<x;i++){
		scanf("%d",&input);
		Target[i]=input;
		}
}

void copy_array(int x, int Target[x], int dest[x]){
	for(int i=0;i<x;i++){
		dest[i]=Target[i];
		}
}

void print_array(int x, int Target[x]){
	for (int i=0;i<x;i++){
		printf("%d ",Target[i]);
	}
	printf("\n");
}


void find_series(int x, int Target[x]){
	minSeries=x+1;
	for(int i=0,temp = 0;i<x;i++){
		if((Target[i]%2)!=0){
			temp+=1;
			if(i==x-1){
				if((minSeries>=temp)*(temp!=0)){
					minSeries=temp;
					}
				}
			printf("\nTarget[%d]: %d temp: %d",i,Target[i],temp);
		}
		else{
			printf("\n %d temp on odd",temp);
			temp=temp;
			if((minSeries>=temp)*(temp!=0)){
				printf("\n temp on compare %d",temp);
				minSeries=temp;
				printf("\n minseries:%d",minSeries);
			}
			temp=0;
		}
	}
	printf("\n FINAL MINSERIES: %d",minSeries);
	minSeries=0;
}



void find_prime(int x, int Target[x]){
	for(int i=0,temp=0;i<x;i++){
		if (temp==2){
			break;
			}
		for(int del=2;del<=(sqrt(Target[i]));del++){
			if (Target[i]%del==0){
				temp++;
				Target[i]=0;
				break;
				}
			}
		}
}

void revers(int x,int ending, int Target[x],int dest[x]){
	for (int i=0;i<x;i++){
	dest[i] = dest[i]^Target[i];
	temp++;
}
}

input_array(n,array_A);
find_series(n,array_A);
printf("\n");
print_array(n,array_A);
copy_array(n,array_A,prime_arr);
find_prime(n,prime_arr);
revers(n,array_A,prime_arr);
print_array(n,prime_arr);
}
//1 3 2 4 4 4 1 3 1 5 1 7 1 3 2 4 6 2 1 5
//1 3 = temp =2         13151713>len(2) => temp=2
