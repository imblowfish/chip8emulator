# Project setups
TARGET=main.exe
OBJ_DIR=./obj
BUILD_DIR=./bin
SRC_DIR=./src

# Compiler options
CXX=g++
CXX_FLAGS=-fPIC -Wall -Wextra

# Includes
INC_PATH=\
-I./include

# Sources
SRC=${wildcard ${SRC_DIR}/*.cpp}

# Objects
OBJS=${SRC:${SRC_DIR}/%.cpp=${OBJ_DIR}/%.o}

all: ${OBJS}
	@echo Building...
	${CXX} ${CXX_FLAGS} ${INC_PATH} ${OBJS} -o ${BUILD_DIR}/${TARGET}
	@echo Building done

${OBJ_DIR}/%.o: ${SRC_DIR}/%.cpp
	${CXX} ${CXX_FLAGS} -c -o $@ $<

run:
	${BUILD_DIR}/${TARGET}

build_and_run: all run

clean:
	del /S /q .\obj\*


