#ifndef __STC89C5xRC_RDP_H__
#define __STC89C5xRC_RDP_H__


#ifdef __SDCC  // this for the sdcc to complie
/////////////////////////////////////////////////

/* The following is STC additional SFR */

/* sfr  AUXR  = 0x8e; */
/* sfr  AUXR1 = 0xa2; */
/* sfr  IPH   = 0xb7; */

__sfr __at (0xe8) P4;
__sbit __at (0xee) P4_6;
__sbit __at (0xed) P4_5;       //ISP下载需要勾选“ALE引脚用在p4.5口
__sbit __at (0xec) P4_4;
__sbit __at (0xeb) P4_3;
__sbit __at (0xea) P4_2;
__sbit __at (0xe9) P4_1;
__sbit __at (0xe8) P4_0;

__sfr __at (0xc0) XICON;

__sfr __at (0xe1) WDT_CONTR;

__sfr __at (0xe2) ISP_DATA;
__sfr __at (0xe3) ISP_ADDRH;
__sfr __at (0xe4) ISP_ADDRL;
__sfr __at (0xe5) ISP_CMD;
__sfr __at (0xe6) ISP_TRIG;
__sfr __at (0xe7) ISP_CONTR;

/* Above is STC additional SFR */

/*--------------------------------------------------------------------------
REG51F.H

Header file for 8xC31/51, 80C51Fx, 80C51Rx+
Copyright (c) 1988-1999 Keil Elektronik GmbH and Keil Software, Inc.
All rights reserved.

Modification according to DataSheet from April 1999
 - SFR's AUXR and AUXR1 added for 80C51Rx+ derivatives
--------------------------------------------------------------------------*/

/*  BYTE Registers  */
__sfr __at (0x80) P0;
__sbit __at (0x80) P0_0;
__sbit __at (0x81) P0_1;
__sbit __at (0x82) P0_2;
__sbit __at (0x83) P0_3;
__sbit __at (0x84) P0_4;
__sbit __at (0x85) P0_5;
__sbit __at (0x86) P0_6;
__sbit __at (0x87) P0_7;

__sfr __at (0x90) P1;
__sbit __at (0x90) P1_0;
__sbit __at (0x91) P1_1;
__sbit __at (0x92) P1_2;
__sbit __at (0x93) P1_3;
__sbit __at (0x94) P1_4;
__sbit __at (0x95) P1_5;
__sbit __at (0x96) P1_6;
__sbit __at (0x97) P1_7;

__sfr __at (0xA0) P2;
__sbit __at (0xA0) P2_0;
__sbit __at (0xA1) P2_1;
__sbit __at (0xA2) P2_2;
__sbit __at (0xA3) P2_3;
__sbit __at (0xA4) P2_4;
__sbit __at (0xA5) P2_5;
__sbit __at (0xA6) P2_6;
__sbit __at (0xA7) P2_7;

__sfr __at (0xB0) P3;
__sbit __at (0xB0) P3_0;
__sbit __at (0xB1) P3_1;
__sbit __at (0xB2) P3_2;
__sbit __at (0xB3) P3_3;
__sbit __at (0xB4) P3_4;
__sbit __at (0xB5) P3_5;
__sbit __at (0xB6) P3_6;
__sbit __at (0xB7) P3_7;

__sfr __at (0xD0) PSW;
__sfr __at (0xE0) ACC;
__sfr __at (0xF0) B;
__sfr __at (0x81) SP;
__sfr __at (0x82) DPL;
__sfr __at (0x83) DPH;
__sfr __at (0x87) PCON;
__sfr __at (0x88) TCON;
__sfr __at (0x89) TMOD;
__sfr __at (0x8A) TL0;
__sfr __at (0x8B) TL1;
__sfr __at (0x8C) TH0;
__sfr __at (0x8D) TH1;
__sfr __at (0xA8) IE;
__sfr __at (0xB8) IP;
__sfr __at (0x98) SCON;
__sfr __at (0x99) SBUF;

/*  80C51Fx/Rx Extensions  */
__sfr __at (0x8E) AUXR;
__sfr __at (0xA2) AUXR1;
__sfr __at (0xA9) SADDR;
__sfr __at (0xB7) IPH;
__sfr __at (0xB9) SADEN;
__sfr __at (0xC8) T2CON;
__sfr __at (0xC9) T2MOD;
__sfr __at (0xCA) RCAP2L;
__sfr __at (0xCB) RCAP2H;
__sfr __at (0xCC) TL2;
__sfr __at (0xCD) TH2;

