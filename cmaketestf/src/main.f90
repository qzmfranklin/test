      program main
        use math
        use inputs
        implicit none

        integer(kind=byte), parameter   ::  Nm=20, Nd=2*Nm+1
        integer(kind=byte), parameter   ::  Ns=10, Nn=Ns, Ng=Nn*Nm

        real(kind=byte), dimension(-Nd:Nd) ::  gTbl
        real(kind=byte), dimension(Ns)  :: musTbl, muaTbl, mutTbl 
        integer(kind=byte)             ::  i, j, k, n, np, m, mp
        real(kind=byte), parameter     ::  g=0.7

        character(len=159)  ::  nodes_file  =&
                                    "/Users/qzmfrank/Codes/&
                                    cmaketest/mesh/trial_dat/nodes.dat"

        do m=-Nd,Nd
            gTbl(m) =   g**abs(m)
        end do
      contains

      end program main
