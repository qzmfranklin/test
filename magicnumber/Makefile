EXE:=mnum.exe

check: ${EXE}
	./$<

%.exe: %.cpp
	@icpc -o $@ $^ 

clean:
	rm *.exe *.s *.log *.o
