//******************************************************************************
//  msp430FG5438 Demo - Timer_B, Toggle P4.7, Overflow ISR, DCO SMCLK
//
//  Description: Toggle P4.7 using software and Timer_B overflow ISR.
//  In this example an ISR triggers when TB overflows.  TB overflow has the 
//  lowest priority. Inside the TB overflow ISR P4.7 is toggled. Toggle rate is 
//  approximatlely 7.822Hz = [1.045MHz/FFFFh]/2. Proper use of TBIV interrupt vector 
//  generator is shown.
//  ACLK = n/a, MCLK = SMCLK = TBCLK = default DCO ~1.045MHz.
//
//           msp430FG5438
//         ---------------
//     /|\|               |
//      | |               |
//      --|RST            |
//        |               |
//        |           P4.7|-->LED
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
  P4DIR |= BIT7;                            // Set P4.7 to output direction
  TBCTL = TBSSEL_2 + MC_2 + TBIE;           // SMCLK, contmode, interrupt

  _BIS_SR(LPM0_bits + GIE);                 // Enter LPM0 w/ interrupt
}

// Timer_B7 Interrupt Vector (TBIV) handler
#pragma vector=TIMERB1_VECTOR
__interrupt void Timer_B(void)
{
 /* Any access, read or write, of the TBIV register automatically resets the 
 highest "pending" interrupt flag. */
  switch( TBIV )
 {
   case  2: break;                          // CCR1 not used
   case  4: break;                          // CCR2 not used
   case 14: P4OUT ^= BIT7;                  // overflow
            break;
 }
}

