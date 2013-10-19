#define N 3
program mpiarray
        use, intrinsic:: iso_c_binding
        implicit none
        include "mpif.h"
        !integer*8  mkl_malloc
        !external   mkl_malloc, mkl_free, mkl_mem_stat

        character(mpi_max_processor_name):: pe_processor_name
        integer(c_int32_t):: pe_rank, pe_size, pe_len, pe_ierr, pe_tag, pe_dest, pe_source
        integer:: pe_status(mpi_status_size)
        real(c_double),dimension(:),allocatable::t 
        call mpi_init(pe_ierr)
        call mpi_comm_size(mpi_comm_world,pe_size,pe_ierr)
        call mpi_comm_rank(mpi_comm_world,pe_rank,pe_ierr)
        call mpi_get_processor_name(pe_processor_name,pe_len,pe_ierr)

        allocate(t(N))


        ! send t(2:3) from PE0 to PE1
        pe_dest=1;
        pe_source=0;
        pe_tag=99;
        if (pe_rank .eq. 0) then
                t=(/2.0,3.0,4.0/)
                print *,"Before: PE ",pe_rank,": t=",t
                call mpi_send(t(2),2,mpi_double,pe_dest,pe_tag,mpi_comm_world,pe_ierr)
        else if (pe_rank .eq. 1) then
                t=99.0d0
                call mpi_recv(t(2),2,mpi_double,pe_source,pe_tag,mpi_comm_world,pe_status,pe_ierr)
                print *,"After: PE ",pe_rank,": t=",t
        end if 


        deallocate(t)
        call mpi_finalize(pe_ierr)
end program 
