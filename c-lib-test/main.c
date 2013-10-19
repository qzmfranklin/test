#include <stdio.h>
#include "mylib.h"

int main(int argc, char *argv[])
{ 
	int x=0;
	printf("test mylib\n");
	printf("call mylib_foo\n");
	mylib_foo(x);
	return 0;
} 
