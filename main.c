/* Name: main.c
 * Author: <insert your name here>
 * Copyright: <insert your copyright message here>
 * License: <insert your license reference here>
 */

#include "teensy_general.h"  // includes the resources included in the teensy_general.h file

float blinkfrequency=0.5;//set the blink frequency to be 50Hz
float dutycyle = 0.5
int main(void)
{
    teensy_clockdivide(0); //set the clock speed
    teensy_led(ON);			// turn on the on board LED
    teensy_wait(1000);		// wait 1000 ms when at 16 MHz
    /* insert your hardware initialization here */
    for(;;){
        /* insert your main loop code here */
        teensy_led(TOGGLE);	// switch the led state
        teensy_wait(1/blinkfrequency/2*1000*(1-dutycyle));		// wait for the blink interval
        tennsy_led(TOGGLE);
        tennsy_wait(1/blinkfrequency/2*1000*dutycycle);

    }
    return 0;   /* never reached */
}
