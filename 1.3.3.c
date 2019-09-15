/* Name: main.c
 * Author: <insert your name here>
 * Copyright: <insert your copyright message here>
 * License: <insert your license reference here>
 */

#include "teensy_general.h"  // includes the resources included in the teensy_general.h file


int COMPAREVALUE = 390;
int main(void)
{
  DDRC |= 0x40;
  set(TCCR3A,COM3A1);
  set(TCCR3B,WGM32);
  set(TCCR3A,WGM31);
  set(TCCR3A,WGM30);
  set(TCCR3B,CS30);
  set(TCCR3B,CS32);
  OCR3A = COMPAREVALUE;
    while(1);

    return 0;   /* never reached */
}
