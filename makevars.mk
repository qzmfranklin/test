ifdef NOINLINE
	NOINLINEOPT := -fno-inline-functions
endif 
ifdef UNIVERSAL_BINARY
	FPIC := -fPIC
endif 
###############################################################################
CC	:=icc
CXX	:=icpc
CFLAGS 	:=-Wall -O3					\
	${FPIC}						\
	${NOINLINEOPT}					\
	-prec-div -no-ftz				\
	-restrict
CXXFLAGS:=${CFLAGS}
OBJFLAGS:=-c -MD -MP
ASMFLAGS:=-S -fsource-asm
# Intel Math Kernel Library
MKL_INCS:= 
MKL_LIBS:=-mkl 
# MathLink include and library
ML_DIR	:=/Applications/Mathematica.app/SystemFiles/Links/MathLink/DeveloperKit/MacOSX-x86-64/CompilerAdditions
ML_INCS	:=-I${ML_DIR}
ML_LIBS	:=-L${ML_DIR} -lMLi3 -lstdc++ -framework Foundation 
MPREP	:=${ML_DIR}/mprep
# LibraryLink include and library
MLL_INCS:=-I/Applications/Mathematica.app/SystemFiles/IncludeFiles/C 
MLL_LIBS:=-L/Applications/Mathematica.app/SystemFiles/Libraries/MacOSX-x86-64/
# The default empty include directories and 
# linking libraries for specific directories
INCS	:=
LIBS	:= 
###############################################################################
.PHONY:
.PHONY: all 						\
	clean cleanx cleanxx 				\
	install uninstall				\
	test 
clean:
	rm -rf *.o *_tm.c a.out *.d
cleanx: clean
	rm -rf log *.s
cleanxx: cleanx
	rm -rf *.dylib *.so *.a *.exe a.out 
############################################################################### 
.SUFFIXES:
.SUFFIXES: .tm .c .cpp .o .exe .s .d
%.exe: %.o 
	$(CXX) -o $@ $(filter %.o,$^) ${INCS} $(LIBS)
%.dylib: %.o
	$(CXX) -o $@ $(filter %.o,$^) ${INCS} $(LIBS)
%.a: %.o
	$(CXX) -o $@ $(filter %.o,$^) ${INCS} $(LIBS)
%.o: %.cpp
	$(CXX) -o $@ $(CXXFLAGS) ${INCS} ${OBJFLAGS} $<
%.s: %.cpp
	$(CXX) -o $@ $(CXXFLAGS) ${INCS} ${ASMFLAGS} $< 
%.o: %.c
	$(CC) -o $@ $(CFLAGS) ${INCS} ${OBJFLAGS} $<
%.s: %.c 
	$(CC) -o $@ $(CFLAGS) ${INCS} ${ASMFLAGS} $< 
