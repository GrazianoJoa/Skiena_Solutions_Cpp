#include "test.h"

TestContext test_ctx = {0, 0, 0, 0};

void t_stack_test_create_destroy(void);
void t_stack_test_push_peek(void);
void t_stack_test_pop_empty(void);
void t_linked_list_create_destroy(void);

int main() {
   RUN_TEST(t_stack_test_create_destroy);
   RUN_TEST(t_stack_test_push_peek);
   RUN_TEST(t_stack_test_pop_empty);
   RUN_TEST(t_linked_list_create_destroy);
   test_report();
}
