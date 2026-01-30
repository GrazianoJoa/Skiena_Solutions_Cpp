#ifndef HASH_MAP_H
#define HASH_MAP_H

#include <stdbool.h>
#include <stdlib.h>
#include "utils.h"

typedef enum HashMapStatus {
    HASH_MAP_OK = 0,
    HASH_MAP_ERR_NULL,
    HASH_MAP_ERR_INVALID_ARG,
    HASH_MAP_ERR_IS_EMPTY,
    HASH_MAP_ERR_ALLOC_MEM,
    HASH_MAP_ERR_NOT_FOUND
} HashMapStatus;

typedef struct HashMap HashMap;

typedef size_t (*hash_fn)(HashMap* hp, const char* key);

HashMap* hash_map_create(size_t elem_size, size_t capacity, hash_fn hash, copy_fn copy, destroy_fn destroy);
void hash_map_destroy(HashMap** hp);
HashMapStatus hash_map_insert(HashMap* hp, const char* key, void* value);
HashMapStatus hash_map_get(HashMap* hp, const char* key, void* out);
bool hash_map_contains(HashMap* hp, const char* key);

#endif