/* PCA SFR
__sfr __at (0xD8) CCON;
__sfr __at (0xD9) CMOD;
__sfr __at (0xDA) CCAPM0;
__sfr __at (0xDB) CCAPM1;
__sfr __at (0xDC) CCAPM2;
__sfr __at (0xDD) CCAPM3;
__sfr __at (0xDE) CCAPM4;
__sfr __at (0xE9) CL;
__sfr __at (0xEA) CCAP0L;
__sfr __at (0xEB) CCAP1L;
__sfr __at (0xEC) CCAP2L;
__sfr __at (0xED) CCAP3L;
__sfr __at (0xEE) CCAP4L;
__sfr __at (0xF9) CH;
__sfr __at (0xFA) CCAP0H;
__sfr __at (0xFB) CCAP1H;
__sfr __at (0xFC) CCAP2H;
__sfr __at (0xFD) CCAP3H;
__sfr __at (0xFE) CCAP4H;
*/

/*  BIT Registers  */
/*  PSW   */
__sbit __at (0xD7) CY;
__sbit __at (0xD6) AC;
__sbit __at (0xD5) F0;
__sbit __at (0xD4) RS1;
__sbit __at (0xD3) RS0;
__sbit __at (0xD2) OV;
__sbit __at (0xD1) F1;
__sbit __at (0xD0) P;

/*  TCON  */
__sbit __at (0x8F) TF1;
__sbit __at (0x8E) TR1;
__sbit __at (0x8D) TF0;
__sbit __at (0x8C) TR0;
__sbit __at (0x8B) IE1;
__sbit __at (0x8A) IT1;
__sbit __at (0x89) IE0;
__sbit __at (0x88) IT0;

/*  IE   */
__sbit __at (0xAF) EA;
__sbit __at (0xAE) EC;
__sbit __at (0xAD) ET2;
__sbit __at (0xAC) ES;
__sbit __at (0xAB) ET1;
__sbit __at (0xAA) EX1;
__sbit __at (0xA9) ET0;
__sbit __at (0xA8) EX0;

/*  IP   */ 
/*  sbit PPC  = IP^6;*/
__sbit __at (0xBD) PT2;
__sbit __at (0xBC) PS;
__sbit __at (0xBB) PT1;
__sbit __at (0xBA) PX1;
__sbit __at (0xB9) PT0;
__sbit __at (0xB8) PX0;

/*  P3  */
__sbit __at (0xB7) RD;
__sbit __at (0xB6) WR;
__sbit __at (0xB5) T1;
__sbit __at (0xB4) T0;
__sbit __at (0xB3) INT1;
__sbit __at (0xB2) INT0;
__sbit __at (0xB1) TXD;
__sbit __at (0xB0) RXD;

/*  SCON  */
__sbit __at (0x9F) SM0; // alternatively "FE"
__sbit __at (0x9F) FE;
__sbit __at (0x9E) SM1;
__sbit __at (0x9D) SM2;
__sbit __at (0x9C) REN;
__sbit __at (0x9B) TB8;
__sbit __at (0x9A) RB8;
__sbit __at (0x99) TI;
__sbit __at (0x98) RI;
             
/*  P1  */
/* PCA
__sbit __at (0x97) CEX4;
__sbit __at (0x96) CEX3;
__sbit __at (0x95) CEX2;
__sbit __at (0x94) CEX1;
__sbit __at (0x93) CEX0;
__sbit __at (0x92) ECI;
*/

__sbit __at (0x91) T2EX;
__sbit __at (0x90) T2;

/*  T2CON  */
__sbit __at (0xCF) TF2;
__sbit __at (0xCE) EXF2;
__sbit __at (0xCD) RCLK;
__sbit __at (0xCC) TCLK;
__sbit __at (0xCB) EXEN2;
__sbit __at (0xCA) TR2;
__sbit __at (0xC9) C_T2;
__sbit __at (0xC8) CP_RL2;

/*  CCON  */
/*  PCA
__sbit __at (0xDF) CF;
__sbit __at (0xDE) CR;

__sbit __at (0xDC) CCF4;
__sbit __at (0xDB) CCF3;
__sbit __at (0xDA) CCF2;
__sbit __at (0xD9) CCF1;
__sbit __at (0xD8) CCF0;
*/

#else // this just for the autocomplete
/////////////////////////////////////////////////

/* The following is STC additional SFR */

/* sfr  AUXR  = 0x8e; */
/* sfr  AUXR1 = 0xa2; */
/* sfr  IPH   = 0xb7; */

