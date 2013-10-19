      module fmodule
      use, intrinsic :: ISO_C_BINDING
      implicit none
      contains
        subroutine dotc(x,y,z) bind(c,name="dot_c")
          integer,parameter::byte=C_DOUBLE_COMPLEX
          complex(kind=byte),dimension(3),intent(in)::x,y
          complex(kind=byte),intent(out)::z
          z=sum(x*y)
        end subroutine
        subroutine dot(a,b,c) bind(c,name="dot")
          integer,parameter::byte=C_DOUBLE
          real(kind=C_DOUBLE),dimension(3),intent(in)::a,b
          real(kind=C_DOUBLE),intent(out)::c
          c=sum(a*b)
        end subroutine
        subroutine addtwofc(x,y,z) bind(c,name="add_c")
          integer,parameter::byte=C_DOUBLE_COMPLEX
          complex(kind=byte),intent(in)::x,y
          complex(kind=byte),intent(out)::z
          z=x+y 
        end subroutine
        subroutine takefc(x,y,z) bind(c,name="take_c")
          integer,parameter::byte=C_DOUBLE_COMPLEX
          complex(kind=byte),intent(in)::x,y
          complex(kind=byte),intent(out)::z
          z=x-y 
        end subroutine
        subroutine addtwof(a,b,c) bind(c,name="add")
          integer,parameter::byte=C_INT
          integer(kind=byte),intent(in)::a,b
          integer(kind=byte),intent(out)::c
          c=a+b
        end subroutine
        subroutine substract(a,b,c) bind(c,name="take")
          integer,parameter::byte=C_INT
          integer(kind=byte),intent(in)::a,b
          integer(kind=byte),intent(out)::c
          c=a-b
        end subroutine
      end module
