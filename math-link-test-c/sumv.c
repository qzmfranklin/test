#include "stdio.h"
#include "mathlink.h"

double sumv(double *v, long vlen){
	double sum=0.0;
	long i=0;
	for (i = 0; i < vlen; i++) {
		sum+=v[i];
	}
	return sum;
}

int main(int argc, char *argv[])
{
	return MLMain(argc,argv);
}
