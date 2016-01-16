#ifndef DS18B20_H_
#define DS18B20_H_

#include <avr/io.h>

#define DS18B20_PORT PORTC
#define DS18B20_DDR  DDRC
#define DS18B20_PIN  PINC
#define DS18B20_DQ   PC0

#define DS18B20_ConvertTemp     0x44
#define DS18B20_RScratchPad     0xbe
#define DS18B20_WScratchPad     0x4e
#define DS18B20_CPYScratchPad   0x48
#define DS18B20_RECEEPROM       0xb8
#define DS18B20_RPWSupply       0xb4
#define DS18B20_SearchROM       0xf0
#define DS18B20_ReadROM         0x33
#define DS18B20_MatchROM        0x55
#define DS18B20_SkipROM         0xcc
#define DS18B20_AlarmSearch     0xec

//stop any interrupt on read
#define DS18B20_StopInterruptOnRead 1

//functions
extern double ds18b20_gettemp();

#endif
