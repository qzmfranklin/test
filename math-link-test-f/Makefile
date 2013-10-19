CC=icc
CCflag=-Wall -O0
F=ifort
Fflag=-warn all -O0

MPREP=mprep
ML_libs=-lMLi3 -lstdc++ -framework Foundation 

F_module_f=fmodule.f
F_module_o=fmodule.o

exe=addtwo sumv dot test
#exe= test

.PHONY:clean cleanall

all : ${exe}

# ML-C
addtwo : addtwotm.c addtwo.c
	${CC} ${CCflag} ${ML_libs} -o $@ $^
addtwotm.c : addtwo.tm
	${MPREP} $? -o $@

sumv : sumvtm.c sumv.c
	${CC} ${CCflag} ${ML_libs} -o $@ $^
sumvtm.c : sumv.tm
	${MPREP} $? -o $@

# ML-C-F
dot : dottm.c dot.c ${F_module_o}
	${CC} ${CCflag} ${ML_libs} -o $@ $^
dottm.c : dot.tm
	${MPREP} $? -o $@

# C-F test
test : test.c ${F_module_o}
	${CC} ${CCflag} -o $@ $^

# F module
${F_module_o} : ${F_module_f}
	${F} ${Fflag} -c $^ -o $@

# clean up
clean :
	rm -rf *.o *tm.c
cleanall: clean
	rm -rf ${exe}
