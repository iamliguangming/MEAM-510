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
void waitforlift();
float timetoms(float time);
int main(void)
{
   int i=0;
   float totaltime = 0;
   float averagetime = 0;
    m_usb_init();
    set(TCCR3B,CS30);
    set(TCCR3B,CS32);
    m_usb_tx_string("Hit the button to get started!");
    m_usb_tx_char(10);m_usb_tx_char(13);
    waitforpress();
    toggle(TCCR3B,ICES3);
    for(i=3;i>=0;i--)
    {
      PRINTNUM(i);
      teensy_wait(1000);
    }
    m_usb_tx_string("START!!!");
    m_usb_tx_char(10);m_usb_tx_char(13);

    oldtime = 0;
    tperiod = 0;
    ICR3 = 0;
    for(i=1;i<=6;i++)
    {

      waitforpress();
      m_usb_tx_string("time between last hit");
      m_usb_tx_char(13);
      PRINTNUM(tperiod);
      m_usb_tx_char(13);
      toggle(TCCR3B,ICES3);
      if(i>1)
      {
      totaltime = totaltime + tperiod;
      averagetime = timetoms(totaltime/(i-1));

      m_usb_tx_string("The average hitting time is ");
      m_usb_tx_char(13);
      PRINTNUM(averagetime);
      m_usb_tx_char(13);
      }

    }

    while(1);
    return 0;   /* never reached */
}

void waitforpress()
{
  while (!bit_is_set(TIFR3,ICF3));
  set(TIFR3,ICF3);
    tperiod = ICR3 - oldtime;
    oldtime = ICR3;

}
float timetoms(float x)
{
  float timeinms = x*1024/16000;
  return timeinms;
}
// void waitforlift()
// {
//   while(bit_is_set(TIFR3,ICF3));
//   set(TIFR3,ICF3);
//   tperiod = ICR3 - oldtime;
//   oldtime = ICR3;
//
// }
