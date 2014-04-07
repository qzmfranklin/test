EXE:=mnum.exe

check: ${EXE}
	./$<

%.exe: %.cpp
	icpc -o $@ $^ 
