#ifndef DARR_H
#define DARR_H

#include <stdbool.h>
#include <stddef.h>

#define DARR_DEFAULT_CAPACITY 2
#define DARR_DEFAULT_GROWING_FACTOR 1.25f

typedef bool(compfun_t)(void const *curr, void const *value);

typedef struct darr_t {
  void **_arr;
  size_t _capacity, _size;
} darr_t;

darr_t *darr_new(void);
size_t darr_get_size(darr_t *da);
size_t darr_get_capacity(darr_t *da);
void *darr_at(darr_t *da, size_t index);
int darr_push(darr_t *da, void *value);
int darr_pop(darr_t *da);
int darr_insert_at(darr_t *da, size_t index, void *value);
int darr_delete_at(darr_t *da, size_t index);
int darr_find(darr_t *da, void *value, compfun_t compare);
void darr_destroy(darr_t *da, bool freeall);

#endif // DARR_H
