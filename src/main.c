/* Name: main.c
 * Author: <insert your name here>
 * Copyright: <insert your copyright message here>
 * License: <insert your license reference here>
 */

#include "teensy_general.h"  // includes the resources included in the teensy_general.h file
#include "t_usb.h"
#define PRINTNUM(x) m_usb_tx_uint(x); m_usb_tx_char(10);m_usb_tx_char(13); //Print number x and start off a new line

unsigned int oldtime, tperiod, startofpulse, endofpulse;
unsigned int pulsewidth;
void waitfortrigger();
int main(void)
{
    m_usb_init();
    set(TCCR3B,CS30);
    set(TCCR3B,CS31);
    set(TCCR3B,ICES3)
    for(;;)
    {
      waitfortrigger();
    }

    return 0;   /* never reached */
}
void waitfortrigger()
{
  while(!bit_is_set(TIFR3,ICF3));
  set(TIFR3,ICF3);
  tperiod = ICR3 - oldtime;
  if (tperiod > 3)
  {
  oldtime = ICR3;
  if (bit_is_set(TCCR3B,ICES3))
    {
    startofpulse = ICR3;
    }
  else if (!bit_is_set(TCCR3B,ICES3))
    {
    endofpulse = ICR3;
    }
  if (startofpulse != 0 && endofpulse !=0)
    {
      pulsewidth = endofpulse - startofpulse;
      startofpulse = 0;
      endofpulse = 0;
    }
  }
}
