!Last Modified: 2013-09-23T22:04:28
program laplace
use, intrinsic:: iso_c_binding
implicit none
include "mpif.h"

character(mpi_max_processor_name):: pe_processor_name
integer,parameter::     NROWTOT=1600,   NCOLTOT=1600,   NROW=1600
integer::               NCOL
integer::       pe_rank, pe_size, pe_len, pe_ierr, pe_status(mpi_status_size)
integer::       niter=0
real*8,dimension(:,:),allocatable::        t
real*8::        maxdiff=0.0d0, pe_maxdiff=999.9d0
call mpi_init(pe_ierr)
call mpi_comm_size(mpi_comm_world,pe_size,pe_ierr)
call mpi_comm_rank(mpi_comm_world,pe_rank,pe_ierr)
call mpi_get_processor_name(pe_processor_name,pe_len,pe_ierr)
NCOL=NCOLTOT/pe_size

allocate(t(0:NROW+1,0:NCOL+1)) 
call init_array() 
do while(niter<=50000)
        call update_array()
        if (pe_rank .eq. 0 .and. mod(niter,1000) .eq. 0) then
                print '("niter=",I8,"  maxdiff=",1pE11.3)',niter,maxdiff
        end if
        !call mpi_barrier(mpi_comm_world,pe_ierr) 
        niter=niter+1
end do 
deallocate(t)

call mpi_finalize(pe_ierr) 

