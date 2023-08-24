#include <stdio.h>
#include <stdlib.h>

#include "gardener.h"

int main(void) {
  char species[] = "Renanthera monachica";
  float water_amount = 0.2;
  unsigned long watering_period = 86400, start_date = 0, last_watering_date = 0;

  plant *p = create_plant(species, water_amount, start_date, last_watering_date,
                          watering_period);
  if (!p)
    return 1;

  printf("Plant species: %s\n", p->species);

  free(p);

  return 0;
}
