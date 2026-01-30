#ifndef UTILS_H
#define UTILS_H

typedef void (*destroy_fn)(void* obj);
typedef void (*copy_fn)(void* dst, void* src);
typedef int (*compare_fn)(const void* a, const void* b);
typedef void (*for_each_fn)(void* elem, void* user_data);

#endif
