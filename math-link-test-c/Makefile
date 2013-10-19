# Mathematica Example
#MLINKDIR = /Applications/Mathematica.app/SystemFiles/Links/MathLink/DeveloperKit
#SYS = MacOSX-x86-64
#CADDSDIR = ${MLINKDIR}/${SYS}/CompilerAdditions
#INCDIR = ${CADDSDIR}
#LIBDIR = ${CADDSDIR}
#MPREP = ${CADDSDIR}/mprep
#EXTRA_LIBS = -lstdc++ -framework Foundation

#.PHONY:clean
#addtwo : addtwotm.o addtwo.o
	#${CC} -I${INCDIR} addtwotm.o addtwo.o -L${LIBDIR} -lMLi3 ${EXTRA_LIBS} -o $@
#addtwotm.c : addtwo.tm
	#${MPREP} $? -o $@
#.c.o :
	#${CC} -c -I%{INCDIR} $<
#clean :
	#rm -rf *.o addtwo *tm.c

CC=icc
MPREP=mprep

EXTRA_LIBS = -lMLi3 -lstdc++ -framework Foundation
.PHONY:clean cleanxx
all : addtwo.exe sumv.exe
addtwo.exe : addtwo_tm.o addtwo.o
	${CC} $^ ${EXTRA_LIBS} -o $@
addtwo_tm.c: addtwo.tm
	${MPREP} $^ -o $@

sumv.exe : sumv_tm.o sumv.o
	${CC} $^ ${EXTRA_LIBS} -o $@
sumv_tm.c: sumv.tm
	${MPREP} $^ -o $@

%.o: %.c
	${CC} -c $^ -o $@

clean :
	rm -rf *.o *_tm.c
cleanxx: clean
	rm -rf *.exe
