
#include "ru_timer_test.h"
#include "ru_timer.h"

void Timer_Test_Init(void)
{	
}

void Timer_Test_Routine(void)
{
	printf("%ld\n", Get_Timer_Zero_Locked() >> 8);
}
