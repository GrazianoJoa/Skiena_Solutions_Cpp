#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef enum LinkedListStatus {
    LINKED_LIST_OK = 0,
    LINKED_LIST_ERR_NULL,
    LINKED_LIST_ERR_ALLOC,
    LINKED_LIST_ERR_EMPTY
};

typedef struct LinkedList LinkedList;
typedef struct ListNode ListNode;

LinkedList* linked_list_create(size_t elem_size);
LinkedListStatus linked_list_destroy(LinkedList** list);
LinkedListStatus linked_list_append(LinkedList* list, void* elem);
LinkedListStatus linked_list_prepend(LinkedList* list, void* elem);
LinkedListStatus linked_list_remove_front(LinkedList* list, void** out_elem);
size_t linked_list_size(const LinkedList* list);
bool linked_list_is_empty(const LinkedList* list);
void linked_list_for_each(const LinkedList* list, void (*visit)(void* elem));


#endif
