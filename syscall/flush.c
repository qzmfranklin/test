#include <stdio.h>
#include <sys/syscall.h>
#include <asm/unistd.h>
/******************************************************************************/
int main(int argc, char const* argv[])
{
	syscall(__NR_flush_cache);
	return 0;
}
