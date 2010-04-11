
#ifndef _ru_drive_h
#define _ru_drive_h 1

void Set_Left_Speed(int spwm);
void Set_Right_Speed(int spwm);

void Set_Tank_Drive(int sleft, int sright);

void Manual_Tank_Drive_Routine(void);

void Manual_Tank_PID_Drive_Routine(void);

#endif
