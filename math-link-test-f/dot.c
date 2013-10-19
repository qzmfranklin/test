#include "stdio.h"
#include "mathlink.h"


double dot(double *x, long xlen, double *y, long ylen){
    double sum=0.0;
    if (xlen!=ylen) { printf("unequal lengths, abort\n"); return 0.0;}
    f_dot(&xlen,x,y,&sum);
    return sum;
}

int main(int argc, char *argv[])
{
    return MLMain(argc,argv);
    return 0;
}
