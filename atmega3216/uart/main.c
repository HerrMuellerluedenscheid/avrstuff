#define F_CPU 4000000
#define sending 0
#define receiving 1
#define __DELAY_BACKWARD_COMPATIBLE__

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

void LED_init(void){
    DDRA = 0xff;
}

void toggle_LED(int id){
    PORTA ^= (1<<id);
}

void blink_LED(int id, int f, float duration){
    // f -> frequency of flickering in Hz
    int num_flick_flacks = duration * f;
    int count = 0;
    int dly = 1000/f;
    int initial_state = id;
    while(count<num_flick_flacks){
        PORTA = PORTA ^(1 << id );
        count += 1;
        _delay_ms(dly);
    }
    PORTA |= (initial_state << id );
}

void USART_vInit(void){

    //set baud rate
    UBRRH = (unsigned char)(25>>8);
    UBRRL = (unsigned char) 25;

    // enable receiver and transmitter
    UCSRB = (1<<RXEN) | (1<<TXEN);
    
    // Set frame format to 8 data bits, odd parity, 1 stop bit
    // USBS: Stop Bit Selection if USBS=0 -> 1 bit  (table 65)
    // UCSZ: Character SiZe (table 66):
    //  UCSZ0 ==1 & UCSZ1 ==1 -> 8 bit
    // UPM: Parity Mode (table 64) if UPM1=UPM0=0 -> no parity
    UCSRC = (1<<URSEL) | (1<<UCSZ1) | (1<<UCSZ0) | (0<<USBS) | (0<<UPM0) | (0<<UPM1);
}

void USART_vSendByte(uint8_t u8Data){

    // wait if a byte is being transmitted
    while((UCSRA&(1<<UDRE))==0);
    
    blink_LED(sending, 10, 0.2);

    // transmit data
    UDR = u8Data;
    UDR = 10;
}
void USART_vSendChar(char u8Data){

    // wait if a byte is being transmitted
    // UDRE: Data Register Empty flag.
    // While data is transmitted, UDRE is not empty. 
    // Another option to check if data is been sent is to read the state of
    // TXC (transmit complete)
    while((UCSRA&(1<<UDRE))==0);

    blink_LED(sending, 10, 0.2);
    // As soon as UDRE is empty, transmit data
    UDR = u8Data;
}

uint8_t USART_vReceiveByte(){
    // Wait until a byte has been received
    while ((UCSRA&(1<<RXC)) == 0);

    blink_LED(receiving, 10, 1);
    // Return received data
    return UDR;
}

int main (void) {
    DDRB = 0xFF;
    uint8_t u8Data;
    uint8_t i = 0;
    char val = '0';
    // Initialize USART
    USART_vInit();
    LED_init();
    blink_LED(receiving, 10, 1);
    blink_LED(sending, 10, 1);
    while (i<4){
        // Send string
        if (i==100){
            i = 0;
        }
        USART_vSendByte(88);
        i = i + 1;

    }
    // Repeat indefinitely
    for (;;) //forever
    {
        blink_LED(receiving, 20, 0.5);
        u8Data = USART_vReceiveByte();

        if(u8Data == 0xAA)
        {
            USART_vSendByte(u8Data);
            _delay_ms(1000);
        }
        if (u8Data == 50){
            toggle_LED(receiving);
            blink_LED(receiving, 10, 1);
            blink_LED(sending, 10, 1);
        }
    }
}
