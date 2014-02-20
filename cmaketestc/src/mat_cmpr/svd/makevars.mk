###############################################################################
#  A set of template files to organize projects with a single Makefile
#  Copyright (C) 2013 Zhongming Qu <qzmfrank@umich.edu>
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
###############################################################################
#	Welcome! The comments in this file will guide you through the process.
#  Please read all the comments very carefully before changing anything.
#  	The idea of this set of template files (Makefile, Makefile.vars, and
#  all the makevars.mk) is to help organize any C/C++ project with a single
#  Makefile. 
#  	Usually the advantage of a single Makefile is speed and easy parallel
#  make. The usual drawbacks are bad maintainability and modularity. This 
#  set of files attempt to cut down all the repetitive work that are usually 
#  done manually, i.e., listing target-prerequisites, while preserving almost 
#  the same degree of modularity as that can be achieved through the recursive 
#  make approach.
#  	If you have any suggestions and/or ideas, please let me know.
###############################################################################
#				STEP 1
#DIRECTORY NAME FROM THE ROOT DIRECTORY
#	The ${DIR-mat_cmpr/svd} variable will be used through the rest of this 
#  makevars.mk file to achieve modularity.
#  	Be very careful:
# 		NO SPACE ( tab is OK )
# 		NO DEFERRED-EVALUATION ( always use colon-equal, i.e., := ) #
DIR-mat_cmpr/svd		:=src/mat_cmpr/svd# Please, NO SPACE 
# Quiet build for this dirctory. Comment the following to be verbose.
${DIR-mat_cmpr/svd}QUIET	:=@
###############################################################################
#				STEP 2
#DIRECTORY-SPECIFIC COMPILING AND LINKING OPTIONS
#
#	Options specified here are used in this directory. By default, all 
#  builds use the same options. When different compiling and/or linking options 
#  need to be assigned to different targets, the programmer needs to list all
#  the speical target-prerequisite dependencies manually.
#  	By default, the local options inherits the corresponding global ones 
#  from the Makefile.vars in the root directory. If one wishes to add any 
#  additional options that are specific to this very directory, add them after 
#  the global ones. For example:
# 	 	${DIR-mat_cmpr/svd}CFLAGS	:=${CFLAGS} [directory-specific options]
#  	Usually, ${DIR-mat_cmpr/svd}INCS and should not need to be modified if
#  the build in this directory does not require some extra libraries and/or 
#  hearder files. But in case it did, free at ease to modify these two 
#  variables.
${DIR-mat_cmpr/svd}CFLAGS 	:=${CFLAGS}
${DIR-mat_cmpr/svd}CXXFLAGS	:=${CXXFLAGS}
${DIR-mat_cmpr/svd}INCS		:=${INCS}
###############################################################################
#				STEP 3
#DIRECTORY-SPECIFIC SOURCE FILES
#
#  	Remember to add the ${DIR-mat_cmpr/svd}/ to whatever source files(s) you wish to add.
#  The dependencies are automatically resolved by the dependency files (*.d 
#  files) generated by the compiler through the -MD -MP and/or similar options.
#  Note that:
#  	a) The GNU make does NOT support recursive include directive. So we must
#  NOT include any *.d file in this file. All the *.d files are included in the
#  Makefile in the root directory AFTER all the makevars.mk's are include.
#  	b) So far, only supports C/C++ files. Maybe Fortran support is needed
#  	c) Please refrain from using $(wildcard) command. It only helps when not
#  really nessaccery and complicates the situation when we have forgotten about
#  it. Yes, be explicit. Manually list all the source files here.
#  	d) Dependencies are readily dealt with by the setup of the Makefile. One
#  Please, you NEVER need to specify the dependency for any .o file. Just list
#  the source files.
${DIR-mat_cmpr/svd}CFILES	:=	
${DIR-mat_cmpr/svd}CPPFILES	:=	${DIR-mat_cmpr/svd}/svd.cpp
################## DO NOT MODIFY ################
${DIR-mat_cmpr/svd}OBJFILES	:=	${${DIR-mat_cmpr/svd}CPPFILES:${DIR-mat_cmpr/svd}%.cpp=${BUILD}%.o}	\
				${${DIR-mat_cmpr/svd}CFILES:${DIR-mat_cmpr/svd}%.c=${BUILD}%.o}
