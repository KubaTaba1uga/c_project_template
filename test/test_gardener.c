/*******************************************************************************
 *    INCLUDED FILES
 ******************************************************************************/

// Test framework
#include "unity.h"

// App
#include "gardener.h"
#include "mock_utils.h"

void test_cmock_working(void) { //
  TEST_PASS_MESSAGE("cmock is working");
}

/*******************************************************************************
 *    PUBLIC API TESTS
 ******************************************************************************/

void test_create_plant_success(void) {
  char species[] = "Renanthera monachica";
  float water_amount = 0.2;
  unsigned long watering_period = 86400, start_date = 0, last_watering_date = 0;

  plant *p;

  p = create_plant(species, water_amount, start_date, last_watering_date,
                   watering_period);

  TEST_ASSERT_NOT_NULL(p);

  TEST_ASSERT_EQUAL_STRING(species, p->species);

  TEST_ASSERT_EQUAL_FLOAT(water_amount, p->water_amount);

  TEST_ASSERT_EQUAL(start_date, p->start_date);
  TEST_ASSERT_EQUAL(last_watering_date, p->last_watering_date);
  TEST_ASSERT_EQUAL(watering_period, p->watering_period);
}

void test_create_plant_failure(void) {
  char species[] = "Renanthera monachica";
  float water_amount = 0.2;
  unsigned long watering_period = 86400, start_date = 0, last_watering_date = 0;

  plant *p;

  my_malloc_IgnoreAndReturn(NULL);

  p = create_plant(species, water_amount, start_date, last_watering_date,
                   watering_period);

  TEST_ASSERT_NOT_NULL(p);
}
