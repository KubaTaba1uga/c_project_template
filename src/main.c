#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "gardener.h"

plant plants[] = {{.species = "Renanthera monachica",
                   .water_amount = 0.2,
                   .watering_period = 86400,
                   .start_date = 123,
                   .last_watering_date = 246},
                  {.species = "Arachnis annamensis",
                   .water_amount = 0.15,
                   .watering_period = 43200,
                   .start_date = 246,
                   .last_watering_date = 10000}};

int main(void) {
  size_t i, plants_amount = sizeof(plants) / sizeof(plant);
  bool was_watered;

  while (true) {
    for (i = 0; i < plants_amount; i++) {
      was_watered = water_plant(&plants[i]);

      if (was_watered)
        printf("%s was watered.\n", plants[i].species);
      else
        printf("%s was watered.\n", plants[i].species);
    }

    sleep(3);
  }

  return 0;
}