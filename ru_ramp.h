
#ifndef _ru_ramp_h
#define _ru_ramp_h 1

void Set_Ramp_Speed(int spwm);

void Manual_Ramp_Routine(void);
void Manual_Joy_Ramp_Routine(void);

int Get_Ramp_Pot(void);

#define ramp_pot_reverse 1

#define ramp_lifting_pot_thresh  ((int)1023-150)
#define ramp_lowering_pot_thresh ((int)1023-850)

#endif
