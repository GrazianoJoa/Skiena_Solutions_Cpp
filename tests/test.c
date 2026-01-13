#include "test.h"

TestContext test_ctx = {0, 0, 0, 0};

void stack_test_create_destroy(void);
void stack_test_push_peek(void);
void stack_test_pop_empty(void);

int main() {
   RUN_TEST(stack_test_create_destroy);
   RUN_TEST(stack_test_push_peek);
   RUN_TEST(stack_test_pop_empty);
   test_report();
}
