#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <error.h>

static int idata=111;	// Allocated in data segment


int main(int argc, char *argv[])
{
	printf("EXIT_SUCCESS=%d\n",EXIT_SUCCESS);
	printf("EXIT_FAILURE=%d\n",EXIT_FAILURE);


	int istack=222;	// Allocated in stack segment
	pid_t childPid;

	switch (childPid=fork()) {
	case -1:
		exit(EXIT_FAILURE);
		break; 
	case 0:
		idata *= 3;
		istack *= 3;
		break; 
	default:
		sleep(1);	// Give the child process a chance to execute
	}

	// Both parent and child come here
	printf("PID=%ld %s &idata=%p &istack=%p idata=%d istack=%d\n",(long)getpid(),
			(childPid==0)?"child ":"parent",&idata,&istack,idata,istack);

	switch (childPid) {
	case 0:
		_exit(EXIT_SUCCESS);
		break;
	default:
		wait(NULL);	// Reap the child process
		exit(EXIT_SUCCESS);
	}
}
