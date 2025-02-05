#include "darr.h"
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define T long
#define N 255

int main(void) {
  darr_t *darr = darr_new();

  srand(time(NULL));
  puts("");

  puts("+----------+-------+------+----------+");
  puts("| Inserted | Index | Size | Capacity |");
  puts("+----------+-------+------+----------+");
  for (size_t i = 0; i < N; ++i) {
    __auto_type const value = &(T){rand()};
    int const index = darr_push(darr, value);

    printf("| %8lx | %5i | %4lu | %8lu |\n", *value, index, darr_get_size(darr),
           darr_get_capacity(darr));
  }
  puts("+----------+-------+------+----------+");

  puts("+-------+------+----------+");
  puts("| Index | Size | Capacity |");
  puts("+-------+------+----------+");
  for (size_t i = 0; i < N; ++i) {
    int const index = darr_pop(darr);

    printf("| %5i | %4lu | %8lu |\n", index, darr_get_size(darr),
           darr_get_capacity(darr));
  }
  puts("+-------+------+----------+");

  return 0;
}
