#define MAX_PATH_LEN 1024
#define MAX_CMD_ARG_LEN 80
#define MAX_CMD_LINE_LEN 1024
#define RK_FILE_UNIT 91
#define MAX_N_ITER 1000000

program runge_kutta
implicit none
        character(len=MAX_PATH_LEN)::runge_kutta_type_filename
        character(len=MAX_CMD_LINE_LEN)::cmd
        character(len=MAX_CMD_ARG_LEN),dimension(:),allocatable::argv
        integer::argc
        integer::i,j
        integer::alloc_error, dealloc_error
        integer::open_status,close_status

        integer::RK_order,RK_stage,RK_explicit,RK_adaptive
        real*8,dimension(:,:),allocatable::RK_a, RK_b
        real*8,dimension(:),allocatable::RK_c, RK_k

        real*8::x,y
        real*8::x_min,x_max,h
        integer::niter
        
        call read_cmd_options()

        call read_rk_method_from_file()

        if (RK_adaptive .eq. 0) then 
                call explicit_non_adaptive_rk()
        else
                call explicit_adaptive_rk()
        end if

        deallocate(RK_a,RK_b,RK_c,RK_k,stat=dealloc_error) 

        contains
                real*8 function f(x,y) result(val)
                        real*8,intent(in)::x,y 
                        val=x*sin(y*y+2.0d0*x+1.0d0)
                end function
                subroutine read_cmd_options () 
                        ! read in all command line arguments
                        call get_command(cmd)
                        argc=command_argument_count()
                        !print *,"cmd=",cmd
                        !print *,"argc=",argc
                        allocate(argv(0:argc),stat=alloc_error)
                        do i=0,argc,1 ! get_command_argument
                                call get_command_argument(i,argv(i))
                                !print *,"argv(",i,")=",argv(i)
                        end do 
                        if (argc < 4) then ! abort if too few arguments
                                print *,"Needs 4 arguments: [x_min] [x_max] [h] [*.RK]. Abort."
                                call exit()
                        end if
                        read (argv(1),'(F40.20)'),x_min
                        read (argv(2),'(F40.20)'),x_max
                        read (argv(3),'(F40.20)'),h
                        print *,"x_min=",x_min
                        print *,"x_max=",x_max
                        print *,"h=",h
                        runge_kutta_type_filename=argv(4)
                        !print *,runge_kutta_type_filename
                        print '("runge_kutta_type_filename=",A20)',runge_kutta_type_filename
                        ! finished using argv and argc, de-allocate
                        deallocate(argv,stat=dealloc_error)
                end subroutine read_cmd_options
                subroutine read_rk_method_from_file () 
                        ! read the specified RK file
                        open(unit=RK_FILE_UNIT,file=runge_kutta_type_filename,status='old',iostat=open_status,action='read',position='rewind') 
                        !print *,'open_status=',open_status
                
                        ! read the file header
                        read (RK_FILE_UNIT,'("BeginHeader")')
                        read (RK_FILE_UNIT,'(I2)'),RK_order
                        read (RK_FILE_UNIT,'(I2)'),RK_stage
                        read (RK_FILE_UNIT,'(I1)'),RK_explicit
                        read (RK_FILE_UNIT,'(I1)'),RK_adaptive
                        read (RK_FILE_UNIT,'("EndHeader")')
                        if (RK_explicit .ne. 1) then 
                                print *,'implicit Runge-Kutta is not supported yet. abort'
                                call exit()
                        end if
                        ! allocate RK tableau and initialize with zeros
                        allocate(RK_a(RK_stage-1,2:RK_stage),stat=alloc_error)
                        allocate(RK_b(RK_stage+RK_adaptive,RK_adaptive+1),stat=alloc_error)
                        allocate(RK_c(2:RK_stage),stat=alloc_error)
                        allocate(RK_k(RK_stage),stat=alloc_error)
                        RK_a=0.0d0
                        RK_b=0.0d0
                        RK_c=0.0d0
                        RK_k=0.0d0
                        ! read RK tableau
                        read (RK_FILE_UNIT,'("BeginTableau")')
                        read (RK_FILE_UNIT,'("RK_a")')
                        do i=2,RK_stage,1 
                                read (RK_FILE_UNIT,'("line ",I2)'),j
                                !print *,i-j
                                do j=1,i-1,1 
                                        read (RK_FILE_UNIT,'(F40.20)'),RK_a(j,i)
                                end do 
                        end do 
                        read (RK_FILE_UNIT,'("RK_b")')
                        do i=1,RK_stage,1 
                                read (RK_FILE_UNIT,'(F40.20)'),RK_b(i,1)
                        end do 
                        read (RK_FILE_UNIT,'("RK_c")')
                        do i=2,RK_stage,1 
                                read (RK_FILE_UNIT,'(F40.20)'),RK_c(i)
                        end do 
                        read (RK_FILE_UNIT,'("EndTableau")') 
                        print '("RK_order=",I2)',RK_order
                        print '("RK_stage=",I2)',RK_stage
                        print '("RK_explicit=",I2)',RK_explicit
                        print '("RK_adaptive=",I2)',RK_adaptive
                        print *,"RK_a=",RK_a
                        print *,"RK_b=",RK_b
                        print *,"RK_c=",RK_c 
                        close(unit=RK_FILE_UNIT,iostat=close_status)
                        !print *,'close_status=',close_status
                end subroutine read_rk_method
                subroutine explicit_non_adaptive_rk () 
                        ! main loop
                        x=x_min
                        y=0.0d0
                        niter=min(int((x_max-x_min)/h),MAX_N_ITER)
                        do i=1,niter,1 
                                RK_k(1)=h*f(x,y)
                                do j=2,RK_stage,1
                                        RK_k(j)=h*f(x+RK_c(j)*h,y+sum((RK_a(1:j-1,j)*RK_k(1:j-1))))
                                end do 
                                h=h
                                x=x+h
                                y=y+sum(RK_b(:,1)*RK_k)
                                print '("(x,y)=(",2(F34.16),")")',x,y
                                !print *,RK_k
                        end do 
                end subroutine explicit_non_adaptive_rk
                subroutine explicit_adaptive_rk () 
                        print *,'explicit_adaptive_rk not impelemented yet. call explicit_non_adaptive_rk instead...'
                        call explicit_non_adaptive_rk()
                end subroutine explicit_adaptive_rk
end program 
