-include ../makevars.mk
############################################################################### 
#CXX:=c++
INCS:=${INCS} ${MKL_INCS}
LIBS:=${LIBS} ${MKL_LIBS}
############################################################################### 

test: test.exe
	./$< 
test.exe: test.o 
#test.o: test.cpp
-include svd-test.d 
