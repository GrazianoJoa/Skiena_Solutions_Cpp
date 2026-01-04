#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef enum StackStatus {
    STACK_OK = 0,
    STACK_ERR_EMPTY,
    STACK_ERR_NULL,
    STACK_ERR_ALLOCATING_MEMORY,
} StackStatus;

typedef struct Stack Stack;

Stack* stack_create(Stack* stack, size_t capacity, size_t elem_size);
StackStatus stack_delete(Stack* stack);
StackStatus stack_push(Stack* stack, const void* elem);
StackStatus stack_pop(Stack* stack, void* poped_elem);
StackStatus stack_peek(Stack* stack, void* peek_elem);
bool stack_is_empty();


#endif
