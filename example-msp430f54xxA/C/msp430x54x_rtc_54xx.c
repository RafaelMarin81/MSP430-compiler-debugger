//******************************************************************************
//  msp430FG5438 Demo - Real Time Clock, Toggle P1.0 Inside ISR, 32kHz ACLK
//                      and send Time via UART
//
//  Description: This program toggles P1.0 by xor'ing P1.0 inside of
//  a Real Time Clock ISR. The Real Time Clock ISR is called once a minute using
//  the Alarm function provided by the RTC. ACLK used to clock basic timer.
//  The actual time is send send via UART
//  ACLK = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
//
//                msp430FG5438
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST              |
//            |             P1.0|-->LED
//            |                 |
//            |      P3.4/UC0TXD|----------->
//            |                 | 2400 - 8N1
//            |      P3.5/UC0RXD|<-----------
//
//   M Smertneck
//   Texas Instruments Inc.
//   April 2008
//   Built with CCEv3.2 IAR Embedded Workbench Version: 3.42A
//******************************************************************************

#include <msp430x54x.h>

void tx_char(char c);

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;             // Stop Watchdog Timer

  P3SEL = 0x30;                         // P3.4,5 = USART0 TXD/RXD
//  P1DIR |= 0x01;                        // Set P1.0 to output direction
  P4DIR |= BIT7;

  // SetupUSCI0:
  UCA0CTL1 = UCSWRST;                   // To set hold the module in reset
  UCA0CTL1 = UCSSEL0;                   // ACLK
  UCA0BR0 = 13;                         // 32k - 2400 baudrate control setting
  UCA0BR1 = 0;
  UCA0MCTL = UCBRS2+UCBRS1;             // Second modulation stage values
  UCA0STAT = UCFE+UCOE+UCPE+UCBRK+UCRXERR;

  // RTC
  RTCCTL01 = RTCBCD+RTCHOLD+RTCMODE+RTCTEV_0+RTCTEVIE;
                                        // RTC enable, BCD mode,
                                        // alarm every Minute,
                                        // enable RTC interrupt
  // Init time
  RTCSEC =  0x00;                       // Set Seconds
  RTCMIN =  0x58;                       // Set Minutes
  RTCHOUR = 0x08;                       // Set Hours

  // Init date
  RTCDOW =  0x02;                       // Set DOW
  RTCDAY =  0x23;                       // Set Day
  RTCMON =  0x08;                       // Set Month
  RTCYEAR = 0x2005;                     // Set Year

  RTCCTL01 &= ~RTCHOLD;                 // Enable RTC

  while (1)
  {
    __bis_SR_register(LPM3_bits + GIE); // Enter LPM3 w/ interrupt
    __no_operation();                   // Required for debugger

    tx_char((RTCHOUR>>4)+0x30);         // Send high nibble of hour
    tx_char((RTCHOUR&0x0F)+0x30);       // Send low nibble of hour
    tx_char(':');                       // Send ':'
    tx_char((RTCMIN>>4)+0x30);          // Send high nibble of minute
    tx_char((RTCMIN&0x0F)+0x30);        // Send low nibble of minute
    tx_char('\n');                      // Send new line
  }
}

void tx_char(char c)
{
  while ((UCA0IFG & UCTXIFG)==0){}      // wait till TXbuf empty
  UCA0TXBUF = c;                        // TX char
}
// Basic Timer interrupt service routine
#pragma vector=RTC_VECTOR
__interrupt void RTC(void)
{
  RTCCTL01 &= ~RTCTEVIFG; 				      // Clear the RTC interrupt flag 
  
//  P1OUT ^= 0x01;                        // Toggle P5.1 using exclusive-OR
  P4OUT ^= BIT7;

  LPM3_EXIT;                            // Exit LPM after interrupt
}
