/* Name: main.c
 * Author: <Yupeng Li>
 * Copyright: <insert your copyright message here>
 * License: <insert your license reference here>
 */

#include "teensy_general.h"  // includes the resources included in the teensy_general.h file

float blinkfrequency=50;//set the blink frequency to be 50Hz
float dutycycle = 0.0;//set the duty cycle of the systeam
float timetoincrease = 0.3;//set the time it takes to increase to maximum to be 0.3
float timetodecrease = 0.7;//set the time it takes to drop to minimum to be 0.7
int main(void)
{

    teensy_led(ON);			// turn on the external LED
    teensy_wait(1000);		// wait 1000 ms when at 16 MHz
    /* insert your hardware initialization here */
    for(;;){
        /* insert your main loop code here */
        while (dutycycle <= 1)//gradually increase the intensity to max
        {
         teensy_led(TOGGLE);	// switch the led state
         teensy_wait(1/blinkfrequency*1000*(1-dutycycle));		// wait for the blink interval
         teensy_led(TOGGLE);	// switch the led state
         teensy_wait(1/blinkfrequency*1000*dutycycle);		// wait for the blink interval
         dutycycle = dutycycle + 1/blinkfrequency/timetoincrease;//increase the intensity each loop by the period divided by time to increase
       }
       while (dutycycle >= 0)//gradually drop the intensity to 0
       {
        teensy_led(TOGGLE);	// switch the led state
        teensy_wait(1/blinkfrequency*1000*(1-dutycycle));		// wait for the blink interval
        teensy_led(TOGGLE);	// switch the led state
        teensy_wait(1/blinkfrequency*1000*dutycycle);		// wait for the blink interval
        dutycycle = dutycycle - 1/blinkfrequency/timetoincrease;//decrease the intensity each loop by the period divided by time to increase
      }
      }

    }
    return 0;   /* never reached */
}
