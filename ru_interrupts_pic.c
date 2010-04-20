
#include "ru_interrupts_pic.h"
#include "ru_config_pic.h"
#include "ru_encoder_pic.h"

#pragma code
#pragma interruptlow InterruptHandlerLow save=PROD,section("MATH_DATA"),section(".tmpdata")

void InterruptHandlerLow ()     
{                               
	static unsigned char delta;
	static unsigned char portb_old = 0xFF;
	static unsigned char portb = 0xFF;
	static unsigned char edge  = 0;

	// 1
	if (INTCON3bits.INT2IF && INTCON3bits.INT2IE) { 
		INTCON3bits.INT2IF = 0;

		Encoder_Tick(&encoders[0], ENC_A);
		INTCON2bits.INTEDG2 ^= 1;
	}
	
	// 2
	else if (INTCON3bits.INT3IF && INTCON3bits.INT3IE) {
		INTCON3bits.INT3IF = 0;

		Encoder_Tick(&encoders[0], ENC_B);
		INTCON2bits.INTEDG3 ^= 1;
	}
	
	else if (INTCONbits.RBIF && INTCONbits.RBIE) {
		portb           = PORTB;
		INTCONbits.RBIF = 0;
		delta           = portb ^ portb_old;
		portb_old       = portb;
	 
		// 3
		if(delta & 0x10) {
			Encoder_Tick(&encoders[1], ENC_A);
		}
		
		// 4
		if(delta & 0x20) {
			Encoder_Tick(&encoders[1], ENC_B);
		}
		
		// 5
		if(delta & 0x40) {
			// Nothing
		}
		
		// 6
		if(delta & 0x80) {
			// Nothing
		}
	}
}
