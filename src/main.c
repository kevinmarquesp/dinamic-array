#include "darr.h"
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define T long
#define N 255

void dbg_print_array(darr_t *darr);
void dbg_push_catalog(darr_t *darr);
void dbg_pop_catalog(darr_t *darr);

int main(void) {
  darr_t *darr = darr_new();

  srand(time(NULL));
  puts("");

  darr_push(darr, &(T){30});
  darr_push(darr, &(T){40});
  darr_push(darr, &(T){50});

  darr_insert_at(darr, 2, &(T){45});

  dbg_print_array(darr);

  darr_delete_at(darr, 1);

  dbg_print_array(darr);

  return 0;
}

void dbg_print_array(darr_t *darr) {
  puts("[dbg]");
  printf("|- Size: %lu\n", darr_get_size(darr));
  printf("|- Capacity: %lu\n", darr_get_capacity(darr));
  printf("'- Values:\n   '- { ");
  for (size_t i = 0; i < darr_get_size(darr); ++i)
    printf("%lu ", *(T *)darr_at(darr, i));
  puts("}\n");
}

void dbg_push_catalog(darr_t *darr) {
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
}

void dbg_pop_catalog(darr_t *darr) {
  puts("+-------+------+----------+");
  puts("| Index | Size | Capacity |");
  puts("+-------+------+----------+");
  for (size_t i = 0; i < N; ++i) {
    int const index = darr_pop(darr);

    printf("| %5i | %4lu | %8lu |\n", index, darr_get_size(darr),
           darr_get_capacity(darr));
  }
  puts("+-------+------+----------+");
}
