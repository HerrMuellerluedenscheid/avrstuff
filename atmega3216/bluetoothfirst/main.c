#include <avr/io.h>
#include <stdio.h>

void USART_vInit(void){

    //set baud rate
    UBRRH = (uint8_t)(51>>8);
    UBRRL = (uint8_t)51;
    
    // Set frame format to 8 data bits, no parity, 1 stop bit
    UCSRC = (0<<USBS)|(3<<UCSZ0);

    // enable receiver and transmitter
    UCSRB = (1<<RXEN)|(1<<TXEN);
}

void USART_vSendByte(uint8_t u8Data){

    // wait if a byte is being transmitted
    while((UCSRA&(1<<UDRE))==0);

    // transmit data
    UDR = u8Data;
}

uint8_t USART_vReceiveByte(){
    // Wait until a byte has been received
    while ((UCSRA&(1<<RXC)) == 0);

    // Return received data
    return UDR;
}

int main (void) {
    DDRB = 0xFF;
    uint8_t u8Data;

    // Initialize USART
    USART_vInit();

    // Send string
    USART_vSendByte('A');

    // Repeat indefinitely
    for (;;) //forever
    {
        //Echo received characters
        u8Data = USART_vReceiveByte();

        if(u8Data == 0xAA)
        {
            u8Data = USART_vReceiveByte();
            PORTB = u8Data;
        }
    }
}
