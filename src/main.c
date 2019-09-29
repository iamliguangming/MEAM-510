/* Name: main.c
 * Author: <insert your name here>
 * Copyright: <insert your copyright message here>
 * License: <insert your license reference here>
 */

#include "teensy_general.h"  // includes the resources included in the teensy_general.h file
#include "t_usb.h"
#define PRINTNUM(x) m_usb_tx_uint(x); m_usb_tx_char(10);m_usb_tx_char(13); //Print number x and start off a new line
#define PRINTSTRING(x) m_usb_tx_string(x); m_usb_tx_char(10); m_usb_tx_char(13);

int xflag = 0;
int syncflag = 0;
unsigned int startofpulse, endofpulse, pulsewidth;
unsigned int lastY, lastX, lastsync;

int main(void)
{
    m_usb_init();
    set(TCCR3B,ICES3);
    set(TCCR3B,CS31);
    set(TCCR3B,CS30);

    teensy_wait(200);
    PRINTSTRING("Please wait for started");

    for(;;)
    {

      while (!bit_is_set(TIFR3,ICF3));
      startofpulse = ICR3;
      set(TIFR3,ICF3);
      toggle(TCCR3B,ICES3);
      while (!bit_is_set(TIFR3,ICF3));
      endofpulse = ICR3;
      pulsewidth = endofpulse - startofpulse;
      set(TIFR3, ICF3);
      toggle(TCCR3B,ICES3);
      if (pulsewidth >= 12 && pulsewidth < 68)
      {
        // PRINTNUM(1);
        if (syncflag == 0)
        {
          syncflag = 1;
        }
        else if (syncflag ==1)
        {
          xflag = 1;
          syncflag = 0;
        }
      lastsync = startofpulse;
      }


      if (pulsewidth > 2 && pulsewidth < 6)
      {
         // PRINTNUM(0);
          if (xflag == 0)
          {
            lastY = startofpulse - lastsync;

            syncflag = 0;
          }
          if (xflag != 0)
          {
            lastX = startofpulse - lastsync;

            syncflag = 0;
            xflag = 0;

          }
      }
      PRINTSTRING("The time between last X Y pulse and Sync pulse is:");
      m_usb_tx_uint(lastX);
      m_usb_tx_char(3);
      PRINTNUM(lastY);
    }



    return 0;   /* never reached */
}
