#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linked_list.h"
#include "utils.h"

typedef struct Node {
    void* elem;
    struct Node* next;
} Node;

struct LinkedList {
    Node* head;
    size_t elem_size;
    size_t size;

    copy_fn copy;
    destroy_fn destroy;
    compare_fn compare;
};

/*
 *  PUBLIC METHODS
*/

// STATE METHODS

LinkedList* linked_list_create(size_t elem_size, copy_fn copy, destroy_fn destroy, compare_fn compare) {
    if (elem_size == 0 || !compare) return NULL;

    LinkedList* list = malloc(sizeof(LinkedList));
    if (!list) return NULL;

    list->elem_size = elem_size;
    list->size = 0;
    list->head = NULL;

    list->copy = copy;
    list->destroy = destroy;
    list->compare = compare;

    return list;
}

void linked_list_destroy(LinkedList **list) {
    if (!list || !(*list)) return;

    Node* curr = (*list)->head;
    while (curr) {
        Node* tmp = curr->next;
        if ((*list)->destroy) {
            (*list)->destroy(curr->elem);
        } else {
            free(curr->elem);
        }
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

    if (list->copy) {
        list->copy(new_node->elem, elem);
    } else {
        memcpy(new_node->elem, elem, list->elem_size);
    }

    if (pos == 0) {
        new_node->next = list->head;
        list->head = new_node;
        list->size++;
        return LINKED_LIST_OK;
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

LinkedListStatus linked_list_delete(LinkedList *list, void* elem) {
    if (!list || !elem) return LINKED_LIST_ERR_NULL;

    if (linked_list_is_empty(list)) return LINKED_LIST_ERR_EMPTY;

    Node* curr = list->head;
    Node* prev = NULL;

    for (size_t i = 0; i < list->size; i++) {
        if (list->compare(curr->elem, elem) == 0) {

            if (prev) {
                prev->next = curr->next;
            } else {
                list->head = curr->next;
            }

            if (list->destroy) {
                list->destroy(curr->elem);
            } else {
                free(curr->elem);
            }
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

bool linked_list_is_empty(const LinkedList* list) {
    return !list || list->size == 0;
}

size_t linked_list_g_size(const LinkedList* list) {
    return list->size;
}
