EXE:=plusminus toolbar menu message font-selection-dialog file-chooser-dialog

all: ${EXE}

%: %.c
	icc -o $@ $^ `pkg-config --libs --cflags gtk+-2.0`

clean:
	rm -f *.o
cleanxx:
	rm -f *.o ${EXE}
