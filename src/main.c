/* Name: main.c
 * Author: <insert your name here>
 * Copyright: <insert your copyright message here>
 * License: <insert your license reference here>
 */

#include "teensy_general.h"  // includes the resources included in the teensy_general.h file
#include "t_usb.h"
#define PRINTNUM(x) m_usb_tx_uint(x); m_usb_tx_char(10);m_usb_tx_char(13);

int main(void)
{
    m_usb_init();
    clear(DDRC,6);
    set(DDRD,2);
    set(TCCR3B,CS30);
    set(TCCR3B,CS32);
    for(;;)
    {
    if (bit_is_set(PINC,6))
    {
      clear(PORTD,2);
      PRINTNUM(TCNT3);

    }
    else if (!bit_is_set(PINC,6))
    {
      set(PORTD,2);
      PRINTNUM(TCNT3);
    }
}

    return 0;   /* never reached */
}
