      module math
        implicit none

        integer(kind=4), parameter  :: byte=16
        real(kind=byte), parameter  :: pi=&
        3.14159265358979323846264338328
        real(kind=byte), parameter  :: e=&
        2.71828182845904523536028747135
        real(kind=byte), parameter  :: euler_gamma=&
        0.577215664901532860606512090082

        contains
            ! recursively compute the factorial of an integer
            recursive integer(kind=byte) function factorial(n) result(nf)
                implicit none
                integer(kind=byte), intent(in)  ::  n
                if (n==1 .or. n==0) then
                    nf=1
                else
                    nf=n*factorial(n-1)
                end if
            end function factorial

      end module math
