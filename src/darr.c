#include "darr.h"
#include <stdio.h>
#include <stdlib.h>

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

bool _increase_darr(darr_t *da, size_t const index) {
  if (index + 1 <= da->_capacity)
    return true;

  __auto_type new_capacity =
      (size_t)((float)da->_capacity * DARR_DEFAULT_GROWING_FACTOR);

  new_capacity =
      new_capacity == da->_capacity ? new_capacity + 1 : new_capacity;

  void *temp = realloc(da->_arr, sizeof(void *) * new_capacity);

  if (temp == NULL) {
    fprintf(stderr, "darr_push(): realocation failed");

    return false;
  }

  da->_arr = temp;
  da->_capacity = new_capacity;

  return true;
}

int darr_push(darr_t *da, void *value) {
  size_t const index = da->_size;

  if (!_increase_darr(da, index))
    return -1;

  da->_arr[index] = value;
  ++da->_size;

  return index;
}
