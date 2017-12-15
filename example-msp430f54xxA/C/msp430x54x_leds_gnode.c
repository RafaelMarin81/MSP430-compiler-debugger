//******************************************************************************
//   MSP430x54x Demo - Software Toggle P1.0
//
//   Description: Toggle P1.0 by xor'ing P1.0 inside of a software loop.
//   ACLK = 32.768kHz, MCLK = SMCLK = default DCO
//
//                 MSP430x5438
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST              |
//            |                 |
//            |             P1.0|-->LED
//
//   M Smertneck
//   Texas Instruments Inc.
//   February 2008
//   Built with CCEv3.2 IAR Embedded Workbench Version: 3.41A
//******************************************************************************
#include  "msp430f2418.h"

/*
12.1 Digital I/O Introduction
The digital I/O features include:
• Independently programmable individual I/Os
• Any combination of input or output.
• Individually configurable P1 and P2 interrupts. Some devices may include additional port interrupts.
• Independent input and output data registers.
• Individually configurable pullup or pulldown resistors
*/
/*
Devices within the family may have up to twelve digital I/O ports implemented (P1 to P11 and PJ). 
Most ports contain eight I/O lines; 
however, some ports may contain less (see the device-specific data sheet for ports available). 
Each I/O line is individually configurable for input or output direction, and each can be individually read or written. 
Each I/O line is individually configurable for pullup or pulldown resistors, as well as, configurable drive strength, full or reduced. 
PJ contains only four I/O lines.
Ports P1 and P2 always have interrupt capability. 
Each interrupt for the P1 and P2 I/O lines can be individually enabled and configured to provide an interrupt on a rising or falling edge of an input signal. 
All P1 I/O lines source a single interrupt vector P1IV, and all P2 I/O lines source a different, single interrupt vector P2IV. 
On some devices, additional ports with interrupt capability may be available (see the device-specific data sheet for details) and contain their own respective interrupt vectors.

P1.0    = Port 1, line 0.
P2.1    = Port 2, line 1.
P1 and P2 = PA.     16 lines,   word-format.
P3 and P4 = PB.     16 lines,   word-format.
P1IV = Port 1 Interrupt Vector.      
P2IV = Port 2 Interrupt Vector.

PxDIR = Direction Register.
Bit 0 = Input direction.
Bit 1 = Output direction.

PxIN = Input Register for Reading from I/O lines.
Bit = 0: Low
Bit = 1: High

PxOUT = Output Register for Writting in I/O lines.
Bit = 0: Low
Bit = 1: High

PxREN =  Resistor Enable Registers. Pullup/Pulldown.
Bit = 0. Disable.
Bit = 1. Enable.

PxDIR  PxREN   PxOUT    I/O Configuration
0       0       x       Input
0       1       0       Input pulldown
0       1       1       Input pullup
1       x       x       Output

PxDS = Output Drive Strength Registers
Bit 0: Reduced.  Default.
Bit 1: Full.

PxSEL = Selection Registers.   Each PxSEL bit is used to select the pin function between I/O or peripheral.
Bit 0: I/O Function.
Bit 1: Peripheral Function.
NOTE: P1 and P2 interrupts are disabled when PxSEL = 1

-------------------------------------------------------------------------

Interruption: PxIFG, PxIE and PxIES.
Each pin in ports P1 and P2 has interrupt capability, configured with the PxIFG, PxIE, and PxIES

PxIFG:  Interrupt FlaG.
Bit 0: No interrupt pending.
Bit 1: YES interrupt pending.

PxIES:  Interrupt Edge Select.  Each PxIES bit selects the interrupt edge.
- Bit = 0: low-to-high transition of PxIFG flag.
- Bit = 1: high-to-low transition of PxIFG flag. 
NOTE: Writing to P1IES or P2IES for each corresponding I/O can result in setting the corresponding interrupt flags PxIFG.
PxIES       PxIN    PxIFG
0 → 1       0       May be set
0 → 1       1       Unchanged
1 → 0       0       Unchanged
1 → 0       1       May be set

PxIE:   Interrupt Enable.       Each PxIE bit enables the associated PxIFG interrupt flag.
• Bit = 0: Interrupt is disabled
• Bit = 1: Interrupt is enabled

--------------------------------------------------------------------------

Unused Port Pins.       Reduce power consumption.

Unused I/O pins should be configured as I/O function, output direction, and left unconnected on the PC
PxSEL = 0:  I/O function
PxDIR = 1:  Output direction.
PxOUT = 0-1:    Dont care.
No connect to board.

NOTE: Configuring port J and shared JTAG pins:



*/




void main(void)
{
  volatile unsigned int i;

  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT.  WatchDog-Timer.

/*  // Operation-OR to Set bit 1.
  P1DIR |= BIT7;    // P1.7
  P2DIR |= BIT0;    // P2.0
  P2DIR |= BIT1;    // P2.1
//  P2DIR |= 0x1 << 4;    // P2.4
//  P5DIR |= 0x1 << 2;    // P5.2
//  P8DIR |= 0x1 << 6;    // P8.6
*/
  P1DIR |= 0xff;
  P2DIR |= 0xff;

/*
  // Operation-OR to Set bit 1.
  P1OUT |= BIT7;  // P1.7
  P2OUT |= BIT0;  // P2.0
  P2OUT |= BIT1;  // P2.1
*/
  P1OUT |= 0xff;
  P2OUT |= 0xff;

/*
  // Operation-AND-NOR to Set bit 0.
  P1OUT &= ~BIT7;  // P1.7
  P2OUT &= ~BIT0;  // P2.0
  P2OUT &= ~BIT1;  // P2.1
*/
  P1OUT &= ~0xff;
  P2OUT &= ~0xff;

  while(1)
  {
/*      
    // Operation-XOR to Toggle the bit.
    P1OUT ^= BIT7;  // P1.7
    P2OUT ^= BIT0;  // P2.0
    P2OUT ^= BIT1;  // P2.1
*/
    P1OUT ^= 0xff;
    P2OUT ^= 0xff;

    for(i=50000;i>0;i--);                   // Delay
  }
}
