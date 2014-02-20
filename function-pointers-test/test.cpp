#include <iostream>



typedef int(*int_func_ptr)(int,int);

int add_two_int(int m, int n) {
	return m+n;
}





int main(int argc, char const* argv[])
{
	int (*function_ptr)(int,int);
	function_ptr = &add_two_int;
	int m=10, n=11;
	printf("%d+%d=%d\n",m,n,function_ptr(m,n));
	return 0;
}
