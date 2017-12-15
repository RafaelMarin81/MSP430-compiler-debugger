//******************************************************************************
//  msp430FG5438 Demo - Timer_B, Toggle P1.0, CCR0 Cont. Mode ISR, DCO SMCLK
//
//  Description: Toggle P1.0 using software and TB_0 ISR. Toggles every
//  50000 SMCLK cycles. SMCLK provides clock source for TBCLK.
//  During the TB_0 ISR, P1.0 is toggled and 50000 clock cycles are added to
//  CCR0. TB_0 ISR is triggered every 50000 cycles. CPU is normally off and
//  used only during TB_ISR.
//  ACLK = n/a, MCLK = SMCLK = TBCLK = default DCO ~1.045MHz
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
  P4DIR |= 0xff;                            // P4.7 output
  TBCCTL0 = CCIE;                           // CCR0 interrupt enabled
//  TBCCR0 = 50;
  TBCTL = TBSSEL_2 + MC_2;                  // SMCLK, contmode
//  TBCTL = TBSSEL_1 + MC_1;                  // ACLK, upmode

  _BIS_SR(LPM0_bits + GIE);                 // Enter LPM0 w/ interrupt
}

// Timer B0 interrupt service routine
#pragma vector=TIMERB0_VECTOR
__interrupt void Timer_B (void)
{
  P4OUT ^= BIT7;                            // Toggle P4.7
//  TBCCR0 += 50000;                          // Add Offset to CCR0 [Cont mode]
    
  switch( TBIV )
  {
      case  2: // CCR1 not used
          P4OUT ^= BIT5;
          break;
          
      case  4: // CCR2 not used
          break;
          
      case 14: // Timer overflow; Interrupt Flag: TBxCTL TBIFG; Interrupt Priority: Lowest
          P4OUT ^= BIT6;
          break;
  }

}

