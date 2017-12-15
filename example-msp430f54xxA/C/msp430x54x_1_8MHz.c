//******************************************************************************
//   MSP430x54x Demo - Software Toggle P1.0
//
//   Description: Toggle P1.0 by xor'ing P1.0 inside of a software loop.
//   ACLK = REFO = 32kHz, MCLK = SMCLK = 8MHz
//
//                 MSP430x5438
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST              |
//            |                 |
//            |             P1.0|-->LED
//
//   Z Albus
//   Texas Instruments Inc.
//   May 2008
//   Built with CCEv3.2 CCE Version: 3.2.0
//******************************************************************************
/*
5.1 Unified Clock System (UCS) Introduction
 The UCS module supports low system cost and ultralow power consumption. 
 3 internal clock signals, the user can select the best balance of performance and low power consumption. 
 The UCS module can be configured to operate without any external components, 
 with 1 or 2 external crystals or with resonators, under full software control.
 
 Up to 5 clocks:

 • XT1CLK: Low-frequency or high-frequency oscillator that can be used either with low-frequency 32768 Hz watch crystals, standard crystals, resonators, or external clock sources in the 4 MHz to 32 MHz range. 
 XT1CLK can be used as a clock reference into the FLL. 
     Some devices only support the low frequency oscillator for XT1CLK.  See the device-specific data sheet for supported functions.

 • VLOCLK: Internal very low power, low frequency oscillator with 10 kHz typical frequency.

 • REFOCLK: Internal, trimmed, low-frequency oscillator with 32768 Hz typical frequency, with the ability to be used as a clock reference into the FLL.

 • DCOCLK: Internal digitally-controlled oscillator (DCO) that can be stabilized by the FLL.

 • XT2CLK: Optional high-frequency oscillator that can be used with standard crystals, resonators, or external clock sources in the 4 MHz to 32 MHz range. XT2CLK can be used as a clock reference into the FLL.


*/
 

#include  "msp430x54x.h"

void main(void)
{
  volatile unsigned int i;

  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT
 
  // Operation-OR to Set bit 1.
  P2DIR |= BIT4;    // P2.4 Output.

 /* 
  // 
  UCSCTL0 = 0x00;                           // Set lowest possible DCOx, MODx
  //UCSCTL3 = SELREF_2;                       // Set DCO FLL reference = REFO
  UCSCTL1 = DCORSEL_6;                      // Select range for 12MHz operation 
  UCSCTL2 = 249;                            // Set DCO Multiplier for 8MHz
  UCSCTL4 = 0;
  UCSCTL4 = SELM_3;                // Set MCLK = DCOCLK
  */
  while(1)
  {
    // Operation-XOR to Toggle the bit.
    P2OUT ^= BIT4;  // P2.4  Toggle.
    
    for(i=50000;i>0;i--);                   // Delay  
  }
}
