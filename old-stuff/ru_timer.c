
#include "ru_timer.h"

volatile signed long timer_zero_base = 0;

void Timer_Init(void)
{
	OpenTimer0(
       TIMER_INT_ON  &
       T0_SOURCE_INT &
       T0_PS_1_128   &
       T0_16BIT );
}

signed long Get_Timer_Zero_Locked(void)
{
	signed long time;
	char saved_enable;
	
	saved_enable = INTCONbits.T0IE;
	
	INTCONbits.T0IE = 0;
	time = Get_Timer_Zero_Unlocked();
	INTCONbits.T0IE = saved_enable;
	
	return time;
}