contains
        subroutine init_array()
                integer         i,j
                t=0.0d0
                do j=0,NCOL+1,1 
                        t(0,j)=top_boundary_val(j)
                        t(NROW+1,j)=bottom_boundary_val(j)
                end do 
                if (pe_rank .eq. 0) then ! left block
                        print '("PE",I2,": left block")',pe_rank
                        do i=1,NROW,1
                                t(i,0)=left_boundary_val(i)
                        end do 
                else if (pe_rank .eq. (pe_size-1) ) then ! right block
                        print '("PE",I2,": right block")',pe_rank
                        do i=1,NROW,1
                                t(i,NCOL+1)=right_boundary_val(i)
                        end do 
                else ! middle blocks
                        print '("PE",I2,": middle block ",I2)',pe_rank,pe_rank
                end if
        end subroutine
        subroutine update_array() 
                integer::       i,j 
                integer::       pe_root=0, pe_tag_right=101, pe_tag_left=102
                integer::       pe_request_send1,pe_request_send2,pe_request_recv1,pe_request_recv2
                !real*8::        tmp_t
                pe_maxdiff=0.0d0
                !do j=1,NCOL,1
                        !do i=1,NROW,1
                                !tmp_t=t(i,j)
                                !t(i,j)=0.25*(t(i-1,j)+t(i+1,j)+t(i,j-1)+t(i,j+1)) 
                                !pe_maxdiff=max(abs(t(i,j)-tmp_t),pe_maxdiff)
                        !end do 
                !end do 
                if (pe_rank .lt. (pe_size-1)/2) then
                        do j=1,NCOL,1
                                do i=1,(NROW-1)/2+1,1
                                        call update_element(i,j)
                                        call update_element(NROW-i,j)
                                end do 
                        end do 
                else if (pe_rank .gt. (pe_size-1)/2) then
                        do j=NCOL,1,1
                                do i=1,(NROW-1)/2+1,1
                                        call update_element(i,j)
                                        call update_element(NROW-i,j)
                                end do 
                        end do 
                else 
                        do j=1,(NCOL-1)/2+1,1
                                do i=1,(NROW-1)/2+1,1
                                        call update_element(i,j)
                                        call update_element(NROW-i,j)
                                        call update_element(i,NCOL-j)
                                        call update_element(NROW-i,NCOL-j)
                                end do 
                        end do 
                end if 
                if (pe_rank .eq. 0) then 
                        !call mpi_send(t(1,NCOL),NROW,mpi_real,pe_rank+1,pe_tag_right,mpi_comm_world,pe_ierr)
                        !call mpi_recv(t(1,NCOL+1),NROW,mpi_real,pe_rank+1,pe_tag_left,mpi_comm_world,pe_status,pe_ierr)
                        call mpi_isend(t(1,NCOL),NROW,mpi_real,pe_rank+1,pe_tag_right,mpi_comm_world,pe_request_send1,pe_ierr)
                        call mpi_irecv(t(1,NCOL+1),NROW,mpi_real,pe_rank+1,pe_tag_left,mpi_comm_world,pe_request_recv1,pe_ierr)
                        call mpi_wait(pe_request_send1,pe_status,pe_ierr)
                        call mpi_wait(pe_request_recv1,pe_status,pe_ierr)
                else if (pe_rank .eq. (pe_size-1)) then 
                        !call mpi_send(t(1,1),NROW,mpi_real,pe_rank-1,pe_tag_left,mpi_comm_world,pe_ierr)
                        !call mpi_recv(t(1,0),NROW,mpi_real,pe_rank-1,pe_tag_right,mpi_comm_world,pe_status,pe_ierr)
                        call mpi_isend(t(1,1),NROW,mpi_real,pe_rank-1,pe_tag_left,mpi_comm_world,pe_request_send1,pe_ierr)
                        call mpi_irecv(t(1,0),NROW,mpi_real,pe_rank-1,pe_tag_right,mpi_comm_world,pe_request_recv1,pe_ierr)
                        call mpi_wait(pe_request_send1,pe_status,pe_ierr)
                        call mpi_wait(pe_request_recv1,pe_status,pe_ierr)
                else
                        !call mpi_send(t(1,1),NROW,mpi_real,pe_rank-1,pe_tag_left,mpi_comm_world,pe_ierr)
                        !call mpi_recv(t(1,0),NROW,mpi_real,pe_rank-1,pe_tag_right,mpi_comm_world,pe_status,pe_ierr)
                        !call mpi_send(t(1,NCOL),NROW,mpi_real,pe_rank+1,pe_tag_right,mpi_comm_world,pe_ierr)
                        !call mpi_recv(t(1,NCOL+1),NROW,mpi_real,pe_rank+1,pe_tag_left,mpi_comm_world,pe_status,pe_ierr)
                        call mpi_isend(t(1,1),NROW,mpi_real,pe_rank-1,pe_tag_left,mpi_comm_world,pe_request_send1,pe_ierr)
                        call mpi_isend(t(1,NCOL),NROW,mpi_real,pe_rank+1,pe_tag_right,mpi_comm_world,pe_request_send2,pe_ierr)
                        call mpi_irecv(t(1,NCOL+1),NROW,mpi_real,pe_rank+1,pe_tag_left,mpi_comm_world,pe_request_recv1,pe_ierr)
                        call mpi_irecv(t(1,0),NROW,mpi_real,pe_rank-1,pe_tag_right,mpi_comm_world,pe_request_recv2,pe_ierr)
                        call mpi_wait(pe_request_send1,pe_status,pe_ierr)
                        call mpi_wait(pe_request_recv1,pe_status,pe_ierr)
                        call mpi_wait(pe_request_send2,pe_status,pe_ierr)
                        call mpi_wait(pe_request_recv2,pe_status,pe_ierr)
                end if 
                call mpi_reduce(pe_maxdiff,maxdiff,1,mpi_double_precision,mpi_max,pe_root,mpi_comm_world,pe_ierr)
        end subroutine 
        subroutine update_element(i,j)
                integer,intent(in)::i,j
                real*8::tmp_t
                tmp_t=t(i,j)
                t(i,j)=0.25*(t(i-1,j)+t(i+1,j)+t(i,j-1)+t(i,j+1)) 
                pe_maxdiff=max(abs(t(i,j)-tmp_t),pe_maxdiff)
        end subroutine

        real*8 function top_boundary_val(col) result (val)
                integer, intent(in)::col
                val=100.0d0*dble(col+pe_rank*NCOL)/dble(NCOL*pe_rank+2)
        end function
        real*8 function bottom_boundary_val(col) result (val)
                integer, intent(in)::col
                val=100.0d0*dble(col+pe_rank*NCOL)/dble(NCOL*pe_rank+2)
        end function 
        real*8 function left_boundary_val(row) result(val)
                integer, intent(in)::row
                val=100.0d0*row/dble(NROW+2)
        end function
        real*8 function right_boundary_val(row) result(val)
                integer, intent(in)::row
                val=100.0d0*row/dble(NROW+2)
        end function
end program
