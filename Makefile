CC ?= gcc

export BUILD_DIR ?= ./build
export SRC_DIR ?= ./src
export TEST_DIR ?= ./test
export TEST_BUILD_DIR ?= ${BUILD_DIR}/test
export CMOCK_DIR ?= ./cmock
export UNITY_DIR ?= ./cmock/vendor/unity
export CMOCK_CONFIG=./cmock_config.yaml

TEST_MAKEFILE = ${TEST_BUILD_DIR}/MakefileTestSupport
OBJ ?= ${BUILD_DIR}/obj
OBJ_DIR = ${OBJ}

TEST_UNIT_PATH = ${TEST_BUILD_DIR}/$(TEST_UNIT)

default: all

all: setup test ${BUILD_DIR}/main run

setup:
	mkdir -p ${BUILD_DIR}	
	mkdir -p ${OBJ}
	ruby ./scripts/create_makefile.rb --silent

clean:
	rm -rf ${BUILD_DIR}

${BUILD_DIR}/main: ${SRC_DIR}/main.c ${SRC_DIR}/gardener.h ${SRC_DIR}/gardener.c ${SRC_DIR}/utils.h ${SRC_DIR}/utils.c
	${CC} $^ -o $@

run: ${BUILD_DIR}/main
	./build/main || true

# test: setup

-include ${TEST_MAKEFILE}

# required by gdb
TEST_CFLAGS += -g

# required to test static functions
LDFLAGS += -zmuldefs

test_summary: test
	cat ${TEST_BUILD_DIR}/*.testresult


memory_test: ${TEST_UNIT_PATH}
	  valgrind -s --tool=memcheck --track-origins=yes ${TEST_UNIT_PATH}

debug_test: ${TEST_UNIT_PATH}
	  gdb ${TEST_UNIT_PATH}


.PHONY: memory_test
.PHONY: debug_test
