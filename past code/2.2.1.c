/* Name: 2.2.1.c
 * Author: <Yupeng Li>
 * Copyright: <insert your copyright message here>
 * License: <insert your license reference here>
 */

#include "teensy_general.h"  // includes the resources included in the teensy_general.h file
#include "t_usb.h"//include the usb headerfile

int main(void)
{
    m_usb_init();//initialize the usb com
    set(DDRD,2);//Set D2 to be the LED output
    set(TCCR3B,CS30);//set clockspeed to be 1/1024
    set(TCCR3B,CS32);//set clockspeed to be 1/1024

    for(;;)//a forever going loop
    {
    if (bit_is_set(PINC,7))//when light is not on the phototransistor
    {
      clear(PORTD,2);//dim the external LED
      while(bit_is_set(PINC,7));//wait until the status of the phototransistor changes

    }
    else if (!bit_is_set(PINC,7))//when light is on the phototransistor
    {
      set(PORTD,2);//light up the external LED
      while(!bit_is_set(PINC,7));//wait until the status of the phototransistor changes
    }
}

    return 0;   /* never reached */
}
