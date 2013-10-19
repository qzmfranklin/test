CC=icc
CCflag=-Wall

F=ifort
Fflag=

exe=main

${exe}: main.o fmodule.o
	${CC} ${CCflag} -o $@ $^
main.o: main.c
	${CC} ${CCflag} -o $@ -c $^ 
fmodule.o: fmodule.f
	${F} ${Fflag} -o $@ -c $^
clean:
	rm -rf *.o
cleanall: clean
	rm -rf ${exe}

