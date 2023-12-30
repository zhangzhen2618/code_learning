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

Filename:     timer4AdmReset.c
Target:       cc2510
Author:       EFU
Revised:      31/1-2006
Revision:     1.0
******************************************************************************/

#include "cul.h"


extern volatile TIMER4_TABLE_ENTRY timer4Table[TIMER_ADM_TABLE_LENGTH];

//-----------------------------------------------------------------------------
// See cul.h for a description of this function.
//-----------------------------------------------------------------------------
void culTimer4AdmReset(BYTE entry){
   BYTE status;

   // Storing the interrupt enable register, and turning off interrupts
   status = IEN0;
   INT_GLOBAL_ENABLE(INT_OFF);

   // Setting up the table.
   timer4Table[entry].counter = 0;

   // Restoring the interrupt enable status.
   IEN0 = status;
   return;
} // ends culTimer4AdmClear(...)
