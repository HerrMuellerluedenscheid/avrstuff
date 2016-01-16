#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "pwm.h"
#define F_CPU 1000000L

int main (void) {

    void ADC_Init(void){
        ADCSRA |= 1<<ADPS2;  // Frequenvorteiler
        // AVCC as reference voltage
        ADMUX |= (1<<REFS1);
        ADCSRA |= 1<<ADIE;

        ADCSRA |= 1<<ADEN;
         
        // Dummy conversion
        ADCSRA |= (1<<ADSC);
    }
    // ADC enable
    ADC_Init();
    setup_PWM();
    _delay_ms(1000);
    //set_PWM_percent(1000);
    
    //uint8_t poti_value;
    float poti_value;
    float frac;
    while (1) {
        
        _delay_ms(100);
        ADCSRA |= (1<<ADSC);
        while (!(ADCSRA & 0x10));
        
        poti_value = ADCL;
        poti_value += (ADCH<<8);
        
        frac = (float) poti_value/1023.;
        set_PWM_range(frac, 0., 19999);
        //set_PWM_percent(frac);
        }
    return 0;
}

