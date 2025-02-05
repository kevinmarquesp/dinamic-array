#include "darr.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

darr_t *darr_new(void) {
  darr_t *da = malloc(sizeof(darr_t));

  da->_size = 0;
  da->_capacity = DARR_DEFAULT_CAPACITY;
  da->_arr = malloc(da->_capacity * sizeof(void *));

  return da;
}

size_t darr_get_size(darr_t *da) { return da->_size; }

size_t darr_get_capacity(darr_t *da) { return da->_capacity; }

void *darr_at(darr_t *da, size_t index) {
  return index >= da->_size ? NULL : da->_arr[index];
}

bool _increase_darr(darr_t *da) {
  if (da->_size + 1 <= da->_capacity)
    return true;

  __auto_type new_capacity =
      (size_t)((float)da->_capacity * DARR_DEFAULT_GROWING_FACTOR);

  new_capacity =
      new_capacity == da->_capacity ? new_capacity + 1 : new_capacity;

  void *temp = realloc(da->_arr, sizeof(void *) * new_capacity);

  if (temp == NULL) {
    fprintf(stderr, "_increase_darr(): realocation failed\n");

    return false;
  }

  da->_arr = temp;
  da->_capacity = new_capacity;

  return true;
}

int darr_push(darr_t *da, void *value) {
  size_t const index = da->_size;

  if (!_increase_darr(da))
    return -1;

  da->_arr[index] = value;
  ++da->_size;

  return index;
}

bool _shrink_darr(darr_t *da) {
  if ((float)da->_size - 1 >=
      (float)da->_capacity / DARR_DEFAULT_GROWING_FACTOR)
    return true;

  da->_capacity = da->_size;

  void *temp = realloc(da->_arr, sizeof(void *) * da->_capacity + 1);

  if (temp == NULL) {
    fprintf(stderr, "_shrink_darr(): realocation failed\n");

    return false;
  }

  da->_arr = temp;

  return true;
}

int darr_pop(darr_t *da) {
  if (da->_size == 0)
    return -1;

  size_t const index = da->_size - 1;

  --da->_size;

  if (!_shrink_darr(da))
    return -1;

  return index;
}

int darr_insert_at(darr_t *da, size_t index, void *value) {
  if (index >= da->_size)
    return -1;

  if (!_increase_darr(da))
    return -1;

  memmove(&da->_arr[index + 1], &da->_arr[index],
          sizeof(void *) * (da->_size - index));

  da->_arr[index] = value;
  ++da->_size;

  return index;
}

int darr_delete_at(darr_t *da, size_t index) {
  if (index >= da->_size)
    return -1;

  memmove(&da->_arr[index], &da->_arr[index + 1],
          sizeof(void *) * (da->_size - index));

  if (!_shrink_darr(da))
    return -1;

  --da->_size;

  return index;
}

int darr_find(darr_t *da, void *value, compfun_t compare) {
  for (size_t i = 0; i < da->_size; ++i)
    if (compare(da->_arr[i], value))
      return i;

  return -1;
}

void darr_destroy(darr_t *da) {
  if (da == NULL)
    return;

  for (size_t i = 0; i < da->_size; ++i)
    free(da->_arr[i]);

  free(da->_arr);
  free(da);
}
