/* Name: main.c
 * Author: <insert your name here>
 * Copyright: <insert your copyright message here>
 * License: <insert your license reference here>
 */

#include "teensy_general.h"  // includes the resources included in the teensy_general.h file
#include "t_usb.h"
unsigned int oldtime, tperiod;

#define PRINTNUM(x) m_usb_tx_uint(x); m_usb_tx_char(10);m_usb_tx_char(13);

void waitforpress();
void toggle_led();


int main(void)
{
    m_usb_init();
    set(DDRD,2);
    set(TCCR3B,CS30);
    set(TCCR3B,CS32);
    clear(PORTD,2);

    for(;;)
    {
      waitforpress();

    }

    return 0;   /* never reached */
}

void waitforpress()
{
  while (!bit_is_set(TIFR3,ICF3))
  {
    toggle_led();
    set(TIFR3,ICF3);
    tperiod = ICR3 - oldtime;
    oldtime = ICR3;
    PRINTNUM(tperiod);
  }
}

void toggle_led()
{
  toggle(PORTD,2);
}
