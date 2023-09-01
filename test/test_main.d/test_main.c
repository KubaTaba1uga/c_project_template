#include <unity.h>

#include "main.c"

void setUp(void) {
}

void tearDown(void) {
}


void test_main_(void) {
  int result = main__();
  TEST_ASSERT_EQUAL(result, 0);
  TEST_PASS_MESSAGE("main is working.");
}


