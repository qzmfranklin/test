#include <stdio.h>
#include "Vector.h"
/******************************************************************************/
int main(int argc, char const* argv[])
{
	Vector v1(5);
	v1.Print();

	v1(2)=0.9;
	v1.Print();

	Vector v2(5);
	v2=5.0;

	(v2-v1).Print();


	printf("\n");

	return 0;
}
