#!/usr/local/bin/python3

import os

root="/Users/qzmfrank/codes/zmake/src"

rootmk="""
################################################################################
#  A set of template files to build projects with a single Makefile
#  Copyright (C) 2013-2014 Zhongming Qu <qzmfrank@umich.edu>
#  
#  This program is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.
#  
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#  
#  You should have received a copy of the GNU General Public License
#  along with this program.  If not, see <http://www.gnu.org/licenses/>.  
################################################################################
ROOT		:=/Users/qzmfrank/codes/zmake/src# root of sources

#	MISC PROJECT INFO
CWD		:=$(shell pwd)# current working directory
BUILD		:=$(shell pwd)# out-of-source build directory
#QUIET		:=@
PROJECT_NAME	:=zmake
VERSION		:=v0.01
DATE_TIME	:=$(shell date "+%Y-%m-%d")
OS		:=$(shell uname -s)
ARCH		:=$(shell uname -m)
PLATFORM	:=${OS}-${ARCH}
RELEASE_NAME	:=${PROJECT_NAME}-${PLATFORM}-${VERSION}-${DATE_TIME}

#	PROJECT-WIDE COMMON COMPILING FLAGS 
CC		:=icc
CFLAGS 		:=-O3							\
		-Wall							\
		-prec-div -no-ftz					\
		-restrict						\
		-std=c99						\
		-openmp							\
		-Wno-deprecated

CXX		:=icpc
CXXFLAGS	:=-O3							\
		-Wall							\
		-prec-div -no-ftz					\
		-restrict						\
		-openmp							\
		-Wno-deprecated

		# 							\
		-DNDEBUG						\
		-MMD -MP						\
		-nostdinc++						\
		-fPIC							\
		-fno-inline-functions					\
		-unroll-aggressive					\
		-fno-math-errno						\
		-nostdinc 						\
		-DDEBUG							\
		-opt-report-phase ipo_inl				\
		-vec-report=1						\


DEPFLAGS	:=-MMD -MP# preprocessor generates .d files
ASMFLAGS	:=-S -fsource-asm# source code commented assembly code

#	PROJECT-WIDE INCLUDE AND LINKAGE OPTIONS
ifeq (${PLATFORM},Linux-x86_64)
	#	FFTW3 Library for Linux
	#FFTW_INCS	:=-I/opt/intel/mkl/include/fftw
	#FFTW_LIBS	:=-lfftw3
	FFTW_DIR	:=/opt/fftw/3.3.3
	FFTW_INCS	:=-I${FFTW_DIR}/include
	FFTW_LIBS	:=-L${FFTW_DIR}/lib -lfftw3 -lfftw3_omp
	#	Intel Math Kernel Library for Linux
	MKL_INCS	:=
	MKL_LIBS	:=-mkl
	#	OpenMP Flags
	OMP_INCS	:=
	OMP_LIBS	:=-openmp
	#	OpenMPI Library
	MPI_INCS	:=`mpicxx -showme:compile`
	MPI_LIBS	:=`mpicxx -showme:link`
	#	Install Directory of Mathematica
	#MATH_DIR	:=/opt/Wolfram/Mathematica/9.0
	#	MathLink for Linux
	#ML_DIR		:=${MATH_DIR}/SystemFiles/Links/MathLink/DeveloperKit/Linux-x86-86/CompilerAdditions
	#ML_INCS		:=-I${ML_DIR}
	#ML_LIBS		:=-L${ML_DIR} -lML64i3
	#MPREP		:=${ML_DIR}/mprep
	#MCC		:=${ML_DIR}/mcc
	###	LibraryLink for MacOSX-x86-64
	#MLL_INCS	:=-I${MATH_DIR}/SystemFiles/IncludeFiles/C
	#MLL_LIBS	:=-L${MATH_DIR}/SystemFiles/Libraries/Linux-x86-64 -lWolframRTL
endif
ifeq (${PLATFORM},Darwin-x86_64)
	#	FFTW3 Library for MacOSX-x86-64
	FFTW_DIR	:=/opt/fftw/3.3.3
	FFTW_INCS	:=-I${FFTW_DIR}/include
	FFTW_LIBS	:=-L${FFTW_DIR}/lib -lfftw3 -lfftw3_omp
	#	Intel Math Kernel Library for MacOSX-x86-64
	#MKL_INCS	:=-iquote /opt/intel/include
	MKL_LIBS	:=-mkl
	#	OpenMP Flags
	OMP_INCS	:=
	OMP_LIBS	:=-openmp
	#	OpenMPI Library
	MPI_INCS	:=`mpicxx -showme:compile`
	MPI_LIBS	:=`mpicxx -showme:link`
	#	MathLink for MacOSX-x86-64
	ML_DIR		:=/Applications/Mathematica.app/SystemFiles/Links/MathLink/DeveloperKit/MacOSX-x86-64/CompilerAdditions/
	ML_INCS		:=-I${ML_DIR}
	ML_LIBS		:=-L${ML_DIR} -lMLi3 -lstdc++ -framework Foundation
	#MPREP		:=${ML_DIR}/mprep
	#	LibraryLink for MacOSX-x86-64
	#MLL_INCS	:=-I/Applications/Mathematica.app/SystemFiles/IncludeFiles/C/
	#MLL_LIBS	:=-L/Applications/Mathematica.app/SystemFiles/Libraries/MacOSX-x86-64/
endif
#PROJECT-WIDE DEFAULT LINKING LIBRARIES AND INCLUDE DIRECTORIES
INCS		:=${FFTW_INCS} ${MKL_INCS} ${OMP_INCS} ${MPI_LIBS}
LIBS		:=${FFTW_LIBS} ${MKL_LIBS} ${OMP_LIBS} ${MPI_LIBS} 








################################################################################
#		INTERNAL VARIABLES
OBJ		:=# .o files
DEP		:=# .d files
ASM		:=# .s files
################################################################################
# 		UNDEFINE DEFAULT PATTERN RULES
.SUFFIXES:
.SUFFIXES: .c .cpp .o .so .dylib .exe .d .s .S .txt .log 
################################################################################
#		COLORFUL SHELL ECHO!
NONE		:=\033[00m 
#	normal colors
BLACK		:=\033[00;30m
RED		:=\033[00;31m
GREEN		:=\033[00;32m
BROWN		:=\033[00;33m 
BLUE		:=\033[00;34m
MAGENTA		:=\033[00;35m
CYAN		:=\033[00;36m
GREY		:=\033[00;37m 
#	bold
B_BLACK		:=\033[01;30m
B_RED		:=\033[01;31m
B_GREEN		:=\033[01;32m
B_BROWN		:=\033[01;33m 
B_BLUE		:=\033[01;34m
B_MAGENTA	:=\033[01;35m
B_CYAN		:=\033[01;36m
B_GREY		:=\033[01;37m 
#	underlined
U_BLACK		:=\033[04;30m
U_RED		:=\033[04;31m
U_GREEN		:=\033[04;32m
U_BROWN		:=\033[04;33m 
U_BLUE		:=\033[04;34m
U_MAGENTA	:=\033[04;35m
U_CYAN		:=\033[04;36m
U_GREY		:=\033[04;37m 
#	blinking
BLK_BLACK	:=\033[05;30m
BLK_RED		:=\033[05;31m
BLK_GREEN	:=\033[05;32m
BLK_BROWN	:=\033[05;33m 
BLK_BLUE	:=\033[05;34m
BLK_MAGENTA	:=\033[05;35m
BLK_CYAN	:=\033[05;36m
BLK_GREY	:=\033[05;37m 
#	reversed foreground and background color
REV_BLACK	:=\033[07;30m
REV_RED		:=\033[07;31m
REV_GREEN	:=\033[07;32m
REV_BROWN	:=\033[07;33m 
REV_BLUE	:=\033[07;34m
REV_MAGENTA	:=\033[07;35m
REV_CYAN	:=\033[07;36m
REV_GREY	:=\033[07;37m 


"""

for t in os.walk(root):
    print(t)
#for path,dirs,files in os.walk(root):
    #for file in files:
        #fname = os.path.join(path,file)
        #print(os.path.dirname(fname))
