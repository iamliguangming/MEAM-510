/* Name: main.c
 * Author: <insert your name here>
 * Copyright: <insert your copyright message here>
 * License: <insert your license reference here>
 */

#include "teensy_general.h"  // includes the resources included in the teensy_general.h file
#include "t_usb.h"

int main(void)
{
    m_usb_init();
    set(DDRD,2);
    set(TCCR3B,CS30);
    set(TCCR3B,CS32);

    for(;;)
    {
    if (bit_is_set(PINC,7))
    {
      clear(PORTD,2);
      while(bit_is_set(PINC,7));

    }
    else if (!bit_is_set(PINC,7))
    {
      set(PORTD,2);
      while(!bit_is_set(PINC,7));
    }
}

    return 0;   /* never reached */
}
