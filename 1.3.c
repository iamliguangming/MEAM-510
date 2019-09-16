/* Name: main.c
 * Author: <Yupeng Li>
 * Copyright: <insert your copyright message here>
 * License: <insert your license reference here>
 */

#include "teensy_general.h"  // includes the resources included in the teensy_general.h file


int COMPAREVALUE = 3125;
int main(void)
{
  DDRC |= 0x40; //set C6 as the output port
  set(TCCR3A,COM3A0);//set the pin to toggle when timer reaches OCR3A
  set(TCCR3B,WGM32);//set the timer to work in mode 4 where it runs to OCR3A
  set(TCCR3B,CS30);//apply prescalar 1/64
  set(TCCR3B,CS31);//apply prescaler 1/64
  OCR3A = COMPAREVALUE;//set OCR3A to be 3125 so that the frequency is 2*3125/65536*64/8MHz=20Hz
    while(1);//infinite loop keeps the LED blinking

    return 0;   /* never reached */
}
