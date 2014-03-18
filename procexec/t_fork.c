#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
/******************************************************************************/
static int idata=111;


int main(int argc, char *argv[])
{
	int istack=222;
	pid_t child_pid;
	switch (child_pid=fork()) {
	case -1:
		fprintf(stderr,"parent: cannot create child process\n");
		exit(1);
		break; 
	case 0: 
		idata *=3;
		istack*=3;
		fprintf(stderr,"%-8lu child : idata=%d istatck=%d\n",
				(size_t)getpid(),idata,istack);
		_exit(0);
		break;
	default: 
		sleep(1);
		fprintf(stderr,"%-8lu parent: idata=%d istatck=%d\n",
				(size_t)getpid(),idata,istack);
		wait(NULL);
		break;
	}
	fprintf(stderr,"See? After the fork(), the parent and the child\n");
	fprintf(stderr,"have independent stack and data segments.\n");
	return 0;
}
