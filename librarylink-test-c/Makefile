#CC=clang
CC=icc
CCFLAGS=-Wall -Werror -O3
SHAREDLIB=-dynamiclib -fPIC
STATICLIB=-staticlib -fpic
LibraryLinkINC=-I/Applications/Mathematica.app/SystemFiles/IncludeFiles/C
LibraryLinkLIB=-L/Applications/Mathematica.app/SystemFiles/Libraries/MacOSX-x86-64/


.PHONY: all clean cleanxx
all: libmylib.dylib

libmylib.dylib: mylib.o
	${CC} ${CCFLAGS} ${SHAREDLIB} ${LibraryLinkLIB} $^ -o $@
mylib.o: mylib.c
	${CC} -c ${CCFLAGS} -fpic ${LibraryLinkINC} $^ -o $@
clean:
	rm -f *.o
cleanxx: clean
	rm -rf *.dylib *.a *.so *.exe
