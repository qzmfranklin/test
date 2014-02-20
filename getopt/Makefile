EXE:=getopt.exe


all: ${EXE}

check: ${EXE}
	./$<

%.exe: %.c
	icc -o $@ $^ -std=c99

clean:
	rm -f *.o
cleanxx:
	rm -f *.o ${EXE}

