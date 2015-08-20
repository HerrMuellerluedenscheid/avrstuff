#/bin/bash

# Very helpfull: blog.louic.nl/?p=161

# Write the fuse bits of atmega32 to use 4 MHz
#
# For fuse low/high byte configuration see atmega32 documentation 
# on page 256, table 105/106.

# To operate at 4 MHz (see p. 27, table 9) CKSEL3..0: 0011
# Thus I want:
# fuse high byte setting: 10011001 (unchanged)
# fuse low byte setting:  11100011 

AVRDUDE_PORT=/dev/spidev0.0  # programmer connected to serial device
AVRDUDE_PROGRAMMER=linuxspi
MCU="atmega32"
AVRDUDE_FLAGS="-p $MCU -P $AVRDUDE_PORT -c $AVRDUDE_PROGRAMMER"

avrdude $AVRDUDE_FLAGS -U lfuse:w:0b11100011:m


