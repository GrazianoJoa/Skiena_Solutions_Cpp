#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stddef.h>
#include <stdbool.h>

typedef enum LinkedListStatus {
    LINKED_LIST_OK = 0,
    LINKED_LIST_ERR_NULL,
    LINKED_LIST_ERR_EMPTY,
    LINKED_LIST_ERR_INVALID_ARG,
    LINKED_LIST_ERR_ASSIGN_MEM
} LinkedListStatus;

typedef struct LinkedList LinkedList;

LinkedList* linked_list_create(size_t elem_size);
void linked_list_destroy(LinkedList** list);

LinkedListStatus linked_list_insert_at(LinkedList* list, size_t pos, void* elem);
LinkedListStatus linked_list_push(LinkedList* list, void* elem);
LinkedListStatus linked_list_pushback(LinkedList* list, void* elem);

LinkedListStatus linked_list_delete(LinkedList* list, void* elem, bool(*cmp_fn)(void*, void*)); 

LinkedListStatus linked_list_search(LinkedList* list, void* elem, bool(*cmp_fn)(void*, void*));

void linked_list_printf(const LinkedList* list, void(*print_elem)(void*));

bool linked_list_is_empty(const LinkedList* list);

#endif
