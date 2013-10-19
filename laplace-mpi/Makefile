MPIF90=mpif90
MPIFFLAGS=-warn all -fpp
MKLLIBS=-mkl

.PHONY: all clean cleanx cleanxx

all: main.exe array_mpi.exe

%.exe: %.o
	${MPIF90} ${MPIFFLAGS} $^ -o $@ ${MKLLIBS}
%.o: %.f90
	${MPIF90} ${MPIFFLAGS} -c $^ -o $@ ${MKLLIBS}
clean:
	rm -rf *.o
cleanxx: clean
	rm -rf *.exe 
