#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct conus{
		double r;
		double h;
		double volume;
		double surface;
	};

void print_structs(struct conus names[],int n){
	for (int i=0;i<n;i++){
		printf("__________\n");
		printf("counus#%d\nradius:%lf\nheight:%lf\nvolume:%lf\nsurface:%lf\n",i,names[i].r,names[i].h,names[i].volume,names[i].surface);
	}
}

void volume_surface(struct conus names[],int n){
	for (int i=0;i<n;i++) {
		names[i].volume = (0.3333)*(3.14*pow(names[i].r,2))*(names[i].h);
		names[i].surface = (3.14*pow(names[i].r,2))+(names[i].r *sqrt((pow(names[i].r,2))+(pow(names[i].h,2))) *3.14);
	}
}

int main(){
	int x;
	if (scanf("%d",&x)!=1){
		printf("incorrect input\n");
		exit;
	}
	else{
		struct conus cons[x];
		double radius;
		double height;
		for (int i=0;i<x;i++){
			if ((scanf("%lf",&radius)==1)&&(scanf("%lf",&height)==1)){
				cons[i].r=radius;
				cons[i].h=height;
			}
			else{
			exit;
			}
		radius,height=0;
		}
		volume_surface(cons,x);
		print_structs(cons,x);
		return 0;
	}
}
