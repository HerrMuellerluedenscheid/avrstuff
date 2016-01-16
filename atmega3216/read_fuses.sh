#/bin/bash

# Very helpfull: blog.louic.nl/?p=161

# Reads the fuse bits of atmega32 and writes them to low.hex and 
# high.hex files
#
# For fuse low/high byte configuration see atmega32 documentation 
# on page 256, table 105/106.
#  default fuse high byte setting: 10011001
#  default fuse low byte setting:  11100001

AVRDUDE_PORT=/dev/spidev0.0  # programmer connected to serial device
AVRDUDE_PROGRAMMER=linuxspi
MCU="atmega32"
AVRDUDE_FLAGS="-p $MCU -P $AVRDUDE_PORT -c $AVRDUDE_PROGRAMMER"

avrdude $AVRDUDE_FLAGS -U hfuse:r:high.bin:b -U lfuse:r:low.bin:b


