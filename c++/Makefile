EXE:=test.exe
SRC:=Vector.cpp Matrix.cpp

all: ${EXE} ${SRC:%.cpp=%.o} ${EXE:%.exe=%.o}

check: ${EXE}
	./$<

%.exe: %.o ${SRC:%.cpp=%.o}
	icpc -o $@ $^ -mkl

%.o: %.cpp
	icpc -c $<

clean:
	rm -f *.o
cleanxx:
	rm -f *.o ${EXE}
