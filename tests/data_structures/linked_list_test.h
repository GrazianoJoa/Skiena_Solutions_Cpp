#pragma once

#include "test.h"
#include "linked_list.h"
#include "comparators.h"

// BASE CASES

TEST(t_linked_list_create_destroy) {
    LinkedList* list = linked_list_create(sizeof(int), NULL, NULL, compare_int);
    ASSERT_TRUE(list != NULL);

    linked_list_destroy(&list);
    ASSERT_TRUE(list == NULL);
}

TEST(t_linked_list_push) {
  LinkedList* list = linked_list_create(sizeof(int), NULL, NULL, compare_int);
  
  int a = 20;
  linked_list_push(list, &a);
  ASSERT_TRUE(linked_list_g_size(list) == 1);
  
  linked_list_destroy(&list);
}

struct Vector2D {
  int x;
  int y;
};

int cmp_vector2d(const void* a, const void* b) {
  struct Vector2D* vec_a = (struct Vector2D*)a;
  struct Vector2D* vec_b = (struct Vector2D*)b;
  double la = vec_a->x * vec_a->x + vec_a->y * vec_a->y;
  double lb = vec_b->x * vec_b->x + vec_b->y * vec_b->y;
  return (la > lb) - (la < lb);
}

TEST(t_linked_list_odt_behavior) {
    // CREATING ODT LINKED LIST
    LinkedList* list = linked_list_create(sizeof(struct Vector2D), NULL, NULL, cmp_vector2d);
    ASSERT_TRUE(list != NULL);

    // ADDING ELEMENT
    struct Vector2D v1 = {0,0};
    struct Vector2D v2 = {1,1};
    linked_list_push(list, &v1);
    linked_list_pushback(list, &v2);
    ASSERT_TRUE(linked_list_g_size(list) == 2);

    // DELETING ELEMENTlinked_list_delet
    linked_list_delete(list, &v2);
    ASSERT_TRUE(linked_list_g_size(list) == 1);

    // DESTROY LISTS
    linked_list_destroy(&list);
    ASSERT_TRUE(list == NULL);
}

