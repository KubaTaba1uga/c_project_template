#include <unity.h>

#include "main.c"

void setUp(void) {
}

void tearDown(void) {
}


void test_main_(void) {
  main__();
  TEST_PASS_MESSAGE("cmock is working.\n");
}


