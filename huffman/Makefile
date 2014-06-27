CXX:=gcc
CXXFLAGS:=-O3 -MMD -MP -Drestrict=__restrict__
INCS:=
LIBS:=


all: listchar.exe

clean:
	rm -f *.o *.d *.exe

%.exe: %.o
	${CXX} $^ -o $@ ${LIBS}

%.o: %.cpp
	${CXX} -c $< -o $@ ${CXXFLAGS} ${INCS} 
