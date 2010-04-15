
#ifndef _ru_shoulder_h
#define _ru_shoulder_h 1

#define shoulder_lowering_pot_thresh ((int)173)
#define shoulder_lifting_pot_thresh  ((int)563)

#define shoulder_pot_reverse 1

void Set_Shoulder_Speed(int signed_pwm);

void Manual_Shoulder_Routine(void);

// + is ALWAYS up. Caller should ignore shoulder_pot_reverse.
int Get_Shoulder_Pot(void);

#endif
