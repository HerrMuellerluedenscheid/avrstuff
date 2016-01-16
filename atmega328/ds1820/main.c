#include <stdlib.h>
#include <string.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include "ds18b20.h"
#include "lcd.h"
//#include "adc.h"

#define DS18B20_PORT PORTC
#define DS18B20_DDR  DDRC
#define DS18B20_PIN  PINC
#define DS18B20_DQ   PC0

#define BOILER_PORT PORTD
#define BOILER_DDR  DDRD
#define BOILER_BIT  PD7

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

#define BUFFERSIZE 12

#define F_CPU 1000000UL

int main(void){
    BOILER_DDR |= (1<<BOILER_BIT);
    heat(0);
    lcd_D7_ddr |= (1<<lcd_D7_bit);
    lcd_D6_ddr |= (1<<lcd_D6_bit);
    lcd_D5_ddr |= (1<<lcd_D5_bit);
    lcd_D4_ddr |= (1<<lcd_D4_bit);

    lcd_E_ddr |= (1<<lcd_E_bit);
    lcd_RS_ddr |= (1<<lcd_RS_bit);

    float t_base = 10;
    double d = 0;
    uint8_t t_target = 670;
    uint8_t t_target_new;
    
    //ADC_Init();

    _delay_ms(1000);
    lcd_init_4d();

    lcd_write_instructions_4d(lcd_SetCursor | lcd_LineOne);
    _delay_us(80);
    d = ds18b20_gettemp();
    sei();

    for (;;){
        //t_target_new = t_base + (100.-t_base) * read_ADC();
        //sprintf(program_version, "Ttarget: %+1.1d", (signed int)t_target_new);
        //lcd_write_hold_clear(program_version, 10000);
        //if (abs(t_target_new-t_target)>5){
        //    t_target = t_target_new;
        //    sprintf(program_version, "Ttarget: %+1.1d", (signed int)d);
        //    lcd_write_hold_clear(program_version, 10000);
        //}
        d = ds18b20_gettemp();
        d *= 10;
        sprintf(program_version, "%+1.1d", (signed int)d);
        lcd_write_hold_clear(program_version, 10000);

        if (d<t_target){
            heat(1);
        }
        else{
            heat(0);
        }
        _delay_ms(2000);
    }

    return 0;
}

void heat(unsigned int doheat){
    if (doheat){
        BOILER_PORT &= ~ (1<<BOILER_BIT);
    }
    else{
        BOILER_PORT |= (1<<BOILER_BIT);
    }
}
