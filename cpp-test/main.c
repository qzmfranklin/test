#include <stdio.h>
#include <assert.h>
#include "mkl.h"

int main(int argc, char const* argv[])
{
        int i;
        for (i = 0; i < 10; i++) {
                assert(i<=8);
        }
	double** a;
	a = (double **) MKL_malloc(10*20*sizeof(double),64);
	if (!a) {
		printf("MKL_malloc failed\n" );
	}
	else {
		printf("MKL_malloc success\n");
		MKL_free(a);
	}

        return 0;
}
