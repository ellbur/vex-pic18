
#ifndef _ru_encoder_record_h
#define _ru_encoder_record_h

#define MAX_COUNTS 20

typedef struct {
	
	char pin;
	
	int deltas[MAX_COUNTS];
	char dirs[MAX_COUNTS];
	int delta_index;
	
	signed long last_time;
	
	char maxed_out;
	
} encoder_record_t;

#define NUM_ENCODER_RECORDS 1
extern encoder_record_t encoder_records[NUM_ENCODER_RECORDS];

void Encoder_Record_Tick(encoder_record_t *rec);
void Encoder_Record_Print_Reset(encoder_record_t *rec, int id);

void Encoder_Record_Init(void);
void Encoder_Record_Routine(void);

#endif