${DIR-mat_cmpr/svd}DEPFILES	:=	${${DIR-mat_cmpr/svd}OBJFILES:%.o=%.d}
${DIR-mat_cmpr/svd}ASMFILES	:=	${${DIR-mat_cmpr/svd}OBJFILES:${BUILD}%.o=${ASM}%.s}
################## DO NOT MODIFY ################ 
###############################################################################
#				STEP 4
#DIRECTORY-SPECIFIC BINARY FILES
#
#	Executables listed in ${DIR}BINFILES are considered the final output of
#  this project. All of them should be built into ${BIN} instead of ${BUILD}
#  for all other executables. 
#  	So far, only supports CPP source files.
${DIR-mat_cmpr/svd}BIN	:=		
################## DO NOT MODIFY ################
${DIR-mat_cmpr/svd}BINCPP	:=		${${DIR-mat_cmpr/svd}BIN:%=${DIR-mat_cmpr/svd}/%.cpp}
${DIR-mat_cmpr/svd}BINOBJ	:=		${${DIR-mat_cmpr/svd}BINCPP:${DIR-mat_cmpr/svd}%.cpp=${BUILD}%.o}
${DIR-mat_cmpr/svd}BINDEP	:=		${${DIR-mat_cmpr/svd}BINOBJ:%.o=%.d}
${DIR-mat_cmpr/svd}BINEXE	:=		${${DIR-mat_cmpr/svd}BINOBJ:${BUILD}%.o=${BIN}%.exe}
${DIR-mat_cmpr/svd}BINASM	:=		${${DIR-mat_cmpr/svd}BINOBJ:${BUILD}%.o=${ASM}%.s}
################## DO NOT MODIFY ################
###############################################################################
#				STEP 5
#DIRECTORY-SPECIFIC TEST FILES

#	Speicify all the test files. All test files must be CPP files. But when
#  listing the them in ${DIR-mat_cmpr/svd}TST, do NOT write the .cpp extension. For example:
#  if one wishes to add test_mytest.cpp, he should write:
#
#  		${DIR-mat_cmpr/svd}TST:=test_mytest
#
#	Then list all the build rules right afterwards. For example:
#
#		${BUILD}/test_mytest.exe:	${BUILD}/test_mytest.o		\
#						${BUILD}/any-other-files.o
${DIR-mat_cmpr/svd}TST	:=		test_svd time_svd
${BUILD}/test_svd.exe: ${BUILD}/test_svd.o ${BUILD}/svd.o ${BUILD}/libutils.dylib
${BUILD}/time_svd.exe: ${BUILD}/time_svd.o ${BUILD}/svd.o ${BUILD}/libutils.dylib
################## DO NOT MODIFY ################
${DIR-mat_cmpr/svd}TSTCPP	:=		${${DIR-mat_cmpr/svd}TST:%=${DIR-mat_cmpr/svd}/%.cpp}
${DIR-mat_cmpr/svd}TSTOBJ	:=		${${DIR-mat_cmpr/svd}TSTCPP:${DIR-mat_cmpr/svd}%.cpp=${BUILD}%.o}
${DIR-mat_cmpr/svd}TSTDEP	:=		${${DIR-mat_cmpr/svd}TSTOBJ:%.o=%.d}
${DIR-mat_cmpr/svd}TSTEXE	:=		${${DIR-mat_cmpr/svd}TSTOBJ:%.o=%.exe}
${DIR-mat_cmpr/svd}TSTASM	:=		${${DIR-mat_cmpr/svd}TSTOBJ:${BUILD}%.o=${ASM}%.s}
SRCFILES	:=		${SRCFILES} ${${DIR-mat_cmpr/svd}CFILES} ${${DIR-mat_cmpr/svd}CPPFILES} ${${DIR-mat_cmpr/svd}TSTCPP} ${${DIR-mat_cmpr/svd}BINCPP}
DEPFILES	:=		${DEPFILES} ${${DIR-mat_cmpr/svd}DEPFILES} ${${DIR-mat_cmpr/svd}TSTDEP} ${${DIR-mat_cmpr/svd}BINDEP}
################## DO NOT MODIFY ################
###############################################################################
#				STEP 6
#	Write whatever special dependencies that do not fit into any pattern
#  rules here:






###############################################################################
###############################################################################
###############################################################################
#	Congratulations! You have completed everything you need to do to build
#  this directory. You do not need to modify this file unless some C and/or
#  CPP source files are added, removed, or renamed. In that case, just go over
#  STEP 1-6 again and it is done!
###############################################################################
###############################################################################
###############################################################################
#				WANRING
#  Please do not modify the following part if you are not 100% sure about it.
#  The design of this file is that one only needs to modify the part above.
#  If you find you need to modify any of the parts below, be very careful!
#				WANRING
###############################################################################
###############################################################################
############################################################################### 
#DIRECTORY-SPECIFIC PATTERN RULES
#
#	C++ linkage at the top level is done in the Makefile.vars in the root 
#  directory. Any special build rules for libraries and executables should be
#  secified in STEP 6 in this makevars.mk file.

#  C++ sources
${BUILD}/%.o: ${DIR-mat_cmpr/svd}/%.cpp
	@echo Compiling "${GREEN}$@${NONE}"...
	${${DIR-mat_cmpr/svd}QUIET}${CXX} -o $@ -c $< ${${DIR-mat_cmpr/svd}CXXFLAGS} ${${DIR-mat_cmpr/svd}INCS}
