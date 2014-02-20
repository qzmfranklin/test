EXE:=diffpar.exe


all: ${EXE}

check: ${EXE}
	./$<

%.exe: %.c
	icpc -o $@ $^ -std=c99

clean:
	rm -f *.o
cleanxx:
	rm -f *.o ${EXE}

