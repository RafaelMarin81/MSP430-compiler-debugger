
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

echo "msp430-gcc -mmcu=msp430f2418 -Wl,-Map=contiki-gnode.map -Wl,--gc-sections,--undefined=_reset_vector__,--undefined=InterruptVectors,--undefined=_copy_data_init__,--undefined=_clear_bss_init__,--undefined=_end_of_init__  $CFLAGS  $1  -o $1.gnode"

msp430-gcc -mmcu=msp430f2418 -Wl,-Map=contiki-gnode.map -Wl,--gc-sections,--undefined=_reset_vector__,--undefined=InterruptVectors,--undefined=_copy_data_init__,--undefined=_clear_bss_init__,--undefined=_end_of_init__  $CFLAGS  $1  -o $1.gnode

echo "Size of program"
msp430-size $1.gnode

echo "Convert program to ihex"
msp430-objcopy -O ihex $1.gnode upload.hex

#rm $1.gnode
#echo "Copying upload.hex to /home/rafael"
#cp upload.hex ~

#echo "Programming upload.hex via JTAG-ttyACM0"
#mspdebug tilib -q  -jd /dev/ttyACM0 "prog upload.hex"

echo "+++++ Programming via Olimex-JTAG-TINY  /dev/ttyACM0;"
mspdebug olimex -jd /dev/ttyACM0 "prog upload.hex"

