#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 1000000L


int main(void)
{
    DDRD |= 0xFF;
    // Fuer verschiedene WGM (waveform generation modes) siehe Table47 im 
    // data sheet.
    // Fuer diesen Modus muessen WGM13, WGM12 und WGM11 gesetzt werden. 
    // Diese befinden sich in Register TCCR1B und TCCR1A:
    TCCR1A |= 1<<WGM11 | 1<<COM1A1 | 1<<COM1A0;
    TCCR1B |= 1<<WGM12 | 1<<WGM13 | 1<<CS10;
    // Mit den beiden Coms wird inverted mode eingeschaltet, also bei 0 Volt
    // gehts los.
    
    // Wir benutzen hier Fast PWM /|/|/|/|/| wobei der ICR1 den hoechsten Wert
    // der gezaehlt wird angiebt. Also fuer 50 Hz PWM bei 1 MHz Takt waere
    // ICR1=20000-1 weil bei 0 losgezaehlt wird.
    ICR1 = 19999;
    //OCR1A = ICR1 - 2000; //18000
    
    int position_left = 1000;
    int position_right = 2000;
    int i=position_right;
    int sign=-1;
    float repeat = 0.9;
    OCR1A = ICR1 - position_left; //18000

    // Initial position 2 ms:
    while (1)
    {   
        
        // OCR1A pin (pin 19) ist der output pin.
        OCR1A = ICR1-i; //18000
        _delay_ms(repeat);
        if (i==position_right)
        {
            sign = -1;
        }
        else if (i==position_left)
        {
            sign = 1;
        }
        else
        {
        }
        i += 1*sign;
    }   //
    return 0;
}


