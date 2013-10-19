      module fmodule
      use, intrinsic :: ISO_C_BINDING
      implicit none
      contains
        !subroutine dotc(x,y,z) bind(c,name="f_dotc")
          !integer,parameter::byte=C_DOUBLE_COMPLEX
          !complex(kind=byte),dimension(1:),intent(in)::x,y
          !complex(kind=byte),intent(out)::z
          !z=sum(x*y)
        !end subroutine
        subroutine dot(n,a,b,c) bind(c,name="f_dot")
          integer(C_LONG),intent(in)::n
          real(C_DOUBLE),dimension(n),intent(in)::a,b
          real(C_DOUBLE),intent(out)::c
          c=sum(a*b)
        end subroutine
        subroutine addtwofc(x,y,z) bind(c,name="f_addc")
          integer,parameter::byte=C_DOUBLE_COMPLEX
          complex(kind=byte),intent(in)::x,y
          complex(kind=byte),intent(out)::z
          z=x+y 
        end subroutine
        subroutine takefc(x,y,z) bind(c,name="f_takec")
          integer,parameter::byte=C_DOUBLE_COMPLEX
          complex(kind=byte),intent(in)::x,y
          complex(kind=byte),intent(out)::z
          z=x-y 
        end subroutine
        subroutine addtwof(a,b,c) bind(c,name="f_add")
          integer,parameter::byte=C_INT
          integer(kind=byte),intent(in)::a,b
          integer(kind=byte),intent(out)::c
          c=a+b
        end subroutine
        subroutine substract(a,b,c) bind(c,name="f_take")
          integer,parameter::byte=C_INT
          integer(kind=byte),intent(in)::a,b
          integer(kind=byte),intent(out)::c
          c=a-b
        end subroutine
      end module
