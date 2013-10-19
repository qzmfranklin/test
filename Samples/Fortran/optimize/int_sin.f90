program int_sin
implicit none

integer, parameter :: DP = kind(0.0D0)
real(DP), parameter :: pi = 3.1415926535897932384626433_DP 
real(DP), parameter :: interval_begin = 0.0_DP
real(DP), parameter :: interval_end   = 2.0_DP * pi
real(DP) :: step, sum, x_i
integer :: N, i, j
real clock_start, clock_finish

write (*,'(A)') "  "
write (*,'(A)') "    Number of    | Computed Integral |"
write (*,'(A)') " Interior Points |                   |"
call cpu_time (clock_start)

do j=2,26
  write (*,'(A)') "--------------------------------------"
  N = 2**j
  step = (interval_end - interval_begin) / real(N,DP);
  sum = INTEG_FUNC(interval_begin) * (step / 2.0_DP)
  do i=1,N-1
    x_i = real(i,DP) * step
    sum = sum + (INTEG_FUNC(x_i) * step)
  end do
  sum = sum + (INTEG_FUNC(interval_end) * (step / 2.0_DP))
  write (*,'(T5,I10,T18,"|",2X,1pE15.7E2,T38,"|")') N, sum
end do

call cpu_time(clock_finish)
write (*,'(A)') "--------------------------------------"
write (*,'(A)') "  "
write (*,*) "CPU Time = ",(clock_finish - clock_start), " seconds"

contains
! Function to integrate
real(DP) function INTEG_FUNC (x)
    real(DP), intent(in) :: x
    INTEG_FUNC = abs(sin(x))
    return
end function INTEG_FUNC
    
end program int_sin
