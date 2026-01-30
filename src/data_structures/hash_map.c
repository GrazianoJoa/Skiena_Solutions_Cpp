#include "hash_map.h"
#include "utils.h"

#include <stdlib.h>
#include <string.h>

typedef struct Node{
    void* value;
    char* key;
    struct Node* next;
} Node;

struct HashMap {
    size_t capacity;
    size_t elem_size;
    Node** list;
    hash_fn hash;

    copy_fn copy;
    destroy_fn destroy; 
};

size_t default_hash(HashMap* hp, const char* key) {
    unsigned long hash = 5381;
    for (size_t i = 0; key[i] != '\0'; i++) {
        hash = ((hash << 5) + hash) + (unsigned char)key[i];
    }
    return hash % hp->capacity;
}

HashMap* hash_map_create(size_t elem_size, size_t capacity, hash_fn hash, copy_fn copy, destroy_fn destroy) {
    if (elem_size == 0 || capacity == 0) return NULL;

    HashMap* hp = malloc(sizeof(HashMap));
    if (!hp) return NULL;

    hp->list = calloc(capacity, sizeof(Node*));
    if (!hp->list) {
        free(hp);
        return NULL;
    }

    hp->elem_size = elem_size;
    hp->capacity = capacity;

    hp->copy = copy;
    hp->destroy = destroy;

    if (!hash) {
        hp->hash = default_hash;
    } else {
        hp->hash = hash;
    }

    return hp;
}

void hash_map_destroy(HashMap **hp) {
    if (!hp || !(*hp)) return;

    for (size_t i = 0; i < (*hp)->capacity; i++) {
        Node* curr = (*hp)->list[i];
        while (curr) {
            Node* next = curr->next;
            if ((*hp)->destroy) {
                (*hp)->destroy(curr->value);
            } else {
                free(curr->value);
            }
            free(curr->key);
            free(curr);
            curr = next;
        }
        (*hp)->list[i] = NULL;
    }
    free((*hp)->list);
    free(*hp);
    *hp = NULL;
}

HashMapStatus hash_map_insert(HashMap* hp, const char* key, void* value) {
    if (!hp || !key) return HASH_MAP_ERR_NULL;
    if (key[0] == '\0') return HASH_MAP_ERR_INVALID_ARG;
    
    size_t index = hp->hash(hp, key);

    Node* curr = hp->list[index];
    while (curr) {
        if (strcmp(key, curr->key) == 0) {
            if (hp->destroy) {
                hp->destroy(curr->value);
            } else {
                free(curr->value);
            }

            curr->value = malloc(hp->elem_size);
            if (!curr->value) return HASH_MAP_ERR_ALLOC_MEM;

            if (hp->copy) {
                hp->copy(curr->value, value);
            } else {
                memcpy(curr->value, value, hp->elem_size);
            }

            return HASH_MAP_OK;
        }
        curr = curr->next;
    }

    Node* new_node = malloc(sizeof(Node));
    if (!new_node) return HASH_MAP_ERR_ALLOC_MEM;

    new_node->key = malloc(strlen(key) + 1);
    if (!new_node->key) {
        free(new_node);
        return HASH_MAP_ERR_ALLOC_MEM;  
    }
    strcpy(new_node->key, key);

    new_node->value = malloc(hp->elem_size);
    if (!new_node->value) {
        free(new_node->key);
        free(new_node);
        return HASH_MAP_ERR_ALLOC_MEM;
    }

    if (hp->copy) {
        hp->copy(new_node->value, value);
    } else {
        memcpy(new_node->value, value, hp->elem_size);
    }

    new_node->next = hp->list[index];
    hp->list[index] = new_node;

    return HASH_MAP_OK;
}

HashMapStatus hash_map_get(HashMap *hp, const char *key, void* out) {
    if (!hp || !key || !out) return HASH_MAP_ERR_NULL;

    if (key[0] == '\0') return HASH_MAP_ERR_INVALID_ARG;

    size_t index = hp->hash(hp, key);

    Node* curr = hp->list[index];
    while (curr) {
        if (strcmp(key, curr->key) == 0) {
            if (hp->copy) {
              hp->copy(out, curr->value);
            } else {
              memcpy(out, curr->value, hp->elem_size);
            }
            return HASH_MAP_OK;
        }
        curr = curr->next;
    }

    return HASH_MAP_ERR_NOT_FOUND;
}

bool hash_map_contains(HashMap *hp, const char *key) {
    if (!hp || !key) return false;

    if (key[0] == '\0') return false;

    size_t index = hp->hash(hp, key);

    Node* curr = hp->list[index];
    while (curr) {
        if (strcmp(key, curr->key) == 0) return true;
        curr = curr->next;
    }
    return false;
}
