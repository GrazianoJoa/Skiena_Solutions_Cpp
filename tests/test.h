#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <stdio.h>

// TEST BASICS

typedef struct {
   int tests_run;
   int tests_failed;
   int assertions;
   const char* current_test;
} TestContext;

extern TestContext test_ctx;

#define TEST(name) void name(void)

#define RUN_TEST(test) do { \
   test_ctx.current_test = #test; \
   test_ctx.tests_run++; \
   test(); \
} while (0)

// TEST MACROS

#define ASSERT_TRUE(expr) do { \
   test_ctx.assertions++; \
   if (!(expr)) { \
      FAIL(#expr); \
   } \
} while (0)

// TEST REPORT MACROS

#define FAIL(msg) do { \
   printf("[FAILED] %s:%d  %s", __FILE__, __LINE__, msg); \
   test_ctx.tests_failed++; \
   return; \
} while (0)

static inline void test_report() {
   printf("\n--- TEST SUMMARY ---\n");
   printf("Tests run     : %d\n", test_ctx.tests_run);
   printf("Tests failed  : %d\n", test_ctx.tests_failed);
   printf("Assertions    : %d\n", test_ctx.assertions);
   if (test_ctx.tests_failed == 0)
      printf("ALL TESTS PASSED ✅\n");
}

#endif
