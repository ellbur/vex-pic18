
#ifndef _ru_config_h
#define _ru_config_h 1

#define nitish 1
#define kevin  0

#include "ru_io_aliases.h"
#include "ifi_aliases.h"
#include "ifi_default.h"
#include "ifi_utilities.h"
#include "ifi_picdefs.h"
#include "printf_lib.h"

#define BUTTON_REV_THRESH       ((int)100)
#define BUTTON_FWD_THRESH       ((int)154)
#define NEUTRAL_VALUE           ((int)127)

#define SLOW_LOOP_PERIOD        ((float) 18.6e-3)

#define PI                      ((float) 3.14159265358979)

extern unsigned char not_wired;

#endif
