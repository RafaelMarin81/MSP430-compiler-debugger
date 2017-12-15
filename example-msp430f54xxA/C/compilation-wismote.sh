
echo "Compiling $1"

msp430-gcc --version | head -1
MSPGCC_VERSION=`msp430-gcc -dumpversion`

if test x$MSPGCC_VERSION = "x4.7.0"; then
    # 20 bits flags for compilation (supported from mspgcc 4.7.0)
    CFLAGS=" -mmemory-model=large  -mcode-region=far -mdata-region=far -mc20 -md20 -msr20"  #-misr20 -ma20
else
    echo "ERROR: Compiler"
    exit
fi

#msp430-gcc -Wl,-Ttext=0x8000     -D__MSP430F5437__       -mmcu=msp430f5437 -Wl,-Map=contiki-wismote.map -Wl,--gc-sections,--undefined=_reset_vector__,--undefined=InterruptVectors,--undefined=_copy_data_init__,--undefined=_clear_bss_init__,--undefined=_end_of_init__ -mmemory-model=large  -mcode-region=far -mdata-region=far  -mc20 -md20 -msr20   blink.co obj_wismote/contiki-wismote-main.o contiki-wismote.a  -o blink.wismote


msp430-gcc  -D__MSP430F5437__   -mmcu=msp430f5437  -Wl,--gc-sections,--undefined=_reset_vector__,--undefined=InterruptVectors,--undefined=_copy_data_init__,--undefined=_clear_bss_init__,--undefined=_end_of_init__   $CFLAGS   $1   -o $1.wismote



upload-jtag-olimex.sh $1.wismote


