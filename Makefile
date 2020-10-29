# Project setups
TARGET=main.exe
BUILD_DIR=./bin
SRC_DIR=./src

# Compiler options
CXX=g++
CXX_FLAGS=-fPIC -Wall -Wextra -Werror

# Includes
INC_PATH=-I./include
TMP_INC=${shell dir .\include /s /b /ad}
INC_PATH+=${TMP_INC:%=-I./include/%}

# Sources
SRC=${shell dir .\src\*.cpp /s /b /a-d}

# Objects
OBJS=${SRC:%.cpp=%.o}

.PHONY: all
all: ${OBJS}
	@echo Building...
	${CXX} ${OBJS} ${INC_PATH} ${CXX_FLAGS} -o ${BUILD_DIR}/${TARGET}
	@echo Building done

%.o: %.cpp
	${CXX} ${INC_PATH} ${CXX_FLAGS} -c -o $@ $<

run:
	${BUILD_DIR}/${TARGET}

build_and_run: all run

clean:
	del /S /q ${OBJS}


