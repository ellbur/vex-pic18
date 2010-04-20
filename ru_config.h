
#ifndef _ru_config_h
#define _ru_config_h 1

#define nitish 0
#define kevin  1

#define PI                      ((float) 3.14159265358979)

#include "ru_io.h"

#if PIC
#include "printf_lib.h"
#endif

#if PIC
#define SLOW_LOOP_PERIOD ((float)18.6e-3)
#endif

#endif
