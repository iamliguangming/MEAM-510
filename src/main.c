/* Name: main.c
 * Author: <Yupeng Li>
 * Copyright: <insert your copyright message here>
 * License: <insert your license reference here>
 */

#include "teensy_general.h"  // includes the resources included in the teensy_general.h file
#include "t_usb.h"//include the usb headerfile
#define PRINTNUM(x) m_usb_tx_uint(x); m_usb_tx_char(10);m_usb_tx_char(13); //Print number x and start off a new line
#define PRINTSTRING(x) m_usb_tx_string(x); m_usb_tx_char(10); m_usb_tx_char(13);//Print string x and start off a new line

int xflag = 0;//set a flag when x should be the short pulse
int synccount = 0;//set a counter for number of synctimes
int yflag = 0;//set a flag when y should be the short pulse
unsigned int startofpulse, endofpulse, pulsewidth;//values that are used to record time of the pulse and pulse width
unsigned int lastY, lastX, lastsync;//values that are used to store last sync time and last x or y pulse time
unsigned int lastXinus, lastYinus;
int main(void)//the main function
{
    m_usb_init();//initiate the usb module
    set(TCCR3B,ICES3);//set the input capture at rising edge
    set(TCCR3B,CS31);//set the clock speed at 1/64
    set(TCCR3B,CS30);//set the clockspeed at 1/64

    teensy_wait(200);//wait for 200 before starting
    PRINTSTRING("Please wait for started");//type a string ask the user to wait for signal

    for(;;)//a loop runs forever
    {

      while (!bit_is_set(TIFR3,ICF3));//wait until a rising edge is captured
      startofpulse = ICR3;//store the rising edge time in startofpulse
      set(TIFR3,ICF3);//reset the input capture flag
      toggle(TCCR3B,ICES3);//change the input capture from rising edge to falling edge
      while (!bit_is_set(TIFR3,ICF3));//wait until a falling edge is captured
      endofpulse = ICR3;//store the falling edge time in a constant
      if (startofpulse > endofpulse)//incase of rollover
      {
        pulsewidth = 65535 - startofpulse + endofpulse;//calculate the actual pulse width
      }
      else//in the case of not rolling over
      {
      pulsewidth = endofpulse - startofpulse;//calculate the pulsewidth based on the rising time and falling time
      }
      set(TIFR3, ICF3);//set the input capture flag
      toggle(TCCR3B,ICES3);//change the input capture from falling edge to rising edge
      if (pulsewidth >= 12 && pulsewidth < 68)//if the pulse width is within the range of a sync pulse
      {
        // PRINTNUM(1);
        synccount = synccount + 1;//the counter for sync pulses increase by 1
        if (synccount > 1 && yflag == 1)//if the counter is greater than 1 and yflag is still set
        {
          yflag = 0;//reset y flag since y signal is missing
        }
        if (synccount == 3)//if the number of counter reaches 3
        {
          xflag = 1;//raise an x flag since if there is a pulse with short pulsewidth coming it must be x
        }
        if (synccount == 4)//if the number of counter reaches 4, x pulse is missing
        {
          synccount = 0;//reset the number of counts so that the system can restart tracking the cycle
          xflag = 0;//reset x flag since x pulse is missing in this case
        }

      lastsync = startofpulse;//record the synctime at the start of its pulse
      }




      if (pulsewidth > 2 && pulsewidth < 6)//if the pulsewidth falls in the range of a x,y signal pulse
      {
         // PRINTNUM(0);
          synccount = 0;//clear the number of counts whenever an x/y signal pulse is detected
          if (yflag == 1)//if the y flag is raised, the incoming signal must be y signal
          {
            if(startofpulse >= lastsync)//in the case of not rolling over
            {
            lastY = startofpulse - lastsync;//record the most recent Y time as the interval between y signal and the last sync

            }
            else if(startofpulse < lastsync)//in the case of rollover
            {
            lastY = 65535 - lastsync + startofpulse;
            lastYinus = lastY*64*1000000/(8*10^6);
            }
            yflag = 0;//clear the y flag

          }
          if (xflag == 1)//if the x flag is already raised,treat this pulse as x pulse
          {
            if (startofpulse >= lastsync)//in the case of not rolling over
             {
               lastX = startofpulse - lastsync; //calculate the time between x pulse and the most recent sync pulse
             }
            else if (startofpulse < lastsync)//in the case of rolling over
            {
              lastX = 65535 - lastsync + startofpulse;
              lastXinus = lastX*64*1000000/(8*10^6);
            }
            yflag = 1;//if we already see an x pulse coming, the next signal pulse must be y pulse, set the y falg here
            xflag = 0;//clear the x flag after the latest x time has been recorded

          }


      }
      PRINTSTRING("The time between last X Y pulse and Sync pulse is:");//print out the time for last x pulse and last y pulse
      m_usb_tx_uint(lastXinus);//print out the last x time
      m_usb_tx_char(3);// print out three spaces
      PRINTNUM(lastYinus);//print out the last y time and print a line
    }



    return 0;   /* never reached */
}
