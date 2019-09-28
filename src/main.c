/* Name: main.c
 * Author: <insert your name here>
 * Copyright: <insert your copyright message here>
 * License: <insert your license reference here>
 */

#include "teensy_general.h"  // includes the resources included in the teensy_general.h file
#include "t_usb.h"
#define PRINTNUM(x) m_usb_tx_uint(x); m_usb_tx_char(10);m_usb_tx_char(13); //Print number x and start off a new line

unsigned int startofpulse, endofpulse, pulsewidth;
int main(void)
{
    m_usb_init();
    set(TCCR3B,CS30);
    set(TCCR3B,CS31);
    set(TCCR3B,ICES3);
    for(;;)
    {
      while (!bit_is_set(TCCR3B,ICF3));
      startofpulse = ICR3;
      set(TCCR3B,ICF3);
      toggle(TCCR3B,ICES3);
      while (!bit_is_set(TCCR3B,ICF3));
      endofpulse = ICR3;
      pulsewidth = endofpulse - startofpulse;
      set(TCCR3B, ICF3);
      toggle(TCCR3B,ICES3);
      if (pulsewidth < something)
      {
        
      }



    }

    return 0;   /* never reached */
}
