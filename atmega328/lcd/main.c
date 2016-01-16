#include <avr/io.h>
#include <util/delay.h>

#define LCD_port        PORTC
#define DDR_LCD_port    DDRC
#define RS              4    // register select: entscheided ob gesendete info
                             // ein command oder ein char war.
#define ReadWrite       7    // Read: from LCD-> MC
                             // Write: from MC-> LCD

// Prototypes:
void check_LCD_busy(void);
void send_command(unsigned char command);
void send_character(unsigned char character);

int main(void){
    DDR_LCD_port |= 1<<ReadWrite | 1<<RS;
    _delay_ms(15);           // warte 15 ms zum starten

    send_command(0x01);     // clear screen 0x01 = 00000001
    _delay_ms(2);
    send_command(0x38);
    _delay_us(50);
    send_command(0b0001110); // cursor on, blinking
    _delay_us(50);
    send_character(0x41);   // ASCII character
    while(1)
    {
    }

}

void check_LCD_busy(void)
{
    //DDR_LCD_port = 0;   // schalte alle auf input
    LCD_port |= 1<<ReadWrite;
    LCD_port &= ~1<<RS;
    DDR_LCD_port &= ~ 1<<PC4;       // PC4 wird zum input. Ist high solange busy
    while(LCD_port & (1<<PC))
    {
    }
    DDR_LCD_port |= 1<<PC4;       // PC4 wird wieder zum output
    //DDR_LCD_port = 0xFF; // schalte alle wieder auf output
}

void send_command(unsigned char command)
{
    LCD_port = command;
    LCD_port &= ~( 1<<ReadWrite | 1<<RS);      // write mode: ReadWrite is off.
    //LCD_port = 0;
}

void send_character(unsigned char character)
{
    LCD_port = character;
    LCD_port &= ~ ( 1<<ReadWrite);
    LCD_port |= ~ ( 1<<RS);
    //LCD_port = 0;                 // clear
}

