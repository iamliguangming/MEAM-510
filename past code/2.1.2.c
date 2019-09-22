/* Name: 2.2.2.c
 * Author: <Yupeng Li>
 * Copyright: <insert your copyright message here>
 * License: <insert your license reference here>
 */

#include "teensy_general.h"  // includes the resources included in the teensy_general.h file
#include "t_usb.h"//include the usb headerfile
unsigned int oldtime, tperiod;//use unsigned integers to store oldtime and period of pressing

#define PRINTNUM(x) m_usb_tx_uint(x); m_usb_tx_char(10);m_usb_tx_char(13);//Macro for printing the number and a line

void waitforpress();//function prototype which stores the time stamp and interval whenever the button is pressed
float timetoms(float time);//function which takes in timestamp and output the time in milliseconds
int main(void)//the main function
{
   int i=0;//counter
   float totaltime = 0;//initialize the total time through the process
   float averagetime = 0;//initialize the average time between each press
    m_usb_init();//initialize usb communication
    set(TCCR3B,CS30);//set the clockspeed to 1/1024
    set(TCCR3B,CS32);//set the clockspeed to 1/1024
    m_usb_tx_string("Hit the button to get started!");//Prompt the user to press the button to start the program
    m_usb_tx_char(10);m_usb_tx_char(13);//print a line
    waitforpress();//wait until the user press the button
    toggle(TCCR3B,ICES3);//change between rising and falling edge since we want to capture both the timestamp at pressing and depressing
    for(i=3;i>=0;i--)//Countdown for user to get prepared
    {
      PRINTNUM(i);//print the time left
      teensy_wait(1000);//delay 1000ms
    }
    m_usb_tx_string("START!!!");//Tell the user to start pressing
    m_usb_tx_char(10);m_usb_tx_char(13);//print a line

    oldtime = 0;//reset oldtime
    tperiod = 0;//reset time interval
    ICR3 = 0;//reset the time count on timer 3
    for(i=1;i<=6;i++)//let the user press 5 times
    {

      waitforpress();//wait for the user to press button
      m_usb_tx_string("time between last hit");//print time between hits
      m_usb_tx_char(13);//print a line
      PRINTNUM(tperiod);//print the time interval
      m_usb_tx_char(13);//print a line
      toggle(TCCR3B,ICES3);//change the time capture between rising edge and falling edge
      if(i>1)//discard the time for the first press which is highly inaccutrate
      {
      totaltime = totaltime + tperiod;//sum up total time
      averagetime = timetoms(totaltime/(i-1));//calculate the average press time dividing total time by number of hits

      m_usb_tx_string("The average hitting time is ");//print the average hitting time
      m_usb_tx_char(13);//print a line
      PRINTNUM(averagetime);//print out the average hitting time
      m_usb_tx_char(13);//print a line
      }

    }

    while(1);//Never going out the loop
    return 0;   /* never reached */
}

void waitforpress()//wait for the user to press
{
  while (!bit_is_set(TIFR3,ICF3));//stay in the loop until ICF3 flag is triggered
  set(TIFR3,ICF3);//clear ICF3 flag by setting ICF3 to 1
    tperiod = ICR3 - oldtime;//calculate the press interval
    oldtime = ICR3;//set the oldetime to be the clocktime

}
float timetoms(float x)//Transform the time from clocktime to time in milliseconds
{
  float timeinms = x*1024/16000;//equation for the /1024 clock
  return timeinms;//return the time in milliseconds
}
