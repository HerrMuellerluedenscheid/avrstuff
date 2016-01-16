//Test cpu freq. At correct F_CPU the led should blink at 1 Hz.

#define F_CPU 4000000

#include <avr/io.h>
#include <util/delay.h>

#define LED_PORT PORTA
#define LED_DDR DDRA
#define LED_PIN PA1

int main()
{
    LED_DDR |= 1 << LED_PIN;

    while (1)
    {
        LED_PORT ^= 1 << LED_PIN;
        _delay_ms(1000);
    }
    return 0;
}
