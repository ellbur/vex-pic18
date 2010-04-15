
#include "ru_encoder.h"
#include "ru_input.h"
#include "ru_timer.h"
#include "ru_config.h"

encoder_t encoders[NUM_ENCODERS] = {
	{ 1, 2, -0.25 },
	{ 3, 4, -0.25 }
};

void Encoder_Init(void)
{
	char b;
	
	// Copied from Kevin Watson's encoder code.
	
	TRISBbits.TRISB2 = 1;
	INTCON3bits.INT2IP = 0;
	INTCON2bits.INTEDG2 = 1;
	INTCON3bits.INT2IF = 0;
	INTCON3bits.INT2IE = 1;

	TRISBbits.TRISB3 = 1;
	INTCON2bits.INT3IP = 0;
	INTCON2bits.INTEDG3 = 1;
	INTCON3bits.INT3IF = 0;
	INTCON3bits.INT3IE = 1;

	TRISBbits.TRISB4 = 1;
	TRISBbits.TRISB5 = 1;
	TRISBbits.TRISB6 = 1;
	TRISBbits.TRISB7 = 1;
  	INTCON2bits.RBIP = 0;
	b = PORTB;

	INTCONbits.RBIF = 0;
	INTCONbits.RBIE = 1;
	TRISBbits.TRISB2 = 1;
	INTCON3bits.INT2IP = 0;
	INTCON2bits.INTEDG2 = 1;
	INTCON3bits.INT2IF = 0;
	INTCON3bits.INT2IE = 1;

	TRISBbits.TRISB3 = 1;
	INTCON2bits.INT3IP = 0;
	INTCON2bits.INTEDG3 = 1;
	INTCON3bits.INT3IF = 0;
	INTCON3bits.INT3IE = 1;

	TRISBbits.TRISB4 = 1;
	TRISBbits.TRISB5 = 1;
	TRISBbits.TRISB6 = 1;
	TRISBbits.TRISB7 = 1;
  	INTCON2bits.RBIP = 0;

	b = PORTB;

	INTCONbits.RBIF = 0;
	INTCONbits.RBIE = 1;
}

void Encoder_Tick(encoder_t *enc, encoder_channel_t channel)
{
	char self, other, dir;
	signed long time;
	
	if (channel == ENC_A)  {
		self  = Read_Interrupt_Digital(enc->dig_a);
		other = Read_Interrupt_Digital(enc->dig_b);
	}
	else {
		self  = Read_Interrupt_Digital(enc->dig_b);
		other = Read_Interrupt_Digital(enc->dig_a);
	}
	
	dir = self ^ other ^ channel;
	if (!dir) dir = -1;
	
	enc->count += dir;
	enc->abs_count++;
	
	if (enc->last_dir != dir) {
		enc->time_buffer_index = 0;
		enc->got_enough = 0;
		enc->last_dir = dir;
	}
	
	enc->time_buffer[enc->time_buffer_index] = Get_Timer_Zero_Unlocked();
	enc->time_buffer_index++;
	
	if (enc->time_buffer_index >= ENCODER_BUFFER_SIZE)
		enc->got_enough = 1;
	
	enc->time_buffer_index = enc->time_buffer_index % ENCODER_BUFFER_SIZE;
}

float Encoder_Calc_Speed_Counting(encoder_t *enc)
{
	return Encoder_Calc_Spin_Counting(enc) / TICKS_PER_METER;
}

float Encoder_Calc_Spin_Counting(encoder_t *enc)
{
	int delta;
	
	delta = (int) (enc->count - enc->last_count);
	return delta / SLOW_LOOP_PERIOD * enc->gear_ratio;
}

float Encoder_Calc_Spin_Timing(encoder_t *enc)
{
	signed long now;
	signed long time_start;
	signed long time_end;
	
	char buffer_start;
	char buffer_end;
	char dir;
	
	char got_enough;
	
	/**/ disable_encoder_interrupts(); /**/
	
	got_enough = enc->got_enough;
	dir = enc->last_dir;
	
	buffer_start = enc->time_buffer_index;
	buffer_end   = (enc->time_buffer_index + (ENCODER_BUFFER_SIZE-1))
		% ENCODER_BUFFER_SIZE;
	
	time_end   = enc->time_buffer[buffer_end];
	time_start = enc->time_buffer[buffer_start];
	
	/**/ enable_encoder_interrupts(); /**/
	
	now = Get_Timer_Zero_Locked();
	
	if (! got_enough) {
		return 0.0;
	}
	
	if (now - time_end >= TICK_WAIT_TIMEOUT) {
		time_end = now;
	}
	
	return (float)((ENCODER_BUFFER_SIZE-1) * dir)
		/ ( (time_end-time_start)*TIMER_DELTA ) * enc->gear_ratio;
}

float Encoder_Calc_Speed_Timing(encoder_t *enc)
{
	return Encoder_Calc_Spin_Timing(enc) / TICKS_PER_METER;
}

void Encoder_Reset_Delta(void)
{
	char i;
	
	for (i=0; i<NUM_ENCODERS; i++) {
		encoders[i].last_count = encoders[i].count;
	}
}

float Encoder_Get_Angle(void)
{
	float d1, d2;
	
	d1 = encoders[0].count * encoders[0].gear_ratio;
	d2 = encoders[1].count * encoders[0].gear_ratio;
	
	return (d2 - d1) / 2.0 / TICKS_PER_ROBOT_RADIAN;
}

float Encoder_Get_Distance(void)
{
	float d1, d2;
	
	d1 = encoders[0].count * encoders[0].gear_ratio;
	d2 = encoders[1].count * encoders[0].gear_ratio;
	
	return (d1 + d2) / 2.0 / TICKS_PER_METER;
}
