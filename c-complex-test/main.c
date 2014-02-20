#include <stdio.h>
#include <complex>
#include "mkl.h"
/******************************************************************************/
int main(int argc, char *argv[])
{
	using namespace std;
	complex<double> z(1.02,2.03);
	printf("z\t\t= %lf + %lf*I\n",z.real(),z.imag());
	printf("sizeof(z)\t= %lu\n",sizeof(z));
	printf("&z\t\t= %p\n",&z);
	printf("&z.real()\t= %p\n",&(z.real()));
	printf("&z.imag()\t= %p\n",&(z.imag()));
	return 0;
}
