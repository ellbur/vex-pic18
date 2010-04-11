
#include "ru_sample.h"
#include "ru_config.h"
#include "ifi_default.h"

unsigned char watch_bytes[5][11];
static int timers[5];

static int record_index;
static int timer;
static int print_index;

char recording = 1;

void Watch_Routine(void)
{
	if (recording && timer%1000 == 0) {
		Record_Watch_Bytes();
	}
	
	Print_Watch_Bytes();
	
	timer++;
}

void Record_Watch_Bytes(void)
{
	int i;
	int j;
	
	i = record_index % 5;
	
	for (j=0; j<9; j++) {
		watch_bytes[i][j] = rxdata.reserve[j];
	}
	
	watch_bytes[i][9]  = rxdata.rc_mode_byte.allbits;
	watch_bytes[i][10] = rxdata.rc_receiver_status_byte.allbits;
	
	timers[i] = timer;
	
	record_index++;
}

void Print_Watch_Bytes(void)
{
	int i, j;
	
	i = print_index%5;
	
	printf("%d ", (int) timers[i]);
	for (j=0; j<11; j++) {
		printf("%d ", (int) watch_bytes[i][j]);
	}
	printf("\n");
	
	print_index++;
}
