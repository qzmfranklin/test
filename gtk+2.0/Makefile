EXE:=simple center icon increment menu manymenu fancymenu \
	checkmenuitem toolbar undoredo simplesignal


.PHONY:


all: ${EXE}

clean:
	rm -f *.o
cleanxx:
	rm -f *.o ${EXE}

%: %.c
	icc -o $@ $^ `pkg-config --libs --cflags gtk+-2.0`