#define P4		(*(char*)0xe8)
#define P4_6		(*(char*)0xee)
#define P4_5		(*(char*)0xed)       //ISP下载需要勾选“ALE引脚用在p4.5口
#define P4_4		(*(char*)0xec)
#define P4_3		(*(char*)0xeb)
#define P4_2		(*(char*)0xea)
#define P4_1		(*(char*)0xe9)
#define P4_0		(*(char*)0xe8)

#define XICON		(*(char*)0xc0)

#define WDT_CONTR		(*(char*)0xe1)

#define ISP_DATA		(*(char*)0xe2)
#define ISP_ADDRH		(*(char*)0xe3)
#define ISP_ADDRL		(*(char*)0xe4)
#define ISP_CMD		(*(char*)0xe5)
#define ISP_TRIG		(*(char*)0xe6)
#define ISP_CONTR		(*(char*)0xe7)

/* Above is STC additional SFR */

/*--------------------------------------------------------------------------
REG51F.H

Header file for 8xC31/51, 80C51Fx, 80C51Rx+
Copyright (c) 1988-1999 Keil Elektronik GmbH and Keil Software, Inc.
All rights reserved.

Modification according to DataSheet from April 1999
 - SFR's AUXR and AUXR1 added for 80C51Rx+ derivatives
--------------------------------------------------------------------------*/

/*  BYTE Registers  */
#define P0		(*(char*)0x80)
#define P0_0		(*(char*)0x80)
#define P0_1		(*(char*)0x81)
#define P0_2		(*(char*)0x82)
#define P0_3		(*(char*)0x83)
#define P0_4		(*(char*)0x84)
#define P0_5		(*(char*)0x85)
#define P0_6		(*(char*)0x86)
#define P0_7		(*(char*)0x87)

#define P1		(*(char*)0x90)
#define P1_0		(*(char*)0x90)
#define P1_1		(*(char*)0x91)
#define P1_2		(*(char*)0x92)
#define P1_3		(*(char*)0x93)
#define P1_4		(*(char*)0x94)
#define P1_5		(*(char*)0x95)
#define P1_6		(*(char*)0x96)
#define P1_7		(*(char*)0x97)

#define P2		(*(char*)0xA0)
#define P2_0		(*(char*)0xA0)
#define P2_1		(*(char*)0xA1)
#define P2_2		(*(char*)0xA2)
#define P2_3		(*(char*)0xA3)
#define P2_4		(*(char*)0xA4)
#define P2_5		(*(char*)0xA5)
#define P2_6		(*(char*)0xA6)
#define P2_7		(*(char*)0xA7)

#define P3		(*(char*)0xB0)
#define P3_0		(*(char*)0xB0)
#define P3_1		(*(char*)0xB1)
#define P3_2		(*(char*)0xB2)
#define P3_3		(*(char*)0xB3)
#define P3_4		(*(char*)0xB4)
#define P3_5		(*(char*)0xB5)
#define P3_6		(*(char*)0xB6)
#define P3_7		(*(char*)0xB7)

#define PSW		    (*(char*)0xD0)
#define ACC		    (*(char*)0xE0)
#define B		    (*(char*)0xF0)
#define SP		    (*(char*)0x81)
#define DPL		    (*(char*)0x82)
#define DPH		    (*(char*)0x83)
#define PCON		(*(char*)0x87)
#define TCON		(*(char*)0x88)
#define TMOD		(*(char*)0x89)
#define TL0		    (*(char*)0x8A)
#define TL1		    (*(char*)0x8B)
#define TH0		    (*(char*)0x8C)
#define TH1		    (*(char*)0x8D)
#define IE		    (*(char*)0xA8)
#define IP		    (*(char*)0xB8)
#define SCON		(*(char*)0x98)
#define SBUF		(*(char*)0x99)

/*  80C51Fx/Rx Extensions  */
#define AUXR		(*(char*)0x8E)
#define AUXR1		(*(char*)0xA2)
#define SADDR		(*(char*)0xA9)
#define IPH		    (*(char*)0xB7)
#define SADEN		(*(char*)0xB9)
#define T2CON		(*(char*)0xC8)
#define T2MOD		(*(char*)0xC9)
#define RCAP2L		(*(char*)0xCA)
#define RCAP2H		(*(char*)0xCB)
#define TL2		    (*(char*)0xCC)
#define TH2		    (*(char*)0xCD)

