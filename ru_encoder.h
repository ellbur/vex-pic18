
#ifndef _ru_encoder_h
#define _ru_encoder_h 1

#define NUM_ENCODERS 2

#define TICK_WAIT_TIMEOUT ((signed long) 2000)
#define TICKS_PER_METER ((float) 1088.6) // Wrong. Needs to be measured.

// Make this 1 more than a multiple of 4
#define ENCODER_BUFFER_SIZE 25

#define disable_encoder_interrupts() { INTCON3bits.INT2IE = 0; INTCON3bits.INT3IE = 0; INTCONbits.RBIE = 0; }
#define enable_encoder_interrupts()  { INTCON3bits.INT2IE = 1; INTCON3bits.INT3IE = 1; INTCONbits.RBIE = 1; }

typedef struct {
	
	char dig_a;
	char dig_b;
	
	float gear_ratio;
	
	signed long count;
	signed long abs_count;
	signed char last_dir;
	
	signed long last_count;
	
	signed long time_buffer[ENCODER_BUFFER_SIZE];
	char time_buffer_index;
	char got_enough;
	
} encoder_t;

typedef enum {
	ENC_A = 0,
	ENC_B = 1
} encoder_channel_t;

extern encoder_t encoders[NUM_ENCODERS];

void Encoder_Init(void);
void Encoder_Tick(encoder_t *enc, encoder_channel_t channel);

float Encoder_Calc_Speed_Counting(encoder_t *enc);
float Encoder_Calc_Spin_Counting(encoder_t *enc);
float Encoder_Calc_Speed_Timing(encoder_t *enc);
float Encoder_Calc_Spin_Timing(encoder_t *enc);

float Encoder_Get_Angle(void);
float Encoder_Get_Distance(void);

// Call once on a slow loop
void Encoder_Reset_Delta(void);

#endif
