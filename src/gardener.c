// Manage plants

/*******************************************************************************
 *    INCLUDED FILES
 ******************************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "gardener.h"

/*******************************************************************************
 *    PUBLIC API
 ******************************************************************************/

struct gardener *create_gardeners(size_t amount) {
  return malloc(sizeof(struct gardener) * amount);
}

struct gardener *cut_many(size_t gardeners_no,
                          struct gardener gardeners[gardeners_no]) {
  size_t i;

  for (i = 0; i < gardeners_no; i++) {
    cut(gardeners[i]);
  }

  return gardeners;
}

/*******************************************************************************
 *    PRIVATE API
 ******************************************************************************/
static void cut(struct gardener gardener_) { gardener_.task = Cutting; }
