#include "unity.h"

#include "main.c"

#include "gardener.h"

void test_main(void) {

  main__();
  TEST_PASS_MESSAGE("cmock is working.\n");
}

/* #define main main */
#undef main
