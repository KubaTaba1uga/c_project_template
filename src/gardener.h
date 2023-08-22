#include <stddef.h>

enum jobs { Sowing, Cutting, Watering };

struct gardener {
  int id;
  char surname[255];
  char firstname[255];
  enum jobs task;
};

struct gardener *create_gardeners(size_t amount);
struct gardener *cut(size_t gardeners_no,
                     struct gardener gardeners[gardeners_no]);
