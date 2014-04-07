CXX:=icpc
CXXFLAGS:=-O3 -MMD -MP -restrict
INCS:=
LIBS:=

-include miss.d

%.exe: %.o %.o
	${CXX} $^ -o $@ ${LIBS}

%.o: %.cpp
	${CXX} -c $< -o $@ ${CXXFLAGS} ${INCS} 
