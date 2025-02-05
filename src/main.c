#include "darr.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* #define T char */
#define T short
/* #define T int */
/* #define T long */
/* #define T float */
/* #define T double */

void test_basic_operations(void);
bool compare(void const *curr, void const *value);
void test_edge_cases(void);
void test_large_array(void);

int main(void) {
  test_basic_operations();
  test_edge_cases();
  test_large_array();

  puts("\nAll tests passed!");
  return 0;
}

// Test function for basic operations
void test_basic_operations(void) {
  darr_t *darr = darr_new();

  // Test initial state
  assert(darr_get_size(darr) == 0);
  assert(darr_get_capacity(darr) == DARR_DEFAULT_CAPACITY);
  assert(darr_at(darr, 0) == NULL); // Out of bounds access should return NULL

  // Test push
  T value1 = 10, value2 = 20, value3 = 30;
  assert(darr_push(darr, &value1) == 0); // First element at index 0
  assert(darr_push(darr, &value2) == 1); // Second element at index 1
  assert(darr_push(darr, &value3) == 2); // Third element at index 2

  // Test size and capacity after pushes
  assert(darr_get_size(darr) == 3);
  assert(darr_get_capacity(darr) >= 3); // Capacity should have grown

  // Test at
  assert(*(T *)darr_at(darr, 0) == value1);
  assert(*(T *)darr_at(darr, 1) == value2);
  assert(*(T *)darr_at(darr, 2) == value3);
  assert(darr_at(darr, 3) == NULL); // Out of bounds access

  // Test pop
  assert(darr_pop(darr) == 2); // Pop last element (index 2)
  assert(darr_get_size(darr) == 2);
  assert(darr_at(darr, 2) == NULL); // Element at index 2 should be gone

  // Test insert_at
  T value4 = 15;
  assert(darr_insert_at(darr, 1, &value4) == 1); // Insert at index 1
  assert(darr_get_size(darr) == 3);
  assert(*(T *)darr_at(darr, 1) == value4); // Check inserted value
  assert(*(T *)darr_at(darr, 2) == value2); // Check shifted value

  // Test delete_at
  assert(darr_delete_at(darr, 1) == 1); // Delete at index 1
  assert(darr_get_size(darr) == 2);
  assert(*(T *)darr_at(darr, 1) == value2); // Check shifted value

  // Test find
  assert(darr_find(darr, &value1, compare) == 0);  // Find value1 at index 0
  assert(darr_find(darr, &value2, compare) == 1);  // Find value2 at index 1
  assert(darr_find(darr, &value3, compare) == -1); // value3 was popped

  // Clean up
  darr_destroy(darr, false);
  printf("{test_basic_operations}\t passed!\n");
}

// Helper function to compare two values
bool compare(void const *curr, void const *value) {
  return *(T *)curr == *(T *)value;
}

// Test function for edge cases
void test_edge_cases() {
  darr_t *darr = darr_new();

  // Test empty array
  assert(darr_pop(darr) == -1);                    // Pop from empty array
  assert(darr_delete_at(darr, 0) == -1);           // Delete from empty array
  assert(darr_insert_at(darr, 1, &(T){10}) == -1); // Insert out of bounds

  // Test inserting at the end
  assert(darr_insert_at(darr, 0, &(T){10}) == 0); // Insert at index 0
  assert(darr_insert_at(darr, 1, &(T){20}) == 1); // Insert at index 1

  // Test deleting the only element
  assert(darr_delete_at(darr, 0) == 0); // Delete at index 0
  assert(darr_get_size(darr) == 1);
  assert(*(T *)darr_at(darr, 0) == 20); // Check remaining element

  // Clean up
  darr_destroy(darr, false);
  printf("{test_edge_cases}\t passed!\n");
}

// Test function for large arrays
void test_large_array() {
  darr_t *darr = darr_new();
  size_t const N = 1000;

  // Push N elements
  for (size_t i = 0; i < N; ++i) {
    T *value = malloc(sizeof(T));

    *value = i;

    assert(darr_push(darr, value) == (int)i);
  }

  // Check size and capacity
  assert(darr_get_size(darr) == N);
  assert(darr_get_capacity(darr) >= N);

  // Check values
  for (size_t i = 0; i < N; ++i)
    assert(*(T *)darr_at(darr, i) == (T)i);

  // Pop all elements
  for (size_t i = 0; i < N; ++i)
    assert(darr_pop(darr) == (int)(N - i - 1));

  // Check final state
  assert(darr_get_size(darr) == 0);
  assert(darr_get_capacity(darr) == DARR_DEFAULT_CAPACITY);

  // Clean up
  darr_destroy(darr, false);
  printf("{test_large_array}\t passed!\n");
}
