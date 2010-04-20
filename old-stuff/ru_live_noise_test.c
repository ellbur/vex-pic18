
#include "ru_live_noise_test.h"
#include "ru_io_aliases.h"
#include "ru_config.h"

#include "printf_lib.h"
#include "ifi_aliases.h"
#include "ifi_default.h"
#include "ifi_utilities.h"

void RU_Live_Noise_Test(void)
{
	printf("%d\n", Get_Analog_Value(IR_SENSOR));
}
