#pragma once

#include "test.h"
#include "binary_search_tree.h"
#include "comparators.h"

TEST(t_binary_search_tree_create_destroy) {
  BinarySearchTree* bst = binary_search_tree_create(sizeof(int), NULL, NULL, compare_int);
  ASSERT_TRUE(bst != NULL);

  binary_search_tree_destroy(&bst);
  ASSERT_TRUE(bst == NULL);
}
