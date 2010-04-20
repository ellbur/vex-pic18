
#ifndef _ru_encoder_pic_h
#define _ru_encoder_pic_h 1

#define NUM_ENCODERS 2

#define disable_encoder_interrupts() { INTCON3bits.INT2IE = 0; INTCON3bits.INT3IE = 0; INTCONbits.RBIE = 0; }
#define enable_encoder_interrupts() { INTCON3bits.INT2IE = 1; INTCON3bits.INT3IE = 1; INTCONbits.RBIE = 1; }

typedef struct {
	
	char dig_a;
	char dig_b;
	
	signed long count;
	signed long abs_count;
	
} encoder_t;

typedef enum {
	ENC_A = 0,
	ENC_B = 1
} encoder_channel_t;

extern encoder_t encoders[NUM_ENCODERS];

void Encoder_Init(void);
void Encoder_Tick(encoder_t *enc, encoder_channel_t channel);

long Encoder_Get_Count(encoder_t *enc);

#endif