/* PCA SFR
#define CCON		(*(char*)0xD8)
#define CMOD		(*(char*)0xD9)
#define CCAPM0		(*(char*)0xDA)
#define CCAPM1		(*(char*)0xDB)
#define CCAPM2		(*(char*)0xDC)
#define CCAPM3		(*(char*)0xDD)
#define CCAPM4		(*(char*)0xDE)
#define CL		(*(char*)0xE9)
#define CCAP0L		(*(char*)0xEA)
#define CCAP1L		(*(char*)0xEB)
#define CCAP2L		(*(char*)0xEC)
#define CCAP3L		(*(char*)0xED)
#define CCAP4L		(*(char*)0xEE)
#define CH		(*(char*)0xF9)
#define CCAP0H		(*(char*)0xFA)
#define CCAP1H		(*(char*)0xFB)
#define CCAP2H		(*(char*)0xFC)
#define CCAP3H		(*(char*)0xFD)
#define CCAP4H		(*(char*)0xFE)
*/

/*  BIT Registers  */
/*  PSW   */
#define CY		(*(char*)0xD7)
#define AC		(*(char*)0xD6)
#define F0		(*(char*)0xD5)
#define RS1		(*(char*)0xD4)
#define RS0		(*(char*)0xD3)
#define OV		(*(char*)0xD2)
#define F1		(*(char*)0xD1)
#define P		(*(char*)0xD0)

/*  TCON  */
#define TF1		(*(char*)0x8F)
#define TR1		(*(char*)0x8E)
#define TF0		(*(char*)0x8D)
#define TR0		(*(char*)0x8C)
#define IE1		(*(char*)0x8B)
#define IT1		(*(char*)0x8A)
#define IE0		(*(char*)0x89)
#define IT0		(*(char*)0x88)

/*  IE   */
#define EA		(*(char*)0xAF)
#define EC		(*(char*)0xAE)
#define ET2		(*(char*)0xAD)
#define ES		(*(char*)0xAC)
#define ET1		(*(char*)0xAB)
#define EX1		(*(char*)0xAA)
#define ET0		(*(char*)0xA9)
#define EX0		(*(char*)0xA8)

/*  IP   */ 
/*  sbit PPC  = IP^6;*/
#define PT2		(*(char*)0xBD)
#define PS		(*(char*)0xBC)
#define PT1		(*(char*)0xBB)
#define PX1		(*(char*)0xBA)
#define PT0		(*(char*)0xB9)
#define PX0		(*(char*)0xB8)

/*  P3  */
#define RD		(*(char*)0xB7)
#define WR		(*(char*)0xB6)
#define T1		(*(char*)0xB5)
#define T0		(*(char*)0xB4)
#define INT1	(*(char*)0xB3)
#define INT0	(*(char*)0xB2)
#define TXD		(*(char*)0xB1)
#define RXD		(*(char*)0xB0)

/*  SCON  */
#define SM0		(*(char*)0x9F) // alternatively "FE"
#define FE		(*(char*)0x9F)
#define SM1		(*(char*)0x9E)
#define SM2		(*(char*)0x9D)
#define REN		(*(char*)0x9C)
#define TB8		(*(char*)0x9B)
#define RB8		(*(char*)0x9A)
#define TI		(*(char*)0x99)
#define RI		(*(char*)0x98)
             
/*  P1  */
/* PCA
#define CEX4		(*(char*)0x97)
#define CEX3		(*(char*)0x96)
#define CEX2		(*(char*)0x95)
#define CEX1		(*(char*)0x94)
#define CEX0		(*(char*)0x93)
#define ECI		(*(char*)0x92)
*/

#define T2EX		(*(char*)0x91)
#define T2		(*(char*)0x90)

/*  T2CON  */
#define TF2		(*(char*)0xCF)
#define EXF2		(*(char*)0xCE)
#define RCLK		(*(char*)0xCD)
#define TCLK		(*(char*)0xCC)
#define EXEN2		(*(char*)0xCB)
#define TR2		(*(char*)0xCA)
#define C_T2		(*(char*)0xC9)
#define CP_RL2		(*(char*)0xC8)

/*  CCON  */
/*  PCA
#define CF		(*(char*)0xDF)
#define CR		(*(char*)0xDE)

#define CCF4		(*(char*)0xDC)
#define CCF3		(*(char*)0xDB)
#define CCF2		(*(char*)0xDA)
#define CCF1		(*(char*)0xD9)
#define CCF0		(*(char*)0xD8)
*/

#endif
/////////////////////////////////////////////////

#endif

