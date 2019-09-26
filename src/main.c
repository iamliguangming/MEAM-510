/* Name: main.c
 * Author: <insert your name here>
 * Copyright: <insert your copyright message here>
 * License: <insert your license reference here>
 */

#include "teensy_general.h"  // includes the resources included in the teensy_general.h file
#include "t_usb.h"
#define PRINTNUM(x) m_usb_tx_uint(x); m_usb_tx_char(10);m_usb_tx_char(13); //Print number x and start off a new line

unsigned int oldtime, tperiod;
void waitfortrigger();
int main(void)
{
    m_usb_init();
    set(DDRD,2);
    set(DDRD,1);
    set(TCCR3B,CS30);
    set(TCCR3B,CS32);

    for(;;)
    {
      waitfortrigger();
      if(tperiod >= 52)
      {
        set(PORTD,2);
        clear(PORTD,1);
        PRINTNUM(tperiod);
      }
      else if (tperiod < 52)
      {
        set(PORTD,1);
        clear(PORTD,2);
        PRINTNUM(tperiod);
      }

    }

    return 0;   /* never reached */
}
void waitfortrigger()
{
  while(!bit_is_set(TIFR3,ICF3));
  set(TIFR3,ICF3);
  tperiod = ICR3 - oldtime;
  oldtime = ICR3;
}
