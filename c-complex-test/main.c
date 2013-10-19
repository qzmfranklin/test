#include <stdio.h>
#include <complex.h>
#include "mkl.h"

int main(int argc, char *argv[])
{
	double complex *z;
	z=(double complex*)mkl_malloc(sizeof(double complex)*2,64);
	/*printf("%f+%f*i\n",creal(z),cimag(z));*/
	printf("%f+%f*i\n%f+%f*i\n",z);
	printf("%d\n",(int)sizeof(z ));
	printf("%d\n",(int)sizeof(float ));
	printf("%d\n",(int)sizeof(double ));
	printf("%d\n",(int)sizeof(float complex));
	printf("%d\n",(int)sizeof(double complex));
	mkl_free(z);
	return 0;
}
