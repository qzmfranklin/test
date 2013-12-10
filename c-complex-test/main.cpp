#include <stdio.h>
#include <complex.h>
#include "mkl.h"
#include <math.h>
/******************************************************************************/


int main(int argc, char *argv[])
{
	double _Complex x = -1.0 + 0.8I;
	double _Complex z = 1.0 + 0.9I;
	printf("z.real\t= %lf\n",creal(z));
	printf("z.imag\t= %lf\n",cimag(z));
	printf("&z\t= %p\n",&z);
	printf("sizeof(z)\t= %lu\n",sizeof(z));
	printf("cexp(1.0I)\t= %lf + %lfI\n",creal(cexp(1.0I)),cimag(cexp(1.0I)));
	return 0; 
}
