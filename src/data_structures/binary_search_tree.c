#include "binary_search_tree.h"
#include <stdio.h>
#include <string.h>

typedef struct Node {
    void* elem;
    struct Node* left;
    struct Node* right;
} Node;

struct BinarySearchTree {
    size_t elem_size;
    Node* root;

    copy_fn copy;
    destroy_fn destroy;
    compare_fn compare;
};

BinarySearchTree* binary_search_tree_create(size_t elem_size, copy_fn copy, destroy_fn destroy, compare_fn compare) {
    if (!elem_size || !compare) return NULL;

    BinarySearchTree* bst = malloc(sizeof(BinarySearchTree));
    if(!bst) return NULL;

    bst->elem_size = elem_size;
    bst->root = NULL;
    
    bst->copy = copy;
    bst->destroy = destroy;
    bst->compare = compare;

    return bst;
}

void node_destroy(Node** node, destroy_fn destroy) {
    if (!node || !(*node)) return;
    node_destroy(&(*node)->left, destroy);
    node_destroy(&(*node)->right, destroy);
    if (destroy) {
        destroy((*node)->elem);
    } else {
        free((*node)->elem);
    }
    free(*node);
    *node = NULL;
}

void binary_search_tree_destroy(BinarySearchTree **bst) {
    if (!bst || !(*bst)) return;

    node_destroy(&(*bst)->root, (*bst)->destroy);

    free(*bst);
    *bst = NULL;
}

Node* node_create(void* elem, size_t elem_size, copy_fn copy) {
    Node* new_node = malloc(sizeof(Node));
    if (!new_node) return NULL;

    new_node->elem = malloc(sizeof(elem_size));
    if (!new_node->elem) return NULL;

    if (copy) {
        copy(new_node->elem, elem);
    } else {
        memcpy(new_node->elem, elem, elem_size);
    }

    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}

int node_insert(Node** node, void* elem, size_t elem_size, copy_fn copy, compare_fn compare) {
    if (!(*node)) {
        *node = node_create(elem, elem_size, copy);
        return (*node) ? 0 : -1;
    }

    int c = compare(elem, (*node)->elem);

    if (c < 0) node_insert(&(*node)->left, elem, elem_size, copy, compare);
    else if (c > 0) node_insert(&(*node)->right, elem, elem_size, copy, compare);

    return -1;
}

BinarySearchTreeStatus binary_search_tree_insert(BinarySearchTree *bst, void *elem) {
    if (!bst || !elem) return BINARY_SEARCH_TREE_ERR_NULL;

    if (node_insert(&bst->root, elem, bst->elem_size, bst->copy, bst->compare) == 0) return BINARY_SEARCH_TREE_OK;

    return BINARY_SEARCH_TREE_ERR;
}
