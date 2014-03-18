CXX:=icc
CXXFLAGS:=-O3 -MMD -MP -restrict -std=c99
INCS:=
LIBS:=

SRC:=t_fork.c fork_whos_first.c

all: ${SRC:%.c=%.exe}

clean:
	rm -f *.o *.d
cleanxx:
	rm -f *.o *.d *.exe 

%.exe: %.o
	${CXX} $^ -o $@ ${LIBS}

%.o: %.c
	${CXX} -c $< -o $@ ${CXXFLAGS} ${INCS} 
