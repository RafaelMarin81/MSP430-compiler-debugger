Compiler and Debugger for MSP430 Texas Instruments
==================================================

[![Compiler of MSP430](https://github.com/tecip-nes/contiki-tres/wiki/Building-the-latest-version-of-mspgcc)](https://github.com/tecip-nes/contiki-tres/wiki/Building-the-latest-version-of-mspgcc)

To build the latest version of mspgcc (which supports the MSP430X extension) you can use the following script (which is a modified version of the one you can find on the old Contiki wiki).

[![More information about Compiler](https://github.com/contiki-os/contiki/wiki/Setup-Contiki-Toolchain-in-Arch-Linux)](https://github.com/contiki-os/contiki/wiki/Setup-Contiki-Toolchain-in-Arch-Linux)

[![Debugger of MSP430](https://github.com/dlbeer/mspdebug)](https://github.com/dlbeer/mspdebug)

MSPDebug is a free debugger for use with MSP430 MCUs. It supports FET430UIF, eZ430, RF2500 and Olimex MSP430-JTAG-TINY programmers, as well as many other compatible devices. It can be used as a proxy for gdb or as an independent debugger with support for programming, disassembly and reverse engineering.

  * Userspace only: no kernel modifications required.
  * Works with RF2500, eZ430, FET430UIF (V2 and V3), Launchpad, Chronos,
    GoodFET, Olimex MSP430-JTAG-TINY and MSP430-JTAG-ISO programmers.
    Also supports the TI flash bootloader.
  * Can act as a GDB remote stub (replacement for msp430-gdbproxy)
    and/or a GDB client.
  * Can single-step, program, run to breakpoint and inspect memory on
    supported devices.
  * Can be used to access the FET430UIF bootloader.
  * Supports Intel HEX, ELF32, BSD symbol table, COFF, TI Text and
    SREC file formats.
  * Can disassemble code in memory, including translating addresses to
    symbols.
  * Includes reverse-engineering features such as instruction search,
    call-graph analysis and symbol table editing.
  * Simulation mode allows execution of MSP430 code without hardware.
  * Cross-platform: compiles on Linux, *BSD, OS/X and Windows.

Installation in Ubuntu/Linux
============================

To install the compiler for 64bits:

$ sudo cp -rf mspgcc-4.7.2 /opt/

To install the compiler for 32bits:

$ sudo install-mspgcc-4.7.2.sh

To install the debugger for 64 bits operation system.

$ cp mspdebug-64bits/mspdebug /usr/local/bin/ 

To install the debugger for 32 bits operation system.

$ cp mspdebug-32bits/mspdebug /usr/local/bin/ 

To support automatical permissions for ttyUSBx ports

$ sudo cp 99-usb-serial.rules  /etc/udev/rules.d/99-usb-serial.rules

Include the following text to ~/.bashrc
=======================================

function msp430-472 () {

    export PATH=/opt/mspgcc-4.7.2/bin:$PATH  # Experimental 20 bits.

    MSP430_GCC_VERSION=`msp430-gcc -dumpversion`

    if [ "$MSP430_GCC_VERSION" == "4.7.2" ]; then

        echo "Compiler msp430-gcc 4.7.2 for MSP430 Experimental 20bits"

    else

        echo "ERROR: Compiler msp430-gcc $MSP430_GCC_VERSION != 4.7.2 for MSP430 Experimental 20bits"

    fi

}

Usage 
=====

make                # Compile in Contiki

make app_pwm.upload0  TARGET=odin5438A    # Program ttyUSB0

make app_pwm.upload1  TARGET=odin5438A    # Program ttyUSB1

mspdebug -d /dev/ttyUSB0 debug      # Logging ttyUSB0

mspdebug -d /dev/ttyUSB1 debug      # Logging ttyUSB1

compilation-5438a.sh msp430x54x_pwm.c   # Compile and Program in ttyUSB0 using example-msp430f54xxA


