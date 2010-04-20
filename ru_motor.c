
#include "ru_motor.h"
#include "ru_config.h"

rom const unsigned char motor_level_table[256] = {
	  0,  39,  40,  41,  41,  42,  43,  44,  48,  51, 
	 53,  55,  58,  60,  62,  63,  65,  67,  68,  69, 
	 70,  71,  72,  73,  75,  76,  77,  78,  78,  79, 
	 81,  81,  82,  83,  84,  84,  85,  86,  87,  87, 
	 88,  89,  89,  90,  90,  91,  91,  92,  92,  92, 
	 93,  94,  94,  95,  95,  96,  96,  96,  97,  98, 
	 98,  98,  99,  99,  99,  99, 100, 100, 100, 101, 
	101, 101, 102, 102, 103, 103, 103, 104, 104, 104, 
	104, 105, 105, 105, 105, 106, 106, 106, 107, 107, 
	107, 107, 108, 108, 108, 108, 109, 109, 109, 110, 
	110, 110, 110, 110, 111, 111, 111, 111, 112, 112, 
	112, 113, 113, 113, 113, 113, 114, 114, 114, 114, 
	114, 115, 115, 117, 120, 122, 125, 127, 128, 128, 
	134, 140, 141, 141, 142, 142, 142, 142, 142, 142, 
	143, 143, 143, 142, 143, 143, 144, 144, 144, 145, 
	145, 145, 146, 146, 146, 146, 147, 147, 147, 148, 
	148, 148, 149, 149, 149, 149, 150, 150, 150, 150, 
	151, 151, 152, 152, 152, 153, 153, 154, 154, 154, 
	155, 155, 155, 155, 156, 156, 157, 157, 157, 158, 
	158, 159, 159, 160, 160, 160, 161, 161, 162, 162, 
	163, 163, 164, 164, 165, 166, 166, 167, 167, 168, 
	168, 169, 170, 170, 172, 172, 173, 174, 175, 176, 
	177, 177, 178, 179, 180, 181, 183, 184, 185, 186, 
	187, 188, 190, 191, 192, 194, 196, 197, 200, 202, 
	203, 207, 208, 210, 211, 212, 213, 214, 215, 215, 
	217, 234, 254, 238, 254, 255
};


int Normalize_PWM(int pwm)
{
	if (pwm < 0)   return 0;
	if (pwm > 254) return 254;
	return pwm;
}

int Linearize_PWM(int u_pwm)
{
	u_pwm = Normalize_PWM(u_pwm);
	
	return motor_level_table[u_pwm];
}

int To_S(int u_pwm) { return u_pwm - (int)127; }
int To_U(int s_pwm) { return s_pwm + (int)127; }

int Flip(int s_pwm)
{
	return -s_pwm;
}
