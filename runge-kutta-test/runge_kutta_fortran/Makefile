F90=ifort
F90FLAGS=-warn all -O3 -fpp

.PHONY: all clean cleanxx

all: runge_kutta.exe

runge_kutta.exe: runge_kutta.o
	${F90} ${F90FLAGS} $^ -o $@
runge_kutta.o: runge_kutta.f90
	${F90} ${F90FLAGS} -c $^ -o $@
clean:
	rm -rf *.o
cleanxx: clean
	rm -rf *.exe 
