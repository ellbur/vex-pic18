
#include "ru_cruise_test.h"
#include "ru_cruise.h"

void Cruise_Test_Init(void)
{
	Cruise_Meta_Init(0.50); // distance in meters
}

void Cruise_Test_Routine(void)
{
	Cruise_Meta_Routine();
}
