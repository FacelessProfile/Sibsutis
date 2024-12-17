#include <stdio.h>
#include <stdlib.h>
#include <math.h>
struct conus{
                double r;
                double h;
                double volume;
                double surface;
        };
void print_structs(struct conus names[],int n);
void volume_surface(struct conus names[],int n);
