CXX:=g++
CXXFLAGS:=-O3 -MMD -MP -Drestrict=__restrict__
INCS:=
LIBS:=

-include mergesort.d
-include test_mergesort.d

all: mergesort.exe
#check: test_mergesort.txt

clean:
	rm -f *.o *.d
cleanxx:
	rm -f *.o *.d *.exe 

%.txt: %.exe
	./$<

test_%.exe: test_%.o %.o
	${CXX} $^ -o $@ ${LIBS}

%.o: %.cpp
	${CXX} -c $< -o $@ ${CXXFLAGS} ${INCS} 
