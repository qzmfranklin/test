CXX:=icpc
CXXFLAGS:=-O3 -MMD -MP -restrict
INCS:=
LIBS:=

-include test_pipe.d

check: test_pipe.txt

clean:
	rm -f *.o *.d
cleanxx:
	rm -f *.o *.d *.exe 

%.txt: %.exe
	./$<

test_%.exe: test_%.o
	${CXX} $^ -o $@ ${LIBS}

%.o: %.cpp
	${CXX} -c $< -o $@ ${CXXFLAGS} ${INCS} 
