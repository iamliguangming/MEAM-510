/* Name: main.c
 * Author: <Yupeng Li>
 * Copyright: <insert your copyright message here>
 * License: <insert your license reference here>
 */

#include "teensy_general.h"  // includes the resources included in the teensy_general.h file

void pulse(float increasetime, float decreasetime, float maxdutycycle);//prototype of the pulse function
int i = 0;//initialize a counter used in the pulse loop
int main(void)
{
    teensy_clockdivide(0); //set the clock speed
    teensy_led(ON);			// turn on the on board LED
    teensy_wait(1000);		// wait 1000 ms when at 16 MHz
    /* insert your hardware initialization here */
    for(;;){
        /* insert your main loop code here */
        int i = 0;//reset the counter
        while (i<20)//continue for 20 loops
        {

        pulse(0.1,0.4,(19.0-i)/19.0);//pulse with max intensity drop each loop
        pulse(0.1,0.4,0.5*(19.0-i)/19.0);//pulse with the secondary max intensity drop each loop
        teensy_led(OFF);//turn led back off
        teensy_wait(2000);//pause for 2 seconds
        teensy_led(ON);//turn the led back on
        i = i + 1;//go to next loop
        }

      }


    return 0;   /* never reached */
}

void pulse(float a, float b, float c) //a pulse function which takes in increase time a, decrease time b and max intensity c
{
  float blinkfrequency = 50;//initialize the blinkfrequency
  float dutycycle = 0.0;//initialize the starting duty cycle to be 0
  while (dutycycle <= c) //increase intensity with time
  {
   teensy_led(TOGGLE);	// switch the led state
   teensy_wait(1/blinkfrequency*1000*(1-dutycycle));		// wait for the blink interval
   teensy_led(TOGGLE);	// switch the led state
   teensy_wait(1/blinkfrequency*1000*dutycycle);		// wait for the blink interval
   dutycycle = dutycycle + c/blinkfrequency/a;//increase the intensity each loop by maxintensity/blinkfrequency/increase time
 }
 while (dutycycle >= 0)//decrease intensity with time
 {
  teensy_led(TOGGLE);	// switch the led state
  teensy_wait(1/blinkfrequency*1000*(1-dutycycle));		// wait for the blink interval
  teensy_led(TOGGLE);	// switch the led state
  teensy_wait(1/blinkfrequency*1000*dutycycle);		// wait for the blink interval
  dutycycle = dutycycle - c/blinkfrequency/b;//increase the intensity each loop by maxintensity/blinkfrequency/increase time
}

}//end of pulse function
