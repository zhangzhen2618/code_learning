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

Filename:     adcSampleSingle.c
Target:       cc2510
Author:       EFU
Revised:      31/1-2006
Revision:     1.0
*******************************************************************************/
#include "hal.h"

//-----------------------------------------------------------------------------
// See hal.h for a description of this function.
//-----------------------------------------------------------------------------
INT16 halAdcSampleSingle(BYTE reference, BYTE resolution, UINT8 input) {
    BYTE volatile temp;
    INT16 value;

    //reading out any old conversion value
    temp = ADCH;
    temp = ADCL;


    ADC_ENABLE_CHANNEL(input);
    ADC_STOP();

    ADC_SINGLE_CONVERSION(reference | resolution | input);

    while (!ADC_SAMPLE_READY());

    ADC_DISABLE_CHANNEL(input);

    value = (((INT16)ADCH) << 8);
    value |= ADCL;
    
    ADC_STOP();

    resolution >>= 3;
    return value >> (8 - resolution);
}
