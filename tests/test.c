#include "test.h"
#include "data_structures/stack_test.h"
#include "data_structures/linked_list_test.h"
#include "data_structures/hash_map_test.h"
#include "data_structures/binary_search_tree_test.h"

TestContext test_ctx = {0, 0, 0, 0};

int main() {
  // STACK TEST
  RUN_TEST(t_stack_create_destroy);
  RUN_TEST(t_stack_push);
  RUN_TEST(t_stack_pop_ret);

  RUN_TEST(t_stack_not_init);
  RUN_TEST(t_stack_pop_is_empty);
  RUN_TEST(t_stack_peek_null);
  RUN_TEST(t_stack_complex);

  // LINKED LIST TEST
  RUN_TEST(t_linked_list_create_destroy);
  RUN_TEST(t_linked_list_push);
  RUN_TEST(t_linked_list_odt_behavior);

  // HASH MAP TEST
  RUN_TEST(t_hash_map_create_destroy);

  // BINARY SEARCH TREE TEST
  RUN_TEST(t_binary_search_tree_create_destroy);
  
  test_report();
}
