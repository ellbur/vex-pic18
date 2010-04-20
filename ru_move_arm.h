
#ifndef _ru_move_arm_h
#define _ru_move_arm_h 1

extern char move_arm_done;

#define UP    (1)
#define DOWN  (-1)

// direction + is up, - is down
void Move_Arm_Meta_Init(int pot_target, char direction);
void Move_Arm_Meta_Routine(void);

#endif
