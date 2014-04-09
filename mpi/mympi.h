#ifndef _MYMPI_H_
#define _MYMPI_H_
/******************************************************************************/
#include <mpi.h>
void mpi_init(int &argc, char **&argv, int &size, int &rank)
{
	MPI_Init(&argc,&argv);			/* starts MPI */
	MPI_Comm_size(MPI_COMM_WORLD,&size);	/* get number of processes */
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);	/* get current process id */
}
/******************************************************************************/
#endif
