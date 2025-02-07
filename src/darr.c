#include "darr.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

bool _increase_darr(darr_t *da); //!< **private** method form *`darr_t`*
bool _shrink_darr(darr_t *da);   //!< **private** method form *`darr_t`*

/*!
 * Creates a `darr_t` instance in the heap and allocates the initial size that
 * the array will occupe based on the `DARR_DEFAULT_CAPACITY` value. The array
 * will be a pointer [array] to other pointers with `void` (generic) type, this
 * means that the items should be castet to some type when using, e.g.: `*(float
 * *)da->_arr[1]` or, even better, `*(float *)darr_at(da, 1)`.
 *
 * @return A pointer to the created `darr_t` instance, it should be used in
 * the other `darr_*()` methods to interact with the array itself.
 */
darr_t *darr_new(void) {
  darr_t *da = malloc(sizeof(darr_t));

  da->_size = 0;
  da->_capacity = DARR_DEFAULT_CAPACITY;
  da->_arr = malloc(da->_capacity * sizeof(void *));

  return da;
}

/*!
 * Simple getter, intended to be used in `for`/`while` loops to interact with
 * the array itself.
 *
 * @return The `darr_t._size` attribute.
 * */
size_t darr_get_size(darr_t *da) { return da->_size; }

/*!
 * Simple getter, this one was intended to be used for debugging propurses, but
 * it can be in handy when needing to have fine control over the memory usage.
 *
 * @return The `darr_t._capacity` attribute.
 */
size_t darr_get_capacity(darr_t *da) { return da->_capacity; }

/*!
 *
 */
void *darr_at(darr_t *da, size_t index) {
  return index >= da->_size ? NULL : da->_arr[index];
}

int darr_push(darr_t *da, void *value, size_t size) {
  size_t const index = da->_size;

  if (!_increase_darr(da))
    return -1;

  void *copy = malloc(size);

  memcpy(copy, value, size);

  da->_arr[index] = copy;
  ++da->_size;

  return index;
}

int darr_pop(darr_t *da) {
  if (da->_size == 0)
    return -1;

  size_t const index = da->_size - 1;

  free(da->_arr[index]);

  --da->_size;

  if (!_shrink_darr(da))
    return -1;

  return index;
}

int darr_insert_at(darr_t *da, size_t index, void *value, size_t size) {
  if (index > da->_size)
    return -1;

  if (!_increase_darr(da))
    return -1;

  memmove(&da->_arr[index + 1], &da->_arr[index],
          sizeof(void *) * (da->_size - index));

  void *copy = malloc(size);

  memcpy(copy, value, size);

  da->_arr[index] = copy;
  ++da->_size;

  return index;
}

int darr_delete_at(darr_t *da, size_t index) {
  if (index >= da->_size)
    return -1;

  free(da->_arr[index]);

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
    if (da->_arr[i] != NULL)
      free(da->_arr[i]);

  if (da->_arr != NULL)
    free(da->_arr);

  free(da);
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

bool _shrink_darr(darr_t *da) {
  if ((float)da->_size - 1 >=
          (float)da->_capacity / DARR_DEFAULT_GROWING_FACTOR ||
      da->_capacity <= DARR_DEFAULT_CAPACITY)
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
