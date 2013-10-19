CC=clang
CCFLAGS=-Wall -Werror -O3
SHAREDLIB=-dynamiclib -fPIC
STATICLIB=-staticlib -fpic
LibraryLinkINC=-I/Applications/Mathematica.app/SystemFiles/IncludeFiles/C
LibraryLinkLIB=-L/Applications/Mathematica.app/SystemFiles/Libraries/MacOSX-x86-64/


.PHONY: all clean cleanxx
all: libmylib.dylib main.exe

main.exe: main.o libmylib.dylib 
	${CC} ${CCFLAGS} ${LibraryLinkINC} ${LibraryLinkLIB} $^ -o $@
main.o: main.c
	${CC} ${CCFLAGS} ${LibraryLinkINC} ${LibraryLinkLIB} $^ -o $@
libmylib.dylib: mylib.c
	${CC} ${CCFLAGS} ${SHAREDLIB} ${LibraryLinkINC} ${LibraryLinkLIB} $^ -o $@
clean:
	rm -f *.o
cleanxx: clean
	rm -rf *.dylib *.a *.so *.exe
