//******************************************************************************
//  msp430FG5438 Demo - Timer_B, Toggle P1.0, Overflow ISR, 32kHz ACLK
//
//  Description: Toggle P1.0 using software and the Timer_B overflow ISR.
//  In this example an ISR triggers when TB overflows. Inside the ISR P1.0
//  is toggled. Toggle rate is exactly 0.25Hz = [32kHz/FFFFh]/2. Proper use of the 
//  TBIV interrupt vector generator is demonstrated.
//  ACLK = TBCLK = 32kHz, MCLK = SMCLK = default DCO ~ 1.045MHz
//
//           msp430FG5438
//         ---------------
//     /|\|               |
//      | |               |
//      --|RST            |
//        |               |
//        |           P1.0|-->LED
//
//   M Smertneck
//   Texas Instruments Inc.
//   April 2008
//   Built with CCEv3.2 IAR Embedded Workbench Version: 3.42A
//******************************************************************************

#include <msp430x54x.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P1DIR |= 0x01;                            // Set P1.0 to output direction

  P4DIR |= 0xff;

  //TBCTL = TBSSEL_1 + MC_2 + TBIE;           // ACLK, contmode, interrupt

  //TBCTL = TBSSEL_2 + MC_2 + TBIE;           // SMCLK, contmode, interrupt
  TBCTL = TBSSEL_2 + MC_1 + TBIE;                  // SMCLK, upmode, interrupt

  _BIS_SR(LPM3_bits + GIE);                 // Enter LPM3 w/ interrupt
}

// Timer_B7 Interrupt Vector (TBIV) handler
#pragma vector=TIMERB1_VECTOR
__interrupt void Timer_B(void)
{
 switch( TBIV )
 {
   P4OUT ^= BIT7;

   case  2: P4OUT ^= BIT5;
            break;                          // CCR1 not used
   case  4: break;                          // CCR2 not used
   case 14: P1OUT ^= 0x01;                  // overflow
            P4OUT ^= BIT6;
           break;
  }
}

