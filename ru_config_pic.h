
#ifndef _ru_config_pic_h
#define _ru_config_pic_h 1

#include "ru_config.h"

#include "ru_io_aliases_pic.h"
#include "ru_io_pic.h"

#include "ifi_aliases.h"
#include "ifi_default.h"
#include "ifi_utilities.h"
#include "ifi_picdefs.h"
#include "printf_lib.h"

#ifndef SLOW_LOOP_PERIOD
#define SLOW_LOOP_PERIOD        ((float) 18.6e-3)
#endif

#define PI                      ((float) 3.14159265358979)

#define enable_drive_pid 0

extern unsigned char not_wired;

#endif
