/*******************************************************************************
* FILE NAME: user_routines_fast.c <VEX VERSION>
*
* DESCRIPTION:
*  This file is where the user can add their custom code within the framework
*  of the routines below. 
*
* USAGE:
*  You can either modify this file to fit your needs, or remove it from your 
*  project and replace it with a modified copy. 
*
* OPTIONS:  Interrupts are disabled and not used by default.
*
*******************************************************************************/

#include "ifi_aliases.h"
#include "ifi_default.h"
#include "ifi_utilities.h"
#include "user_routines.h"
#include "printf_lib.h"
#include "delays.h"
#include "ru_slow_loop.h"


/*** DEFINE USER VARIABLES AND INITIALIZE THEM HERE ***/


/*******************************************************************************
* FUNCTION NAME: InterruptVectorLow
* PURPOSE:       Low priority interrupt vector
* CALLED FROM:   nowhere by default
* ARGUMENTS:     none
* RETURNS:       void
* DO NOT MODIFY OR DELETE THIS FUNCTION 
*******************************************************************************/
#pragma code InterruptVectorLow = LOW_INT_VECTOR
void InterruptVectorLow (void)
{
  _asm
    goto InterruptHandlerLow  /*jump to interrupt routine*/
  _endasm
}

/* InterruptHandlerLow has been moved!!!!
 *
 * to ru_interrupts.h
 */

/*******************************************************************************
* FUNCTION NAME: User_Autonomous_Code
* PURPOSE:       Execute user's code during autonomous robot operation.
* You should modify this routine by adding code which you wish to run in
* autonomous mode.  It will be executed every program loop, and not
* wait for or use any data from the Operator Interface.
* CALLED FROM:   main.c file, main() routine when in Autonomous mode
* ARGUMENTS:     none
* RETURNS:       void
*******************************************************************************/
void User_Autonomous_Code(void)
{
  printf("Entering auto\n");
	
  /* Initialize all PWMs and Relays when entering Autonomous mode, or else it
     will be stuck with the last values mapped from the joysticks.  Remember, 
     even when Disabled it is reading inputs from the Operator Interface. 
  */
  pwm01 = pwm02 = pwm03 = pwm04 = 127;
  pwm05 = pwm06 = pwm07 = pwm08 = 127;
  pwm09 = pwm10 = pwm11 = pwm12 = 127;

  while (autonomous_mode)   /* DO NOT CHANGE! */
  {
    if (statusflag.NEW_SPI_DATA)      /* 18.5ms loop area */
    {
      Getdata(&rxdata);   /* DO NOT DELETE, or you will be stuck here forever! */

     /* Add your own code here. */
      //printf("%2x : %2x %2x %2x %2x %2x %2x\n",(int)rxdata.rc_receiver_status_byte.allbits,
       // (int)PWM_in1,(int)PWM_in2,(int)pwm01,(int)pwm02,(int)pwm03,(int)pwm04);
	
	   RU_Auto_Slow_Loop();
	   
      Putdata(&txdata);   /* DO NOT DELETE, or you will get no PWM outputs! */
    }
  }
}


/*******************************************************************************
* FUNCTION NAME: Process_Data_From_Local_IO
* PURPOSE:       Execute user's realtime code.
* You should modify this routine by adding code which you wish to run fast.
* It will be executed every program loop, and not wait for fresh data 
* from the Operator Interface.
* CALLED FROM:   main.c
* ARGUMENTS:     none
* RETURNS:       void
*******************************************************************************/
void Process_Data_From_Local_IO(void)
{
  /* Add code here that you want to be executed every program loop. */

}


/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
