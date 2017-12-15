
echo ""
echo "Uploading file $1 via Olimex-JTAG-TINY"

echo "Size of program"
msp430-size $1
echo ""

echo "Convert program to ihex"
msp430-objcopy -O ihex          $1 upload.ihex
echo "Convert program to txt"
msp430-objcopy -O symbolsrec    $1 upload.txt      # Show the address of each function.
echo "Convert program to bin"
msp430-objcopy -O binary        $1 upload.bin      # Show the strings for debugging.
echo "Convert program to text"
msp430-objcopy -O verilog       $1 upload.text     # Generate to TI-text firmware with 20-bit addressing. "q"
echo ""

#echo "Programming via FET430UIF JTAG /dev/ttyACM0"
#echo ""
#mspdebug tilib  -jd /dev/ttyACM0 "prog upload.ihex"

echo "Programming via UART-BSL /dev/ttyUSB0"
echo "mspdebug -d /dev/ttyUSB0 --long-password flash-bsl \"prog upload.ihex\""
echo ""
mspdebug -d /dev/ttyUSB0 --long-password flash-bsl "prog upload.ihex"

#echo "+++++ Programming via Olimex-JTAG-TINY  /dev/ttyACM0;"
#echo ""
#mspdebug olimex -jd /dev/ttyACM0 "prog upload.ihex"

#rm $1.gnode
#echo "Copying upload.ihex to /home/rafael"
#echo ""
#cp upload.ihex ~


