// Manage gardeners in the mansion

#include <stddef.h>
#include <stdlib.h>

#include "gardener.h"

struct gardener *create_gardeners(size_t amount) {
  return malloc(sizeof(struct gardener) * amount);
}

struct gardener *cut(size_t gardeners_no,
                     struct gardener gardeners[gardeners_no]) {
  size_t i;

  for (i = 0; i < gardeners_no; i++) {
    gardeners[i].task = Cutting;
  }

  return gardeners;
}
