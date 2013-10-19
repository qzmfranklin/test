CC=icc
CCflag=-Wall -profile-functions -profile-loops=all -profile-loops-report=2
exe=main

.PHONY: clean cleanall

${exe}: main.o
	${CC} ${CCflag} -o $@ $^
main.o: main.c
	${CC} ${CCflag} -c $^
clean:
	rm -rf *.o *.xml *.dump
cleanall: clean
	rm -rf ${exe}
