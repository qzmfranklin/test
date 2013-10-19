
F=gfortran
EXE=main

.PHONY=clean
main: main.o inputs.o math.o
	${F} main.o inputs.o math.o -o ${EXE}
main.o: main.f90 inputs.o math.o
	${F} -c main.f90
inputs.o: inputs.f90 math.o
	${F} -c inputs.f90
math.o: math.f90
	${F} -c math.f90
clean:
	rm *.o *.mod