${ASM}/%.s: ${DIR-mat_cmpr/svd}/%.cpp
	@echo Generating "${CYAN}$@${NONE}"...
	${${DIR-mat_cmpr/svd}QUIET}${CXX} -o $@ $< ${ASMFLAGS} ${${DIR-mat_cmpr/svd}CXXFLAGS} ${${DIR-mat_cmpr/svd}INCS} 
#  C sources
${BUILD}/%.o: ${DIR-mat_cmpr/svd}/%.c
	@echo Compiling "${GREEN}$@${NONE}"...
	${${DIR-mat_cmpr/svd}QUIET}${CC} -o $@ -c $< ${${DIR-mat_cmpr/svd}CFLAGS} ${${DIR-mat_cmpr/svd}INCS}
${ASM}/%.s: ${DIR-mat_cmpr/svd}/%.c
	@echo Generating "${CYAN}$@${NONE}"...
	${${DIR-mat_cmpr/svd}QUIET}${CC} -o $@ $< ${ASMFLAGS} ${${DIR-mat_cmpr/svd}CFLAGS} ${${DIR-mat_cmpr/svd}INCS} 
#DIR-mat_cmpr/svdECTORY-SPECIFIC PHONY TARGETS
.PHONY: ${DIR-mat_cmpr/svd}-all ${DIR-mat_cmpr/svd}-test ${DIR-mat_cmpr/svd}-asm ${DIR-mat_cmpr/svd}-list
TARGET_ALL	:=${TARGET_ALL} ${DIR-mat_cmpr/svd}-all
TARGET_TEST	:=${TARGET_TEST} ${DIR-mat_cmpr/svd}-test
TARGET_ASM	:=${TARGET_ASM} ${DIR-mat_cmpr/svd}-asm
TARGET_LIST	:=${TARGET_LIST} ${DIR-mat_cmpr/svd}-list
${DIR-mat_cmpr/svd}-all: ${${DIR-mat_cmpr/svd}OBJFILES} ${${DIR-mat_cmpr/svd}BINEXE}
	@echo Finished building "${B_BLUE}$@${NONE}".
${DIR-mat_cmpr/svd}-test: ${${DIR-mat_cmpr/svd}TSTEXE}
	@echo Finished building "${B_BLUE}$@${NONE}".  
${DIR-mat_cmpr/svd}-asm: ${${DIR-mat_cmpr/svd}ASMFILES} ${${DIR-mat_cmpr/svd}TSTASM}
	@echo Finished generating "${B_BLUE}$@${NONE}".  
${DIR-mat_cmpr/svd}-list:
	@echo \#\#\#\#\#\#\#\#"${B_BROWN}BEGIN $@${NONE}"\#\#\#\#\#\#\#\#
	@echo "${BROWN}CFILES${NONE}":${${DIR-mat_cmpr/svd}CFILES}
	@echo "${BROWN}CPPFILES${NONE}":${${DIR-mat_cmpr/svd}CPPFILES}
	@echo "${BROWN}OBJFILES${NONE}":${${DIR-mat_cmpr/svd}OBJFILES}
	@echo "${BROWN}DEPFILES${NONE}":${${DIR-mat_cmpr/svd}DEPFILES}
	@echo "${BROWN}ASMFILES${NONE}":${${DIR-mat_cmpr/svd}ASMFILES}
	@echo "${BROWN}TSTCPP${NONE}":${${DIR-mat_cmpr/svd}TSTCPP}
	@echo "${BROWN}TSTOBJ${NONE}":${${DIR-mat_cmpr/svd}TSTOBJ}
	@echo "${BROWN}TSTDEP${NONE}":${${DIR-mat_cmpr/svd}TSTDEP}
	@echo "${BROWN}TSTEXE${NONE}":${${DIR-mat_cmpr/svd}TSTEXE}
	@echo "${BROWN}TSTASM${NONE}":${${DIR-mat_cmpr/svd}TSTASM} 
	@echo "${BROWN}BINCPP${NONE}":${${DIR-mat_cmpr/svd}BINCPP}
	@echo "${BROWN}BINOBJ${NONE}":${${DIR-mat_cmpr/svd}BINOBJ}
	@echo "${BROWN}BINDEP${NONE}":${${DIR-mat_cmpr/svd}BINDEP}
	@echo "${BROWN}BINEXE${NONE}":${${DIR-mat_cmpr/svd}BINEXE}
	@echo "${BROWN}BINASM${NONE}":${${DIR-mat_cmpr/svd}BINASM} 
	@echo \#\#\#\#\#\#\#\#"${B_BROWN}END $@${NONE}"\#\#\#\#\#\#\#\#
