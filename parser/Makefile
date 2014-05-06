exe:=parser.exe

cflags:=-O3 -Wall 			\
	-restrict			\
	-c

	#-DNDEBUG			\
	#-Drestrict=__restrict__		\

src:=opr_q.cpp opd_q.cpp opr_s.cpp opd_s.cpp



all: ${src:%.cpp=%.o}



check: ${exe}
	./$< < input.txt

#check: ${exe}
	#./$< < input.txt > output.txt
	#more output.txt

%.o: %.cpp
	icpc -o $@ $< ${cflags}

${exe}: ${exe:%.exe=%.o} ${src:%.cpp=%.o}
	icpc -o $@ ${filter %.o,$^} -O3 -Wall

clean:
	rm -f *.o *.exe *.d *.s
