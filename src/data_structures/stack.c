#include "stack.h"
#include "utils.h"
#include <stdio.h>

struct Stack {
    void* data;
    size_t elem_size;
    size_t capacity;
    size_t size;

    copy_fn copy;
    destroy_fn destroy;
};


// PRIVATE METHODS

static StackStatus stack_resize(Stack* s, size_t new_capacity) {
    if (!s) return STACK_ERR_NULL;

    if (new_capacity == 0) return STACK_ERR_ALLOC_MEM;

    void* tmp = realloc(s->data, new_capacity * s->elem_size);

    if (!tmp) return STACK_ERR_ALLOC_MEM;

    s->data = tmp;
    s->capacity = new_capacity;
    return STACK_OK;
}

// PUBLIC METHODS

Stack* stack_create(size_t elem_size, size_t capacity, copy_fn copy, destroy_fn destroy) {
    if (capacity == 0 || elem_size == 0) return NULL;

    Stack* s = malloc(sizeof(Stack));

    if (!s) return NULL;

    s->data = malloc(capacity * elem_size);

    if (!s->data) {
        free(s);
        return NULL;
    }

    s->capacity = capacity;
    s->elem_size = elem_size;
    s->size = 0;

    s->copy = copy;
    s->destroy = destroy;

    return s;
}

void stack_destroy(Stack** s) {
    if (!s || !*s) return;

    if ((*s)->destroy) {
      for (size_t i = 0; i < (*s)->size; i++) {
        (*s)->destroy((char*)(*s)->data + i * (*s)->elem_size);
      }
    } 
    free((*s)->data);
    free(*s);

    *s = NULL;
}

StackStatus stack_push(Stack* s, void* elem) {
    if (!s) return STACK_ERR_NULL;
    if (!elem && !s->copy) return STACK_ERR_INVALID_ARG;

    if (s->size == s->capacity) {
        if (stack_resize(s, s->capacity*2) != STACK_OK) {
            return STACK_ERR_ALLOC_MEM;
        }
    }

    char* src = (char*)s->data + s->size * s->elem_size;

    if (s->copy) {
      s->copy(src, elem);
    } else {
      memcpy(src, elem, s->elem_size);
    }

    s->size++;

    return STACK_OK;
}

StackStatus stack_pop(Stack* s, void* pop) {
    if (!s) return STACK_ERR_NULL;

    if (stack_is_empty(s)) return STACK_ERR_EMPTY;

    s->size--;

    char* src = (char*)s->data + s->size * s->elem_size;
  
    if (pop) {
      if (s->copy) {
        s->copy(pop, src);
      } else {
        memcpy(pop, src, s->elem_size);
      }
    }

    if (s->destroy) {
      s->destroy(src);
    }

    return STACK_OK;
}

StackStatus stack_peek(Stack* s, void* peek) {
    if (!s) return STACK_ERR_NULL;
    if (!peek) return STACK_ERR_INVALID_ARG;

    if (stack_is_empty(s)) return STACK_ERR_EMPTY;

    char* src = (char*)s->data + (s->size -1) * s->elem_size;

    if (s->copy) {
      s->copy(peek, src);
    } else {
      memcpy(peek, src, s->elem_size);
    }

    return STACK_OK;
}

bool stack_is_empty(const Stack* s) {
    return s == NULL || s->size == 0;
}

