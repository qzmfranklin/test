#include <stdio.h>
#include "mympi.h"
/******************************************************************************/ 
int main (int argc, char **argv)
{
	int np,pid;
	mpi_init(argc,argv,np,pid);
	printf( "Hello world from process %d of %d\n", pid, np );
	MPI_Finalize();
	return 0;
}
