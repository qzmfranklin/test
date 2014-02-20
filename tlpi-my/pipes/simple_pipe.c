#include <sys/wait.h>
#include <stdio.h>
#include <limits.h>

int main(int argc, char *argv[])
{
	printf("PIPE_BUF\t= %d\n",PIPE_BUF);

	return 0;
}
