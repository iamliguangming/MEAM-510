/* Name: main.c
 * Author: <Yupeng Li>
 * Copyright: <insert your copyright message here>
 * License: <insert your license reference here>
 */

#include "teensy_general.h"  // includes the resources included in the teensy_general.h file

float blinkfrequency=0.5;//set the blink frequency to be any frequency you want
float dutycycle = 0.8;//set the duty cycle from 0 as 0% to 1 as 100%
int main(void)
{
    teensy_led(ON);			// turn on the on board LED
    teensy_wait(1000);		// wait 1000 ms when at 16 MHz
    /* insert your hardware initialization here */
    for(;;){
        /* insert your main loop code here */
         teensy_led(TOGGLE);	// switch the led state
         teensy_wait(1/blinkfrequency*1000*(1-dutycycle));		// wait for the blink interval
         teensy_led(TOGGLE);	// switch the led state
         teensy_wait(1/blinkfrequency*1000*dutycycle);		// wait for the blink interval
//the blink interval here equals period * dutycycle for the high and period *(1-dutycycle) for low

    }
    return 0;   /* never reached */
}
