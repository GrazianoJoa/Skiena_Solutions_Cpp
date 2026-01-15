#include "linked_list.h"
#include <stdbool.h>
#include <stdlib.h>

typedef struct Node {
    void* elem;
    struct Node* next;
} Node;

struct LinkedList {
    Node* head;
    size_t elem_size;
    size_t size;
};

/*
 *  PUBLIC METHODS
*/

// STATE METHODS

LinkedList* linked_list_create(size_t elem_size) {
    if (elem_size == 0) return NULL;

    LinkedList* list = malloc(sizeof(LinkedList));
    if (!list) return NULL;

    list->elem_size = elem_size;
    list->size = 0;
    list->head = NULL;

    return list;
}

void linked_list_destroy(LinkedList **list) {
    if (!list || !(*list)) return;

    Node* curr = (*list)->head;
    while (curr) {
        Node* tmp = curr->next;
        free(curr->elem);
        free(curr);
        curr = tmp;
    }

    free(*list);
    *list = NULL;
}

// INSERT METHODS

LinkedListStatus linked_list_insert_at(LinkedList *list, size_t pos, void *elem) {
    if (!list || !elem) return LINKED_LIST_ERR_NULL;

    if (pos > list->size) return LINKED_LIST_ERR_INVALID_ARG;

    Node* new_node = malloc(sizeof(Node));
    if (!new_node) return LINKED_LIST_ERR_ASSIGN_MEM;

    new_node->elem = malloc(list->elem_size);
    if (!new_node->elem) {
        free(new_node);
        return LINKED_LIST_ERR_ASSIGN_MEM;
    }
    memcpy(new_node->elem, elem, list->elem_size);

    if (list->head == NULL) {
        list->head = new_node;
        new_node->next = NULL;
    }

    if (pos == 0) {
        new_node->next = list->head;
        list->head = new_node;
    }

    Node* curr = list->head;
    for (size_t i = 0; i < pos - 1; i++) {
        curr = curr->next;
    }
    new_node->next = curr->next;
    curr->next = new_node;
    
    list->size++;
    return LINKED_LIST_OK;
}

LinkedListStatus linked_list_pushback(LinkedList* list, void* elem) {
    return linked_list_insert_at(list, list->size, elem);
}

LinkedListStatus linked_list_push(LinkedList* list, void* elem) {
    return linked_list_insert_at(list, 0, elem);
}

// DELETION METHODS

LinkedListStatus linked_list_delete(LinkedList *list, void* elem, bool (*cmp_fn)(void*, void*)) {
    if (!list || !elem || !cmp_fn) return LINKED_LIST_ERR_NULL;

    if (linked_list_is_empty(list)) return LINKED_LIST_ERR_EMPTY;

    Node* curr = list->head;
    Node* prev = NULL;

    for (size_t i = 0; i < list->size; i++) {
        if (cmp_fn(curr->elem, elem)) {

            if (prev) {
                prev->next = curr->next;
            } else {
                list->head = curr->next;
            }

            free(curr->elem);
            free(curr);

            list->size--;
            return LINKED_LIST_OK;
        }
        prev = curr;
        curr = curr->next;
    }

    return LINKED_LIST_ERR_INVALID_ARG;
}

// PRINT METHODS

void linked_list_print(const LinkedList *list, void (*print_elem)(void*)) {
    if (!list || !print_elem) return;

    Node* curr = list->head;
    while (curr != NULL) {
        print_elem(curr->elem);
        curr = curr->next;
    }
    printf("\n");
}

// UTILS 

void print_int(void* data) {
    printf("%d", *(int*)data);
}

bool cmp_int(void* a, void* b) {
    return *(int*)a == *(int*)b;
}

bool linked_list_is_empty(const LinkedList* list) {
    return !list || list->size == 0;
}
