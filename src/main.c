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
    clear(DDRC,6);
    set(DDRD,2);
    while(1)
    {
    if (bit_is_set(PORTC,6))
    {
      clear(PORTD,2);
    }
    else if (!bit_is_set(PORTC,6))
    {
      set(PORTD,2);
    }
}

    return 0;   /* never reached */
}
