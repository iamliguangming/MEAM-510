/* Name: main.c
 * Author: <insert your name here>
 * Copyright: <insert your copyright message here>
 * License: <insert your license reference here>
 */

#include "teensy_general.h"  // includes the resources included in the teensy_general.h file

float dutycycle = 0.5; //manually input the dutycycle
int COMPAREVALUE = dutycycle * 1023;//calculate the compare value based on dutycycle
int main(void)
{
  DDRC |= 0x40; //set C6 as the output pin
  set(TCCR3A,COM3A1);//clear at OCR3A, set at rollover
  set(TCCR3B,WGM32);//set the timer to work in mode7 PWM mode
  set(TCCR3A,WGM31);//set the timer to work in mode7 PWM mode
  set(TCCR3A,WGM30);//set the timer to work in mode7 PWM mode
  set(TCCR3B,CS30);//set the prescaler to be 1/1024
  set(TCCR3B,CS32);//set the prescaler to be 1/1024
  OCR3A = COMPAREVALUE;//set OCR3A to be a value between 0x0000 to 0x03FF
    while(1);//keep the led blinking

    return 0;   /* never reached */
}
