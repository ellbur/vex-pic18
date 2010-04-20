
#ifndef _ru_shoulder_h
#define _ru_shoulder_h 1

#define shoulder_lowering_pot_thresh   ((int)1023-800)
#define shoulder_on_wall_pot_thresh    ((int)1023-500) // TODO: NOT RIGHT
#define shoulder_off_wall_pot_thresh   ((int)1023-450) // TODO: NOT RIGHT

#define shoulder_pickup_pot_thresh     ((int)1023-300)
#define shoulder_stay_up_pot_thresh    ((int)1023-300)

#define shoulder_pot_reverse 1

// reduntant with ru_io.h
void Set_Shoulder_Speed(int signed_pwm);

void Manual_Shoulder_Routine(void);

// + is ALWAYS up. Caller should ignore shoulder_pot_reverse.
int Get_Shoulder_Pot(void);

#endif
