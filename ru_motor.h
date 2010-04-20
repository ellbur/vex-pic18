
#ifndef _ru_motor_h
#define _ru_motor_h 1

#define motor_set(M, S) M = Normalize_PWM(To_U(S));

int Normalize_PWM(int u_pwm);

int Linearize_PWM(int u_pwm);

int To_S(int u_pwm);
int To_U(int s_pwm);

/*
 * Signed input and output!!
 */
int Flip(int s_pwm);

#endif
