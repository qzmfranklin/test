exe:=parser.exe

release:=-DNDEBUG

src:=opr_q.cpp opd_q.cpp opr_s.cpp opd_s.cpp

all: ${src:%.cpp=%.o}

check: ${exe}
	./$< < input.txt

%.exe: %.cpp
	icpc -o $@ $^ -O3 -Wall

%.o: %.cpp
	icpc -o $@ -c $< -O3 -Wall ${release}

${exe}: ${exe:%.exe=%.o} ${src:%.cpp=%.o}
	icpc -o $@ $^ -O3 -Wall

clean:
	rm -f *.o *.exe *.d *.s
