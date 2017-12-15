#!/bin/bash

echo "Compiling $1"

msp430-gcc --version | head -1
MSPGCC_VERSION=`msp430-gcc -dumpversion`

# Flag set to avoid writing on the bootloader flash space
#LDFLAGS += -Wl,-Ttext=0x8000
#CFLAGS += -Wl,-Ttext=0x8000

if test x$MSPGCC_VERSION = "x4.7.2"; then
    # 20 bits flags for compilation (supported from mspgcc 4.7.2)
    CFLAGS=" -Wl,-Ttext=0x8000 -mmemory-model=large  -mcode-region=far -mdata-region=far -mc20 -md20 -msr20"  #-misr20 -ma20
else
    echo "ERROR: Compiler"
    exit
fi

rm $1.odin5419A

#msp430-gcc -Os -fno-strict-aliasing -Wall -mmcu=msp430f5419a -g   -MMD -c sy

#msp430-gcc  -D__MSP430F5437__   -mmcu=msp430f5437  -Wl,--gc-sections,--undefined=_reset_vector__,--undefined=InterruptVectors,--undefined=_copy_data_init__,--undefined=_clear_bss_init__,--undefined=_end_of_init__   $CFLAGS   $1   -o $1.wismote

msp430-gcc -Os -fno-strict-aliasing -Wall -mmcu=msp430f5419a -Wl,--gc-sections,--undefined=_reset_vector__,--undefined=InterruptVectors,--undefined=_copy_data_init__,--undefined=_clear_bss_init__,--undefined=_end_of_init__   -g $CFLAGS -MMD  $1 -o $1.odin5419A

upload-jtag-olimex.sh $1.odin5419A


