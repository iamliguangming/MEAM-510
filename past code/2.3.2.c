/* Name: main.c
 * Author: <insert your name here>
 * Copyright: <insert your copyright message here>
 * License: <insert your license reference here>
 */

#include "teensy_general.h"  // includes the resources included in the teensy_general.h file
#include "t_usb.h"//include the usb header file
#define PRINTNUM(x) m_usb_tx_uint(x); m_usb_tx_char(10);m_usb_tx_char(13); //Print number x and start off a new line

unsigned int oldtime, tperiod;//initialized constants to store the oldtime and time interval
void waitfortrigger();//subrountine prototype
int main(void)//main function
{
    m_usb_init();//initialize usb connection
    set(DDRD,2);//make D2 a DC output
    set(DDRD,1);//make D1 a DC output
    set(TCCR3B,CS30);//set prescaler 1/1024
    set(TCCR3B,CS32);//set prescaler 1/1024

    for(;;)//forever running
    {
      waitfortrigger();//wait for the incoming signal
      if(tperiod >= 30)// if the signal is of lower frequency
      {
        set(PORTD,2);//turn on the LED on D2
        clear(PORTD,1);//turn off the LED on D1
        PRINTNUM(tperiod);//print out the interval with last pulse
      }
      else if (tperiod < 30)//if the signal is of higher frequency
      {
        set(PORTD,1);//turn on the LED on D1
        clear(PORTD,2);//turn off the LED on D2
        PRINTNUM(tperiod);//print out the interval between signals
      }

    }

    return 0;   /* never reached */
}
void waitfortrigger()//subroutine which detects incoming pulse and update the pulse interval and oldtime
{
  while(!bit_is_set(TIFR3,ICF3));//wait until there is incoming falling edge
  set(TIFR3,ICF3);//clear the ICF3 flag
  tperiod = ICR3 - oldtime;//calculate the time interval with last pulse
  oldtime = ICR3;//update the oldtime
}
