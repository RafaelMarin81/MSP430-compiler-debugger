MSPDebug
========

MSPDebug is a free debugger for use with MSP430 MCUs. 

Modified: Rafael Marin-Perez rafael.marin81@gmail.com

Features
--------

  * Programming: Flash-BSL of MSP430, FET430UIF (V2 and V3), Olimex MSP430-JTAG-TINY, MSP430-JTAG-ISO, etc.
  * Debugging:  UART Transmission and Reception.
  * Reset:    RST line.

Compiling from source
---------------------

Ensure that you have the necessary packages to compile programs that use libusb 
(on Debian or Ubuntu systems, you might need to do apt-get install libusb-dev). 
After that, unpack and compile the source code with:

    make WITHOUT_READLINE=1
    make install

Type "mspdebug --help" for usage instructions.

Programming MSP430 via Flash-BSL:

    sudo chmod 777 /dev/ttyUSB0
    mspdebug -jd /dev/ttyUSB0 --long-password flash-bsl "prog blink-sender.ihex"

Debugging MSP430 via UART-port at 115200 Baud-rate:

    mspdebug -jd /dev/ttyUSB0 debug

Reset MSP430 via RST pin:

    mspdebug -jd /dev/ttyUSB1 reset

Ethbridge MSP430 via UART-port at 115200 Baud-rate:

    mspdebug -d /dev/ttyUSB0 tapslip  # Forwarding for Ethbridge MSP430f54xx

