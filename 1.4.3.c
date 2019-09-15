/* Name: main.c
 * Author: <insert your name here>
 * Copyright: <insert your copyright message here>
 * License: <insert your license reference here>
 */

#include "teensy_general.h"  // includes the resources included in the teensy_general.h file

void pulse(float increasetime, float decreasetime, float maxdutycycle);

int main(void)
{
    teensy_clockdivide(0); //set the clock speed
    teensy_led(ON);			// turn on the on board LED
    teensy_wait(1000);		// wait 1000 ms when at 16 MHz
    /* insert your hardware initialization here */
    for(;;){
      int i = 0;
        /* insert your main loop code here */
        while (i<20)
        {

        pulse(0.1,0.4,(19.0-i)/19.0);
        pulse(0.1,0.4,0.5*(19.0-i)/19.0);
        teensy_led(OFF);
        teensy_wait(2000);
        teensy_led(ON);
        i= i + 1;
        }
        // pulse(0.1,0.4,1);
        // pulse(0.1,0.4,0.5);
      }


    return 0;   /* never reached */
}

void pulse(float a, float b, float c)
{
  float blinkfrequency = 50;
  float dutycycle = 0.0;
  while (dutycycle <= c)
  {
   teensy_led(TOGGLE);	// switch the led state
   teensy_wait(1/blinkfrequency*1000*(1-dutycycle));		// wait for the blink interval
   teensy_led(TOGGLE);	// switch the led state
   teensy_wait(1/blinkfrequency*1000*dutycycle);		// wait for the blink interval
   dutycycle = dutycycle + c/blinkfrequency/a;
 }
 while (dutycycle >= 0)
 {
  teensy_led(TOGGLE);	// switch the led state
  teensy_wait(1/blinkfrequency*1000*(1-dutycycle));		// wait for the blink interval
  teensy_led(TOGGLE);	// switch the led state
  teensy_wait(1/blinkfrequency*1000*dutycycle);		// wait for the blink interval
  dutycycle = dutycycle - c/blinkfrequency/b;
}

}
