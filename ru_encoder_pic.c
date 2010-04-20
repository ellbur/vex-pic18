
#include "ru_encoder_pic.h"
#include "ru_config_pic.h"

encoder_t encoders[NUM_ENCODERS] = {
	{ 1, 2 },
	{ 3, 4 }
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

}

long Encoder_Get_Count(encoder_t *enc)
{
	long count;
	
	disable_encoder_interrupts();
	count = enc->count;
	enable_encoder_interrupts();
	
	return count;
}
