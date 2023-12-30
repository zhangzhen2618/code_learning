/******************************************************************************
*                                                                             *
*        **********                                                           *
*       ************                                                          *
*      ***        ***                                                         *
*     ***    ++    ***                                                        *
*     ***   +  +   ***                      CHIPCON                           *
*     ***   +                                                                 *
*     ***   +  +   ***                                                        *
*     ***    ++    ***                                                        *
*      ***        ***                                                         *
*       ************                                                          *
*        **********                                                           *
*                                                                             *
*******************************************************************************

Filename:     setTimer2Period.c
Target:       cc2510
Author:       EFU
Revised:      31/1-2006
Revision:     1.0
******************************************************************************/
#include "hal.h"

//-----------------------------------------------------------------------------
// See hal.h for a description of this function.
//-----------------------------------------------------------------------------
BOOL halSetTimer2Period(UINT32 period, UINT8* cnt, UINT8* presc)
{
   BYTE tip = 0;
   UINT16 prescaler = 256;
   UINT8 counter;

   // Times 26 and devided by 64 (crystal clock frequency and minimum tick period of T2).
   period = (UINT32)((float)period * 0.40625);

   // Compensating for TICKSPD.
   period = (period >>  TICKSPD);


   while(period > 65280)
   {
      tip++;
      if(tip == 3)
      {  // Step from 256 to 1024 clock cycles
         period = period >> 1;
      }
      period = period >> 1;
   }

   if(tip > 3)
   {
      return FALSE;
   }

   while(((counter = (period / prescaler))  < 1))
   {
      prescaler--;
   }

   TIMER2_SET_COUNTER(counter);
   TIMER2_SET_PRESCALER(prescaler);
   TIMER2_SET_TICK_PERIOD(tip);

   *cnt = counter;
   *presc = prescaler;

   return TRUE;
}


