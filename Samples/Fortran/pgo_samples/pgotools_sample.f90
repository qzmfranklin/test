 module addermod 
   implicit none 
   contains 
   subroutine mod_add(i1, i2, i4, i8, res) 
     integer(1), intent(in) :: i1 
     integer(2), intent(in) :: i2 
     integer(4), intent(in) :: i4 
     integer(8), intent(in) :: i8 
     integer, intent(out) :: res 
     res = i1 + i2 + i4 + i8 
   end subroutine mod_add 
 end module addermod 
  
 subroutine delegate(non_existent, res)      ! no_cover 
   implicit none 
   external non_existent 
   integer, intent(in) :: res 
   call non_existent(1_1, 2_2, 4_4, 8_8, res) 
 end subroutine delegate 
  
 program main 
   use addermod 
   implicit none 
   integer :: res 
   call delegate(mod_add, res)               ! begin_cover 
   if (res /= 15) print *, 'mod_add failed' 
   call delegate(main_add, res) 
   if (res /= 15) print *, 'main_add failed' ! end_cover 
   contains 
   subroutine main_add(i1, i2, i4, i8, res) 
     integer(1), intent(in) :: i1 
     integer(2), intent(in) :: i2 
     integer(4), intent(in) :: i4 
     integer(8), intent(in) :: i8 
     integer, intent(out) :: res 
     res = i1 + i2 + i4 + i8 
   end subroutine main_add 
 end program main
