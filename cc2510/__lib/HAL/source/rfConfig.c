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

Filename:     rfConfig.c
Target:       cc2510
Author:       EFU
Revised:      31/1-2006
Revision:     1.0
******************************************************************************/
#include "hal.h"


//-----------------------------------------------------------------------------
// See hal.h for a description of this function.
//-----------------------------------------------------------------------------
BOOL halRfConfig(UINT32 frequency)
{
   BOOL status;

   //Turning on crystal oscillator
   SET_MAIN_CLOCK_SOURCE(CRYSTAL);

   // Setting the frequency
   halRfSetRadioFrequency(frequency);


   if (frequency > 2400000)
   {
// 250kbps FSK setup (for other data rates or modulation formats, please see SmartRF Studio)
      // Dynamic packet length and append status
      PKTLEN = 0xFF;
      PKTCTRL0 = 0x05;
      PKTCTRL1 = 0x04;

      // IF frequency
      FSCTRL1 = 0x0C;

      // filter BW, data rate,
      MDMCFG4 = 0x4D;
      MDMCFG3 = 0x3B;

      // Modulation format, detection level
      MDMCFG2 = 0x03;
      MDMCFG1 = 0x22;
      MDMCFG0 = 0xF8;

      // Deviation setting
      DEVIATN = 0x62;

      // Calibration synth
      MCSM0 = 0x10;

      // Frequency offset compensation configuration
      FOCCFG = 0x2D;

      // Bit synchronization
      BSCFG = 0x6C;

      // AGC settings
      AGCCTRL2	= 0x83;
      AGCCTRL1	= 0x40;
      AGCCTRL0	= 0x91;

      // Front end settings (from SmartRf04)
      FREND1 = 0x56;
      FREND0 = 0x10;

      // Synth calibration
      FSCAL3 = 0xA9;
      FSCAL2 = 0x0A;
      FSCAL1 = 0x00;
      FSCAL0 = 0x11;

      // Output power
      PA_TABLE0 = 0xFF;

      // Calibrating synth.
      SIDLE();
      SCAL();
      while(MARCSTATE != 0x01);

      INT_SETFLAG(INUM_RFTXRX,INT_CLR);

      status = TRUE;
   }
   else {
      status = FALSE;
   }

   return status;
}
