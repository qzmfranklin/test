CXX:=icpc
CXXFLAGS:=-O3 -MMD -MP -restrict
INCS:=
LIBS:=

-include heapsort.d
-include test_heapsort.d

check: test_heapsort.txt

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
