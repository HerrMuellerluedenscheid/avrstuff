#include <avr/io.h>
#include <util/delay.h>

#include "lcd.h"

int main(void){

    DDRB |= 1<<PINB0;
    PORTB |= 1<<PINB0;
    lcd_D7_ddr |= (1<<lcd_D7_bit);
    lcd_D6_ddr |= (1<<lcd_D6_bit);
    lcd_D5_ddr |= (1<<lcd_D5_bit);
    lcd_D4_ddr |= (1<<lcd_D4_bit);

    lcd_E_ddr |= (1<<lcd_E_bit);
    lcd_RS_ddr |= (1<<lcd_RS_bit);

    lcd_init_4d();

    lcd_write_instructions_4d(lcd_SetCursor | lcd_LineOne);
    _delay_us(80);

    lcd_write_string_4d(program_version);
    while(1);
    return 0;
}

