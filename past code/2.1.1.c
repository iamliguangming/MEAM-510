/* Name: 2.1.1.c 
 * Author: <Yupeng Li>
 * Copyright: <insert your copyright message here>
 * License: <insert your license reference here>
 */

#include "teensy_general.h"  // includes the resources included in the teensy_general.h file
#include "t_usb.h" //includes the resources included in t_usb.h headerfile
#define PRINTNUM(x) m_usb_tx_uint(x); m_usb_tx_char(10);m_usb_tx_char(13); //Print number x and start off a new line

int main(void)//the main function
{
    m_usb_init();//initialize usb communication
    set(DDRD,2);//set D2 as the ouput port
    set(TCCR3B,CS30);//set clock frequency to be /1024
    set(TCCR3B,CS32);//set clock frequency to be /1024

    for(;;)// The code will keep going
    {
    if (bit_is_set(PINC,6))//when the switch is open
    {
      clear(PORTD,2);//turn off the LED on D2
      PRINTNUM(TCNT3);//Print the time stamp
      m_usb_tx_string("Now it's off");//Print a string indicating LED is off
      while(bit_is_set(PINC,6));//Keep the led on until the status of the switch changes

    }
    else if (!bit_is_set(PINC,6))//when the switch is pressed
    {
      set(PORTD,2);//turn on the LED on D2
      PRINTNUM(TCNT3);//Print the time stamp
      m_usb_tx_string("Now it's on");//Print a string indicating the LED is on
      while(!bit_is_set(PINC,6));//Keep the swtich on until the switch is open
    }
}

    return 0;   /* never reached */
}
