EXE:=helloworld.exe

CXX:=icpc
CXXFLAGS:=-Wall `mpic++ -showme:compile`
#INCS:=-I/opt/openmpi/1.6.5/include
LIBS:=`mpic++ -showme:link`
MPIRUN=/usr/bin/mpirun

all: ${EXE}

check: ${EXE}
	${MPIRUN} -np 3 $<

%.exe: %.cpp
	${CXX} -o $@ $^ ${CXXFLAGS} ${INCS} ${LIBS}

clean:
	rm -f *.o
cleanxx:
	rm -f *.o ${EXE} 
