#include "linked_list.h"

struct Node {
    void* data;
    struct Node* next;
};

struct LinkedList {
    Node* head;
    size_t elem_size;
};

LinkedList* linked_list_create(size_t elem_size) {
    if (elem_size == 0) return NULL;

    LinkedList* list = malloc(sizeof(LinkedList));

    if (!list) return NULL;

    list->elem_size = elem_size;
    list->head = NULL;

    return list;
}

LinkedListStatus linked_list_append(LinkedList* list, void* data) {
    if (!list || !data) return LINKED_LIST_ERR_NULL;

    Node* new_node = malloc(sizeof(Node));
    if (!new_node) return LINKED_LIST_ERR_ALLOC;

    new_node->data = malloc(list->elem_size);
    if (!new_node->data) {
        free(new_node);
        return LINKED_LIST_ERR_ALLOC;
    }

    memcpy(new_node->data, data, list->elem_size);
    new_node->next = NULL;

    if (list->head == NULL) {
        list->head = new_node;
        return LINKED_LIST_OK;
    }

    Node* tmp = list->head;
    while (tmp->next) {
        tmp = tmp->next;
    }

    tmp->next = new_node;
    return LINKED_LIST_OK;
}
