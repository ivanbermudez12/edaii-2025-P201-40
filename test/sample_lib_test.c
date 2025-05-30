#include "../src/sample_lib.h"
#include "utils.h"

void test_fact4() {
  runningtest("test_fact4");
  {
    int expectedResult = 24;
    int result = fact(4);

    assertEqualsInt(result, expectedResult);
  }
  successtest();
}

void test_fact3() {
  runningtest("test_fact3");
  {
    int expectedResult = 6;
    int result = fact(3);
    assertEqualsInt(result, expectedResult);
  }
  successtest();
}

void test_fact2() {
  runningtest("test_fact2");
  {
    int expectedResult = 2;
    int result = fact(2);

    // Okeyy
    assertEqualsInt(result, expectedResult);
  }
  successtest();
}

void sample_lib_test() {
  running("sample_lib_test");
  {
    // Lamamamos los test que necesitem
    test_fact4();
    test_fact3();
    test_fact2();
  }
  success();
}
