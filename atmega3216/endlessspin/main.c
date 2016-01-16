#include <avr/io.h>
#include <util/delay.h>


int main (void) {
    DDRB |= 1 << PINB0;
    DDRB |= 1 << PINB1;
    DDRB |= 1 << PINB2;
    DDRB |= 1 << PINB3;
    int delay = 10;
    while (1) {
        PORTB ^= 1 << PINB0;
        _delay_ms(delay);
        PORTB ^= 1 << PINB0;
        PORTB ^= 1 << PINB1;
        _delay_ms(delay);
        PORTB ^= 1 << PINB1;
        PORTB ^= 1 << PINB2;
        _delay_ms(delay);
        PORTB ^= 1 << PINB2;
        PORTB ^= 1 << PINB3;
        _delay_ms(delay);
        PORTB ^= 1 << PINB3;
        PORTB ^= 1 << PINB4;
        _delay_ms(delay);
        PORTB ^= 1 << PINB4;
    }
    return 0;
}
