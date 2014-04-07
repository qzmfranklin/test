#include <stdio.h>
/******************************************************************************/
int main(int argc, char const* argv[])
{
	int n;
	scanf("%d",&n);
	size_t f=1;
	printf("%5d! = %lu\n",0,1l);
	for (int i = 1; i <= n; i++) { 
		f *= i;
		printf("%5d! = %lu\n",i,f);
	}

	return 0;
}
