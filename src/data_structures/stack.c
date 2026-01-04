#include "stack.h"

struct Stack {
    void* data;
    size_t elem_size;
    size_t capacity;
    size_t size;
};

// PUBLIC METHODS
Stack* stack_create(size_t capacity, size_t elem_size) {
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

    return s;
}

StackStatus stack_delete(Stack** s) {
    if (!s || !*s) return STACK_ERR_NULL;

    free((*s)->data);
    free(*s);

    *s = NULL;

    return STACK_OK;
}

StackStatus stack_push(Stack* s, const void* elem) {
    if (!s || !elem) return STACK_ERR_NULL;

    if (s->size == s->capacity) {
        if (stack_resize(s, s->capacity*2) == STACK_ERR_ALLOC_MEM) {
            return STACK_ERR_ALLOC_MEM;
        }
    }

    memcpy((char*)s->data + s->size * s->elem_size, elem, s->elem_size );

    s->size++;

    return STACK_OK;
}

StackStatus stack_pop(Stack* s, void* poped_elem) {
    if (!s || !poped_elem) return STACK_ERR_NULL;

    if (stack_is_empty(s)) return STACK_ERR_IS_EMPTY;

    s->size--;

    memcpy(poped_elem, (char*)s->data + s->size * s->elem_size, s->elem_size);
    
    return STACK_OK;
}

StackStatus stack_peek(Stack* s, void* peek_elem) {
    if (!s || !peek_elem) return STACK_ERR_NULL;

    if (stack_is_empty(s)) return STACK_ERR_IS_EMPTY;

    memcpy(peek_elem, (char*)s->data + (s->size-1) * s->elem_size, s->elem_size);

    return STACK_OK;
}

bool stack_is_empty(const Stack* s) {
    return s == NULL || s->size == 0;
}

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
