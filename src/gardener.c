// Let's imagine an app for managing plant's watering.

/*******************************************************************************
 *    INCLUDED FILES
 ******************************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gardener.h"

/*******************************************************************************
 *    PUBLIC API
 ******************************************************************************/
plant *create_plant(char *species, float water_amount, unsigned long start_date,
                    unsigned long last_watering_date,
                    unsigned long watering_period) {

  plant *p = my_malloc(sizeof(plant));
  if (!p)
    return NULL;

  strcpy(p->species, species);
  p->water_amount = water_amount;
  p->last_watering_date = last_watering_date;
  p->watering_period = watering_period;

  return p;
}

int water_plant(plant *plant_) {
  // On success return 0

  unsigned long now = get_current_time();
  if (now == 0)
    return 1;

  if (!is_watering_required(plant_, now))
    return 0;

  plant_->last_watering_date = now;

  return 0;
}

/*******************************************************************************
 *    PRIVATE API
 ******************************************************************************/
bool is_watering_required(plant *plant_, unsigned long time) {
  unsigned long new_watering_period =
      plant_->last_watering_date + plant_->watering_period;

  // Detect overflow
  if (new_watering_period < plant_->last_watering_date ||
      new_watering_period < plant_->watering_period)
    exit(1);

  return time >= new_watering_period;
}
