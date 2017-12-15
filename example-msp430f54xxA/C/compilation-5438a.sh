
echo "Compiling $1"

msp430-gcc --version | head -1
MSPGCC_VERSION=`msp430-gcc -dumpversion`

if test x$MSPGCC_VERSION = "x4.7"; then
    # 20 bits flags for compilation (supported from mspgcc 4.7)
    CFLAGS=" -mmemory-model=large  -mcode-region=far -mdata-region=far -mc20 -md20 -msr20"  #-misr20 -ma20
else
    echo "ERROR: Compiler"
    exit
fi

rm $1.odin5438A

#msp430-gcc -Os -fno-strict-aliasing -Wall -mmcu=msp430f5438a -g   -MMD -c sy

#msp430-gcc  -D__MSP430F5437__   -mmcu=msp430f5437  -Wl,--gc-sections,--undefined=_reset_vector__,--undefined=InterruptVectors,--undefined=_copy_data_init__,--undefined=_clear_bss_init__,--undefined=_end_of_init__   $CFLAGS   $1   -o $1.wismote

msp430-gcc -Os -fno-strict-aliasing -Wall -mmcu=msp430f5438a -Wl,--gc-sections,--undefined=_reset_vector__,--undefined=InterruptVectors,--undefined=_copy_data_init__,--undefined=_clear_bss_init__,--undefined=_end_of_init__   -g $CFLAGS -MMD  $1 -o $1.odin5438A

upload-jtag-olimex.sh $1.odin5438A


