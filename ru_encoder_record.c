
#include "ru_encoder.h"
#include "ru_encoder_record.h"
#include "ru_config.h"
#include "ru_timer.h"
#include "ru_input.h"

encoder_record_t encoder_records[NUM_ENCODER_RECORDS] = {
	{ 1 }
};

void Encoder_Record_Tick(encoder_record_t *rec)
{
	int delta;
	signed long time;
	
	time = Get_Timer_Zero_Unlocked();
	
	delta = (int) (time - rec->last_time);
	rec->last_time = time;
	
	if (rec->delta_index < MAX_COUNTS) {
		rec->deltas[rec->delta_index] = delta;
		rec->dirs[rec->delta_index]   = Read_Interrupt_Digital(rec->pin);
		rec->delta_index++;
	}
	else {
		rec->maxed_out = 1;
	}
}

void Encoder_Record_Print_Reset(encoder_record_t *rec, int id)
{
	char i;
	static char delta_index_copy;
	static int delta_copy[MAX_COUNTS];
	static char dir_copy[MAX_COUNTS];
	static char maxed_out_copy;
	
	/**/ disable_encoder_interrupts(); /**/
	
	delta_index_copy = rec->delta_index;
	
	for (i=0; i<rec->delta_index; i++) {
		delta_copy[i] = rec->deltas[i];
		dir_copy[i]   = rec->dirs[i];
	}
	maxed_out_copy = rec->maxed_out;
	
	rec->delta_index = 0;
	rec->maxed_out   = 0;
	
	/**/ enable_encoder_interrupts(); /**/
	
	for (i=0; i<delta_index_copy; i++) {
		printf("%d,%d,%d\n", id, delta_copy[i], dir_copy[i]);
	}
	if (maxed_out_copy) {
		printf("%d ...............\n", id);
	}
}

void Encoder_Record_Init(void)
{
}

void Encoder_Record_Routine(void)
{
	char i;
	
	for (i=0; i<NUM_ENCODER_RECORDS; i++) {
		Encoder_Record_Print_Reset(encoder_records + i, i);
	}
	
	pwm01 = 150;
}
