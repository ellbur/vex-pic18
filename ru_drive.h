
#ifndef _ru_drive_h
#define _ru_drive_h 1

void Drive_Init(void);

void Set_Left_Sig(int spwm);
void Set_Right_Sig(int spwm);

int Get_Left_Sig(void);
int Get_Right_Sig(void);

void Set_Left_Linear(int speed);
void Set_Right_Linear(int speed);

void Set_Left_Damped(int speed);
void Set_Right_Damped(int speed);

void Set_Auto_Tank_Drive(float left, float right);
void Set_Tele_Tank_Drive(float left, float right);

void Manual_Tank_Drive_Routine(void);

#endif
