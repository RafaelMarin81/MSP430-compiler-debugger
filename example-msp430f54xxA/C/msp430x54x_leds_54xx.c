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
#include  "msp430x54x.h"

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

const int FirmwareVersion __attribute__((section(".fartext"))) = 0xDDDD;
const char FirmwareHeader[] __attribute__((section(".fardata"))) = {0x02, 0x00, 0x01, 0x00, 0xD8, 0x00, 0x00, 0x00, 0xF8, 0xD6};  // header: u16version, u16options, u32length, u16crc

void sleep_LPM3(void);


int main(void)
{
  volatile unsigned int i;


  if(FirmwareVersion) 
      i = FirmwareVersion + 1;

  i = FirmwareHeader[4];

  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT.  WatchDog-Timer.

  for(i=50000;i>0;i--);                   // Delay

  // Operation-OR to Set bit 1.
//  P2DIR |= BIT7;    // P2.7
//P5DIR |= BIT2;    // P5.2
//P8DIR |= BIT6;    // P8.6
  P4DIR |= BIT5;
  P4DIR |= BIT6;
  P4DIR |= BIT7;

  // Operation-OR to Set bit 1.
//  P2OUT |= BIT7;  // P2.7
//P5OUT |= BIT2;  // P5.2
//P8OUT |= BIT6;  // P8.6
  P4OUT |= BIT5;
  P4OUT |= BIT6;
  P4OUT |= BIT7;

  // Operation-AND-NOR to Set bit 0.
//  P2OUT &= ~BIT7;  // P2.7
//P5OUT &= ~BIT2;  // P5.2
//P8OUT &= ~BIT6;  // P8.6
  P4OUT &= ~BIT5;
  P4OUT &= ~BIT6;
  P4OUT &= ~BIT7;

  while(1)
  {
    // Operation-XOR to Toggle the bit.
//    P2OUT ^= BIT7;  // P2.7
//  P5OUT ^= BIT2;  // P5.2
//  P8OUT ^= BIT6;  // P8.6
    P4OUT ^= BIT5;
    P4OUT ^= BIT6;
    P4OUT ^= BIT7;

    __delay_cycles(1000000uL);

    disable_hardware_MexSTv1();   // Enter LPM3

//    __bis_SR_register(LPM3_bits);             // Enter LPM3
//    __no_operation();

    //__delay_cycles(F_CPU);
    //for(i=50000;i>0;i--);                   // Delay
  }

  return 0;
}

void disable_hardware_MexSTv1(void)       // MexSTv1.0  Consumption: 72 uA  without the programming cable.
{

    P1SEL = 0x00;       // I/O General operation.
    P1REN = 0x00;       // No pullup/pulldown
    P1OUT = 0x00;
    P1DIR = 0xFF;       // BSL-UART and GDOs-RADIO.  Output-Low
 
    P2SEL = 0x00;       // I/O General operation.
    P2REN = 0x00;       // No pullup/pulldown
    P2OUT = 0x00;
    P2DIR = 0xFF;       // Mosfets: Output-Low.  GAS-ON, SENS-ON, RADIO-ON    1uA
    
    P3SEL = 0x00;       // I/O General operation.
    P3REN = 0x00;       // No pullup/pulldown
    P3OUT = 0x00;
    P3DIR = 0xFF;       // SPI-Radio.  Output-Low  -30uA
    P3OUT |= BIT6 | BIT7;   // I2C SDA-SCL.  Output-High    -700uA
/*
    P4SEL = 0x00;       // I/O General operation.
    P4REN = 0x00;       // No pullup/pulldown
    P4OUT = 0x00;
    P4DIR = 0xFF;       // Leds and PWM: Output-Low     -40uA
*/
    P5SEL = 0x00;       // I/O General operation.
    P5REN = 0x00;       // No pullup/pulldown
    P5OUT = 0x00;
    P5DIR = 0xFF;       // Debug-UART:  Output-Low

    P6SEL = 0x00;       // I/O General operation.
    P6REN = 0x00;       // No pullup/pulldown
    P6OUT = 0x00;
    P6DIR = 0xFF;       // ADC-inputs: Output-Low:  GAS, LUX, TEMP, BAT   100uA

    P7SEL = 0x00;       // I/O General operation.
    P7REN = 0x00;       // No pullup/pulldown
    P7OUT = 0x00;
    P7DIR = 0xFF;       // Nothing.  Output-Low

    P7SEL = 0x00;       // I/O General operation.
    P7REN = 0x00;       // No pullup/pulldown
    P8OUT = 0x00;
    P8DIR = 0xFF;       // Nothing.  Output-Low

    P9SEL = 0x00;       // I/O General operation.
    P9REN = 0x00;       // No pullup/pulldown
    P9OUT = 0x00;
    P9DIR = 0xFF;       // SPI-Dataflash.   30uA

    P10SEL = 0x00;       // I/O General operation.
    P10REN = 0x00;       // No pullup/pulldown
    P10OUT = 0x00;
    P10DIR = 0xFF;       // Nothing.  Output-Low
    P10OUT |= BIT1 | BIT2;   // I2C SDA-SCL.  Output-High    -700uA

    P11SEL = 0x00;       // I/O General operation.
    P11REN = 0x00;       // No pullup/pulldown
    P11OUT = 0x00;
    P11DIR = 0xFF;      // Nothing.  Output-Low

    PJREN = 0x00;       // No pullup/pulldown
    PJOUT = 0x00;
    PJDIR = 0x00;       // Input:  RST, TCK     -66uA

}

