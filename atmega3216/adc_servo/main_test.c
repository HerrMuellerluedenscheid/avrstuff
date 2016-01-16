#include <avr/io.h>
#include <util/delay.h>

#define Richard 0
#define Lisa 1
#define Anton 2

int main (void) {
    // TESTE DAS OSZI.......
    int i;
    // Setze alle Ausgaenge an Port A auf Ausgang
    DDRA = 0xff;

    // Gib auf Pin 0 und 1 3.3v
    PORTA |= (1<<Richard) | (1<<Lisa) | (1<<Anton);

    _delay_ms(2000);
    while (1) {
        i = 0;
        PORTA &= ~(1 << Richard);
        _delay_ms(1);
    }
    return 0;
}
