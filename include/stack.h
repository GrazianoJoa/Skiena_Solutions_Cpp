#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "utils.h"

typedef enum StackStatus {
    STACK_OK = 0,
    STACK_ERR_EMPTY,
    STACK_ERR_NULL,
    STACK_ERR_ALLOC_MEM,
    STACK_ERR_INVALID_ARG
} StackStatus;

typedef struct Stack Stack;

Stack* stack_create(size_t elem_size, size_t capacity, copy_fn copy, destroy_fn destroy);
void stack_destroy(Stack** stack);
StackStatus stack_push(Stack* stack, void* elem);
StackStatus stack_pop(Stack* stack, void* pop);
StackStatus stack_peek(Stack* stack, void* peek);
bool stack_is_empty(const Stack* s);

#endif
