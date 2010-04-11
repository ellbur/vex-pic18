
#include "ru_ir_test.h"
#include "ru_ir.h"
#include "ru_config.h"

void IR_Test_Init(void)
{
	
}

void IR_Test_Routine(void)
{
	static int loop = 0;
	
	printf("%d: %d %d %d | %d %d %d\n",
		(int) loop,
		(int) Get_Analog_Value(FRONT_IR),
		(int) Get_Analog_Value(SIDE_FRONT_IR),
		(int) Get_Analog_Value(SIDE_REAR_IR),
		(int) Get_Front_IR(),
		(int) Get_Side_Front_IR(),
		(int) Get_Side_Rear_IR()
	);
	
	loop++;
}
