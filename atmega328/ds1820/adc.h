#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


void ADC_Init(void){
    uint8_t ADC_PIN = (uint8_t) 1;

    ADCSRA |= 1<<ADPS2;  // Frequenvorteiler
    // AVCC as reference voltage
    ADMUX |= (1<<REFS1);
    ADMUX |= (1<<MUX0);
    //ADMUX |= ADC_PIN;
    ADCSRA |= 1<<ADIE;

    ADCSRA |= 1<<ADEN;
     
    // Dummy conversion
    ADCSRA |= (1<<ADSC);
    return;
}

float read_ADC(void){
    float poti_value;
    float frac;
    
    _delay_ms(100);
    ADCSRA |= (1<<ADSC);
    while (!(ADCSRA & 0x10));
    
    poti_value = ADCL;
    poti_value += (ADCH<<8);
    
    frac = (float) poti_value/1023.;
    return frac;
}
