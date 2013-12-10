CC=icpc
CCflag=-Wall -mkl

.PHONY: all clean cleanxx

all: main.exe 
main.exe: main.o
	${CC} ${CCflag} -o $@ $^
main.o: main.cpp
	${CC} ${CCflag} -o $@ -c $^ 
clean:
	rm -rf *.o
cleanxx: clean
	rm -rf *.exe 
