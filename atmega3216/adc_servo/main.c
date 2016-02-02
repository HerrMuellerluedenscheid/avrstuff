#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "lcd.h"
#include "pwm.h"
#include "util.h"
#define F_CPU 1000000L

void ADC_Init(void){
    ADCSRA |= 1<<ADPS2;  // Frequenvorteiler
    // AVCC as reference voltage
    ADMUX |= (1<<REFS1);
    ADCSRA |= 1<<ADIE;

    ADCSRA |= 1<<ADEN;
     
    // Dummy conversion
    ADCSRA |= (1<<ADSC);
}


int main (void) {

    // ADC enable
    ADC_Init();
    setup_PWM();
    lcd_D7_ddr |= (1<<lcd_D7_bit);
    lcd_D6_ddr |= (1<<lcd_D6_bit);
    lcd_D5_ddr |= (1<<lcd_D5_bit);
    lcd_D4_ddr |= (1<<lcd_D4_bit);

    lcd_E_ddr |= (1<<lcd_E_bit);
    lcd_RS_ddr |= (1<<lcd_RS_bit);
    lcd_RW_ddr |= (1<<lcd_RW_bit);
    lcd_init_4d();
    lcd_write_instructions_4d(lcd_SetCursor | lcd_LineOne);
    lcd_write_string_4d(program_version);
    _delay_ms(1000);
    lcd_write_instructions_4d(lcd_SetCursor | lcd_LineTwo);
    lcd_write_string_4d("XXXXXXXXXXXXXXXX");
    //uint8_t poti_value;
    
    float poti_value;
    float frac;
    while (1) {
        
        _delay_ms(100);
        ADCSRA |= (1<<ADSC);
        while (!(ADCSRA & 0x10));
        
        poti_value = ADCL;
        poti_value += (ADCH<<8);
        
        //lcd_write_instructions_4d(lcd_Clear);
        //lcd_write_instructions_4d(lcd_SetCursor | lcd_LineOne);
        //lcd_write_string_4d(int(poti_value));
        
        frac = (float) poti_value/1023.;
        set_PWM_range(frac, 0., 19999);
        }
    return 0;
}

