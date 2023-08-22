CC ?= gcc
export BUILD_DIR ?= ./build
export SRC_DIR ?= ./src
export TEST_DIR ?= ./test
export TEST_BUILD_DIR ?= ${BUILD_DIR}/test
export CMOCK_DIR ?= ./cmock
export UNITY_DIR ?= ./cmock/vendors/unity
TEST_MAKEFILE = ${TEST_BUILD_DIR}/MakefileTestSupport
OBJ ?= ${BUILD_DIR}/obj
OBJ_DIR = ${OBJ}

default: all

all: setup test ${BUILD_DIR}/main run

setup:
	mkdir -p ${BUILD_DIR}
	mkdir -p ${OBJ}
	ruby ./cmock/scripts/create_makefile.rb --silent

clean:
	rm -rf ${BUILD_DIR}

${BUILD_DIR}/main: ${SRC_DIR}/gardener.c ${SRC_DIR}/gardener.h
	${CC} $< -o $@

run:
	./build/main || true

test: setup

-include ${TEST_MAKEFILE}
