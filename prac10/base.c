#include "ext.h"
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
