#include "comparators.h"

int compare_int(const void *a, const void *b) {
  int ia = *(const int*)a;
  int ib = *(const int*)b;

  return (ia > ib) - (ia < ib);
}
