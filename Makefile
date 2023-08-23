CC ?= gcc

export BUILD_DIR ?= ./build
export SRC_DIR ?= ./src
export TEST_DIR ?= ./test
export TEST_BUILD_DIR ?= ${BUILD_DIR}/test
export CMOCK_DIR ?= ./cmock
export UNITY_DIR ?= ./cmock/vendor/unity
export CMOCK_CONFIG=./config.yaml

TEST_MAKEFILE = ${TEST_BUILD_DIR}/MakefileTestSupport
OBJ ?= ${BUILD_DIR}/obj
OBJ_DIR = ${OBJ}

GARDENER_TEST = ${TEST_BUILD_DIR}/test_gardener


default: all

all: setup test ${BUILD_DIR}/main run

setup:
	mkdir -p ${BUILD_DIR}
	mkdir -p ${OBJ}
	ruby ./cmock/scripts/create_makefile.rb --silent

clean:
	rm -rf ${BUILD_DIR}

${BUILD_DIR}/main: ${SRC_DIR}/gardener.c ${SRC_DIR}/gardener.h ${SRC_DIR}/utils.c ${SRC_DIR}/utils.h
	${CC} $< -o $@

run:
	./build/main || true

test: setup

-include ${TEST_MAKEFILE}

test_summary: 
	cat ${TEST_BUILD_DIR}/*.testresult

# required by gdb
TEST_CFLAGS += -g
