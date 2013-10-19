      module inputs
        use math
        implicit none
        integer(kind=byte), parameter   :: Nd=100, Nm=2*Nd+1
        integer(kind=byte), parameter   :: Ns=914, Nn=Ns, Ng=Nn*Nm

      contains
             
        real(kind=byte) function phasef(m)
          implicit none
          integer(kind=byte), intent(in) :: m
          real(kind=byte), parameter :: g=0.5
          phasef = g**abs(m)
        end function phase
        real(kind=byte) function muafun(x,y)
          implicit none
          real(kind=byte), intent(in) :: x,y
          muafun = 0.1*(x*x+y*y)
        end function muafun
        real(kind=byte) function musfun(x,y)
          implicit none
          real(kind=byte), intent(in) :: x,y
          musfun = 0.2*(x+y)
        end function musfun
        real(kind=byte) function mutfun(x,y)
          implicit none
          real(kind=byte), intent(in) :: x,y
          mutfun = musfun(x,y) + muafun(x,y)
        end function mutfun
      end module inputs
