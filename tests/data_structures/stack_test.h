#pragma once

#include "test.h"
#include "stack.h"
#include <stdlib.h>

// BASE CASES

TEST(t_stack_create_destroy) {
  Stack* st = stack_create(sizeof(int), 2, NULL, NULL);
  ASSERT_TRUE(st != NULL);

  stack_destroy(&st);
  ASSERT_TRUE(st == NULL);
}

TEST(t_stack_push) {
  Stack* st = stack_create(sizeof(int), 2, NULL, NULL);
  
  int num = 20;
  stack_push(st, &num);
  ASSERT_TRUE(stack_is_empty(st) == false);

  stack_destroy(&st);
}

TEST(t_stack_pop_ret) {
  Stack* st = stack_create(sizeof(int), 2, NULL, NULL);

  int num = 10;
  int num_b;
  stack_push(st, &num);
  stack_pop(st, &num_b);

  ASSERT_TRUE(num == num_b);
}

typedef struct Pointer {
  int* p;
} Pointer;

void copy_pointer(void* dst, void* src) {
  Pointer* d = (Pointer*)dst;
  Pointer* s = (Pointer*)src;

  if (!s->p) {
    d->p = NULL;
    return;
  }

  d->p = malloc(sizeof(int));
  if (!d->p) {
    d->p = NULL;
    return;
  }

  *(d->p) = *(s->p);
}

void destroy_pointer(void* obj) {
  Pointer* o = (Pointer*)obj;
  free(o->p);
}

TEST(t_stack_complex) {
  Stack* st = stack_create(sizeof(Pointer), 2, copy_pointer, destroy_pointer);
  
  Pointer* p = malloc(sizeof(Pointer));
  p->p = malloc(sizeof(int));
  *(p->p) = 20;
  stack_push(st, p);
  ASSERT_TRUE(stack_is_empty(st) == false);
  free(p->p);
  free(p);

  Pointer* p_b = malloc(sizeof(Pointer));
  stack_peek(st, p_b);
  ASSERT_TRUE(*(p_b->p) == 20);

  stack_destroy(&st);
  ASSERT_TRUE(st == NULL);
  
  ASSERT_TRUE(*(p_b->p) == 20);
  free(p_b->p);
  free(p_b);
}

// CORNER CASES

TEST(t_stack_not_init) {
  Stack* st = NULL;
  int a = 20;
  int b;
  ASSERT_TRUE(stack_push(st, &a) == STACK_ERR_NULL);
  ASSERT_TRUE(stack_pop(st, NULL) == STACK_ERR_NULL);
  ASSERT_TRUE(stack_peek(st, &b) == STACK_ERR_NULL);
}

TEST(t_stack_pop_is_empty) {
  Stack* st = stack_create(sizeof(int), 2, NULL, NULL);
  ASSERT_TRUE(stack_pop(st, NULL) == STACK_ERR_EMPTY);
  stack_destroy(&st);
}

TEST(t_stack_peek_null) {
  Stack* st = stack_create(sizeof(int), 2, NULL, NULL);
  int* peek = NULL;
  ASSERT_TRUE(stack_peek(st, peek) == STACK_ERR_INVALID_ARG);
  stack_destroy(&st);
}
