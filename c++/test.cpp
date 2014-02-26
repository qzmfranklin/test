#include <stdio.h>
#include "Vector.h"
/******************************************************************************/
int main(int argc, char const* argv[])
{
	Vector v1(4);
	v1 = 1.5;

	printf("norm\t= %lf\n",norm(v1));
	printf("norm\t= %lf\n",v1.norm());

	return 0;
}
