#include <avr/io.h>
#include <util/delay.h>

#define Richard 0
#define Lisa 1
#define Anton 2

int main (void) {

    int i;
    // Setze alle Ausgaenge an Port A auf Ausgang
    DDRA = 0xff;

    // Gib auf Pin 0 und 1 3.3v
    PORTA |= (1<<Richard) | (1<<Lisa) | (1<<Anton);

    _delay_ms(2000);
    while (1) {
        i = 0;
        PORTA = PORTA ^(1 << Richard);
        _delay_ms(100);

        //PORTA |= (1 << Richard);
        //_delay_ms(100);
        //PORTA &= ~(1<<Lisa);
        //if (PINA & (1<<Lisa)){
        //    while (i<=201){
        //        PORTA = PORTA ^(1<<Lisa);
        //        _delay_ms(10);
        //        i = i+1;
        //    }
        //}
        //else{
        //    while (i<=20){
        //        PORTA = PORTA ^(1<<Lisa);
        //        _delay_ms(100);
        //        i = i+1;
        //    }
        //}
        //_delay_ms(1000);
    }
    return 0;
}
