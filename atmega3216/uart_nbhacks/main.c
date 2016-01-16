#include <avr/io.h>
#include <stdio.h>

void USART_vInit(void){

    //set baud rate
    //UBRRH = (unsigned char)(103>>8);
    //UBRRL = (unsigned char) 103;
    UBRRH = (unsigned char)(25 >>8);
    UBRRL = (unsigned char) 25;

    // enable receiver and transmitter
    UCSRB = (1<<RXEN) | (1<<TXEN);
    
    // Set frame format to 8 data bits, no parity, 1 stop bit
    UCSRC = (1<<URSEL) | (0<<UCSZ1) | (1<<UCSZ0) | (0<<USBS);
    //UCSRC = (1<<URSEL) | (3<<UCSZ0) | (1<<USBS);
}

void USART_Transmit (unsigned int data)
{
    //Wait until the Transmitter is ready
    while (! (UCSRA & (1 << UDRE)) ); 
    
    //Make the 9th bit 0 for the moment
    UCSRB &=~(1 << TXB8); 
    
    //If the 9th bit of the data is a 1
    if (data & 0x0100) 
    
    //Set the TXB8 bit to 1
    UCSRB |= (1 << TXB8); 
    
    //Get that data outa here!
    UDR = data;
    }

unsigned char USART_Receive( void )
{
    while ( !(UCSRA & (1 << RXC)) ); //Wait for the RXC to not have 0
    return UDR; //Get that data outa there and back to the main program!
}

int main (void) {
    DDRB = 0xFF;
    uint8_t u8Data;

    // Initialize USART
    USART_vInit();

    // Send string
    USART_Transmit(1);

    // Repeat indefinitely
    for (;;) //forever
    {
        //Echo received characters
        u8Data = USART_Receive();

        if(u8Data == 0xAA)
        {
            u8Data = USART_Receive();
            PORTB = u8Data;
        }
    }
}
