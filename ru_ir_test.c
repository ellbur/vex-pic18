
#include "ru_ir_test.h"
#include "ru_ir.h"
#include "ru_config.h"

void IR_Test_Init(void)
{
	
}

void IR_Test_Routine(void)
{
	static int loop = 0;
	
	printf("%d %d %d %d %d %d\n",
		(int) loop,
		(int) Get_Front_IR(),
		(int) Get_Side_Front_IR(),
		(int) Get_Side_Rear_IR(),
		(int) Get_Rear_IR(),
		(int) Get_Front_Low_IR()
	);
	
	loop++;
}
