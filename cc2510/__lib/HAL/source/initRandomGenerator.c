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

Filename:     initRandomGenerator.c
Target:       cc2510
Author:       EFU
Revised:      31/1-2006
Revision:     1.0
******************************************************************************/
#include"hal.h"


//-----------------------------------------------------------------------------
// See hal.h for a description of this function.
//-----------------------------------------------------------------------------
void halInitRandomGenerator(void)
{

   
   BYTE i;
   //debug:
   BYTE volatile test;

   halRfConfig(2425000);
   
   // Turning on receiver to get output from IF-ADC.
   SRX();
   halWait(1);

   ENABLE_RANDOM_GENERATOR();

   for(i = 0 ; i < 32 ; i++)
   {
      RNDH = RSSI;
      CLOCK_RANDOM_GENERATOR();
   }

   return;
}

