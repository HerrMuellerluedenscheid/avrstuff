#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 4000000UL

int main(void)
{
    DDRD |= 0xFF;
    // Fuer verschiedene WGM (waveform generation modes) siehe Table47 im 
    // data sheet.
    // Fuer diesen Modus muessen WGM13, WGM12 und WGM11 gesetzt werden. 
    // Diese befinden sich in Register TCCR1B und TCCR1A:
    TCCR1A |= (1<<WGM10) | (1<<COM1A1) | (1<<COM1B1);
    TCCR1B |= (1<<WGM12) | (1<<CS12) | (1<<CS10);
    // Mit den beiden Coms wird inverted mode eingeschaltet, also bei 0 Volt
    // gehts los.
    
    OCR1A = 63;
    OCR1B = 127;
    // Initial position 2 ms:

    for(;;);
    return 0;
}
