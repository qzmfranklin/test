EXE:=main.exe

all: ${EXE}

check: ${EXE}
	./$< < input.txt

main.exe: main.cpp
	icpc -o $@ $^ -O3
