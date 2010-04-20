
#include "ru_elbow_pickup_test.h"
#include "ru_elbow_pickup.h"
#include "ru_motor.h"
#include "ru_config.h"

typedef enum {
	WAITING,
	ACTIVE
} elbow_pickup_test_state_t;

elbow_pickup_test_state_t elbow_pickup_test_state;

void Elbow_Pickup_Test_Routine(void)
{
	int button;
	
	button = Bang_Bang(To_S(PICKUP_BUTTON));
	
	switch (elbow_pickup_test_state) {
		case WAITING:
			
			if (button > 0) {
				elbow_pickup_test_state = ACTIVE;
				Elbow_Pickup_Init();
			}
			break;
		
		case ACTIVE:
			Elbow_Pickup_Routine();
			
			if (elbow_pickup_done) {
				elbow_pickup_test_state = WAITING;
			}
			
			break;
	}
}
