#include <stdio.h>
#include "Vector.h"
/******************************************************************************/
int test01(void);
/******************************************************************************/ 
int main(int argc, char const* argv[])
{
	test01(void);
	return 0;
}

int test01(void)
{
	int err=0; 
        printf("TEST01\n");
        printf("	|Test Vector Matrix\n");
	const int m=10,n=10;
	double a[m*n];


        printf("END OF TEST01\n");
        printf("\n");
	return err;
}
