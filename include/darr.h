#ifndef DARR_H
#define DARR_H

#include <stdbool.h>
#include <stddef.h>

#ifndef DARR_DEFAULT_CAPACITY
/*!
 * Initial array capacity, that's just an arbitrary number and it can shrank as
 * the items is removed. But this value can be changed to avoid resizing the
 * array too soon.
 */
#define DARR_DEFAULT_CAPACITY 2
#endif // !DARR_DEFAULT_CAPACITY

#ifndef DARR_DEFAULT_GROWING_FACTOR
/*!
 * The growing factor will define how much the array should be resized when
 * needed. Between 1 and 2 is a good choice. By the way, **this value should be
 * a float**.
 */
#define DARR_DEFAULT_GROWING_FACTOR 1.25f
#endif // !DARR_DEFAULT_GROWING_FACTOR

/*!
 * Type for the function that the `darr_find()` method will use to iterate over
 * all items in the array to compare with the target item that needs to be
 * found. **The user isn't meant to use this type**, it's useful to make the
 * definition of the *find* paramter easier to write -- but it can also be used
 * as reference to build the comparation function in the main code.
 */
typedef bool(compfun_t)(void const *curr, void const *value);

/*!
 * Struct that will **hold the actual dinamic array** and other informations to
 * search, insert and remove elements from within. Since **C** doesn't support
 * *generic types*, the array will be stored as an array that points to a
 * sequence of pointers (I know complicated).
 *
 * Since all the items is a generic pointer (`void*`) to something, it's due to
 * the developer to cast that item into a type that makes sence, for an example:
 * `darr_at(mydarr, 1)` will be a `void*`, cast this `void` to a `int` with
 * `(int *)darr_at(mydarr, 1)` to interprete this as a pointer to an integer,
 * and now access the value that it's pointing to with an extra `*`, like `*(int
 * *)darr_at(mydarr, 1)`.
 *
 * Check the detailed `darr_t` description for more information about it's
 * attributes.
 */
typedef struct darr_t {
  /*! Pointer to the array body, the elements should be casted when using. */
  void **_arr;
  /*! Total ammount of spaces being used by the array, used in `for` loops. */
  size_t _size;
  /*! Max capacity, this should change when it needs to resize. */
  size_t _capacity;
} darr_t;

darr_t *darr_new(void);
size_t darr_get_size(darr_t *da);
size_t darr_get_capacity(darr_t *da);
void *darr_at(darr_t *da, size_t index);
int darr_push(darr_t *da, void *value, size_t size);
int darr_pop(darr_t *da);
int darr_insert_at(darr_t *da, size_t index, void *value, size_t size);
int darr_delete_at(darr_t *da, size_t index);
int darr_find(darr_t *da, void *value, compfun_t compare);
void darr_destroy(darr_t *da);

#endif // DARR_H
