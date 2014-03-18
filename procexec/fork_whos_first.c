#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
/******************************************************************************/
int main(int argc, char const* argv[])
{
	if (argc<2) {
		fprintf(stderr,"usage: ./fork_whos_first.exe [num_trials]\n");
		exit(0);
	}

	int num_trials;
	sscanf(argv[1],"%d",&num_trials);

	enum {
		PARENT_FIRST = 101,
		CHILD_FIRST  = 102
	} flagdata;
	int *flag=&flagdata;

	int num_parent_first=0; 
	for (int i = 0; i < num_trials; i++) {
		pid_t pid;
		switch (pid=fork()) {
		case -1:
			fprintf(stderr,"parent: cannot create child\n");
			exit(1);
			break;
		case 0: // child
			/*fprintf(stderr,"child : %p\n",flag);*/
			*flag = PARENT_FIRST;
			_exit(0);
			break;
		default: // parent
			/*fprintf(stderr,"parent: %p\n",flag);*/
			*flag = CHILD_FIRST;
			wait(NULL);
			break;
		}
		/*if (*flag==CHILD_FIRST)*/
		if (*flag==PARENT_FIRST)
			num_parent_first++;
	}

	fprintf(stderr,"Out of %d trials,\n",num_trials);
	fprintf(stderr,"parent comes first %d times,\n",num_parent_first);
	fprintf(stderr,"child comes first %d times.\n",num_trials-num_parent_first); 

	return 0;
}
