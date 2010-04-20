
#ifndef _ru_timer_h
#define _ru_timer_h 1

#include "ru_config.h"
#include <timers.h>

// Might be right
#define TIMER_DELTA (1.28e-05)

void Timer_Init(void);

// Incremented on interrupts
extern volatile signed long timer_zero_base;

#define Get_Timer_Zero_Unlocked() (timer_zero_base + ReadTimer0())

signed long Get_Timer_Zero_Locked(void);

#endif
