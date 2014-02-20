CXX:=icpc
CXXFLAGS:=-O3 -MMD -MP -restrict
INCS:=
LIBS:=

-include heap.d
-include test_heap.d
-include tree.d
-include test_tree.d

all: test_heap.o heap.o test_tree.o tree.o

check: test_heap.txt test_tree.txt

clean:
	rm -f *.o *.d
cleanxx:
	rm -f *.o *.d *.exe 

%.txt: %.exe
	./$< > $@

test_%.exe: test_%.o %.o
	${CXX} $^ -o $@ ${LIBS}

%.o: %.cpp
	${CXX} -c $< -o $@ ${CXXFLAGS} ${INCS} 
