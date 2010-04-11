
#ifndef _ru_sample_h
#define _ru_sample_h 1

#define _recording 0

extern unsigned char watch_bytes[5][11];
extern char recording;

void Watch_Routine(void);

void Record_Watch_Bytes(void);
void Print_Watch_Bytes(void);

#endif
