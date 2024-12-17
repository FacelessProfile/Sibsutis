#include <stdio.h>
#include <math.h>

void print_arr(int n, int target[n][n]){
for (int i=0;i<n;i++){
	for (int j;i<n;i++){
		printf("%d",target[i][j]);
		}
	}
}

// void input_data(){
//	char x[256];
//	fgets(x,256,stdin);
//}

//void get_data(int n, int target[n][n]){
//	for (int i=0;i<n;i++){
//		for (int j = 0;j<n;j++){
//			target[i][j]=
//		}
//	}
//}

void main(){
int n;
scanf("%d",&n);
int array[n][n]={{5,2},{2,1}};
int resArray[2][1]={{7},{9}};

//get_data(n,array);
print_arr(n,array);
}
