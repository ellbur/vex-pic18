
#include "ru_bumper.h"
#include "ru_ir.h"

int Get_Bumper(void)
{
	return Get_Rear_IR_In() < rear_ir_thresh;
}
