#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "lcd.h"
#include "pwm.h"
#include "util.h"
#include "math.h"
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


void reverse(char *str, int len){
    int i=0, j=len-1;
    char temp;
    while (i<j){
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++, j--;
    }
}


int intToStr(int x, char str[], int d){
    int i = 0;
    while (x){
        str[i++] = (x%10) + '0';
        x = x/10;
    }

    while (i<d){
        str[i++] = '0';
    }
    reverse(str, i);
    str[i] = '\0';
    return i;
}

void ftoa(float n, char *res, int afterpoint){
    int ipart = (int)n;

    float fpart = n - (float)ipart;

    int i = intToStr(ipart, res, 0);

    if (afterpoint != 0){
        res[i] = '.';
        fpart = fpart * pow(10, afterpoint);
        intToStr((int)fpart, res + i + 1, afterpoint);
    }
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
    
    float poti_value, last_poti_value;
    float frac;
    
    lcd_write_instructions_4d(lcd_Clear);
    lcd_write_instructions_4d(lcd_SetCursor | lcd_LineOne);
    char res[20];
    while (1) {
        
        _delay_ms(100);
        ADCSRA |= (1<<ADSC);
        while (!(ADCSRA & 0x10));
        
        poti_value = ADCL;
        poti_value += (ADCH<<8);
        
        frac = (float) poti_value/1023.;
        set_PWM_range(frac, 0., 19999);
        if (last_poti_value-poti_value!=0){
            ftoa(poti_value, res, 1);
            lcd_print(res);
            last_poti_value = poti_value;
        }
    }
    return 0;
}

