/* Name: main.c
 * Author: <insert your name here>
 * Copyright: <insert your copyright message here>
 * License: <insert your license reference here>
 */

#include "teensy_general.h"  // includes the resources included in the teensy_general.h file
#include "t_usb.h"
#define PRINTNUM(x) m_usb_tx_uint(x); m_usb_tx_char(10);m_usb_tx_char(13); //Print number x and start off a new line

int syncflag = 0;
int noxyflag = 0;
unsigned int oldtime, tperiod, startofpulse, endofpulse;
unsigned int pulsewidth, lastsynctime,lastxtime,lastytime;
unsigned int xwithsync, ywithsync;
void waitfortrigger();
int main(void)
{
    m_usb_init();
    set(TCCR3B,CS30);
    set(TCCR3B,CS31);
    set(TCCR3B,ICES3);
    for(;;)
    {
      waitfortrigger();
      PRINTNUM(1);
    }

    return 0;   /* never reached */
}

void waitfortrigger()
{
  while(!bit_is_set(TIFR3,ICF3));
  set(TIFR3,ICF3);
  tperiod = ICR3 - oldtime;
  if (tperiod > 3)
  {
  oldtime = ICR3;
  if (bit_is_set(TCCR3B,ICES3))
    {
    startofpulse = ICR3;
    }
  else if (!bit_is_set(TCCR3B,ICES3))
    {
    endofpulse = ICR3;
    }
  if (startofpulse != 0 && endofpulse !=0)
    {
      pulsewidth = endofpulse - startofpulse;
    }

  }
  if (pulsewidth > 3 && pulsewidth <6)//for x,y pulse
  {
    if (syncflag == 0)
    {
      syncflag = 1;
    }
    if (syncflag ==1 )
    {
      noxyflag = 1;
    }
  lastsynctime = endofpulse;

  }
  if (pulsewidth > 12.5 && pulsewidth < 25)//for sync pulse
  {
   if (noxyflag == 1)
   {
     syncflag = 0;
     noxyflag = 0;
     lastxtime = endofpulse;
   }
   if (noxyflag == 0)
   {
     syncflag = 0;
     lastytime = endofpulse;
   }
  }
  xwithsync = lastxtime - lastsynctime;
  m_usb_tx_string("Time between x and sync");
  m_usb_tx_char(10);m_usb_tx_char(13);
  PRINTNUM(xwithsync);
  ywithsync = lastytime - lastsynctime;
  m_usb_tx_string("Time between y and sync");
  m_usb_tx_char(10);m_usb_tx_char(13);
  PRINTNUM(ywithsync);
  toggle(TCCR3B,ICES3);

}
