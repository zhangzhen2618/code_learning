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

Filename:     getkey.c
Target:       cc2510
Author:       efu
Revised:      31/1-2006
Revision:     1.0
******************************************************************************/

//-----------------------------------------------------------------------------
// See hal.h for a description of this function.
//-----------------------------------------------------------------------------
#include "hal.h"

char getkey ()
{
   char c;
   // Turning on reception
   U0CSR |= UART_ENABLE_RECEIVE;

   while (!URX0IF);
   c = U0DBUF;
   URX0IF = FALSE;

   return c;
}