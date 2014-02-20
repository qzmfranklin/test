################################################################################
#			CHOOSING COMPILERS
#SET(ENV{CC} "icc")
#SET(ENV{CXX} "icpc")
set(CMAKE_C_COMPILER "icc")
set(CMAKE_CXX_COMPILER "icpc")
################################################################################ 
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(rte2dvis)

SET(INCLUDE_DIR include)
SET(BIN_DIR bin)
SET(RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})
#SET(EXECUTABLE_OUTPUT_PATH ${BIN_DIR})

INCLUDE_DIRECTORIES(${INCLUDE_DIR})

ADD_SUBDIRECTORY(src bin)
