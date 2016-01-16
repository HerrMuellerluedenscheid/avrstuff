#define F_CPU 1000000L

#include <avr/io.h>
#include <util/delay.h>

#define lcd_D7_port PORTD
#define lcd_D7_bit  PORTD7
#define lcd_D7_ddr  DDRD

#define lcd_D6_port PORTD
#define lcd_D6_bit  PORTD6
#define lcd_D6_ddr  DDRD

#define lcd_D5_port PORTD
#define lcd_D5_bit  PORTD5
#define lcd_D5_ddr  DDRD

#define lcd_D4_port PORTD
#define lcd_D4_bit  PORTD4
#define lcd_D4_ddr  DDRD


#define lcd_E_port  PORTC
#define lcd_E_bit   PORTC3
#define lcd_E_ddr   DDRC

#define lcd_RW_port PORTC
#define lcd_RW_bit  PORTC4
#define lcd_RW_ddr  DDRC

#define lcd_RS_port PORTC
#define lcd_RS_bit  PORTC5
#define lcd_RS_ddr  DDRC


#define lcd_LineOne 0x00 // start of line 2
#define lcd_LineTwo 0x40 // start of line 2

// LCD instructions
#define lcd_Clear           0b00000001
#define lcd_Home            0b00000010
#define lcd_EntryMode       0b00000110
#define lcd_DisplayOff      0b00001000
#define lcd_DisplayOn       0b00001100
#define lcd_FunctionReset   0b00011000
#define lcd_FunctionSet4bit 0b00101000
#define lcd_SetCursor       0b10000000

uint8_t program_version[] = "BrewMate";

// prototypes
void lcd_write_4(uint8_t);
void lcd_write_instructions_4d(uint8_t);
void lcd_write_character_4d(uint8_t);
void lcd_write_string_4d(uint8_t *);
void lcd_init_4d(void);


void lcd_init_4d(void){
    _delay_ms(100);  // powerup delay
    lcd_RS_port &= ~(1<<lcd_RS_bit);
    lcd_E_port &= ~(1<<lcd_E_bit);

    lcd_write_4(lcd_FunctionReset);
    _delay_ms(10);
    lcd_write_4(lcd_FunctionReset);
    _delay_us(200);
    lcd_write_4(lcd_FunctionReset);
    _delay_us(200);
    
    lcd_write_4(lcd_FunctionSet4bit);
    _delay_us(80);

    lcd_write_instructions_4d(lcd_Clear);
    _delay_ms(4);
    lcd_write_instructions_4d(lcd_EntryMode);
    _delay_us(80);
    lcd_write_instructions_4d(lcd_DisplayOn);
    _delay_us(80);
}

void lcd_write_string_4d(uint8_t theString[]) {
    volatile int i = 0;
    while (theString[i] != 0)
    {
        lcd_write_character_4d(theString[i]);
        i++;
        _delay_us(80);
    }
}

void lcd_write_character_4d(uint8_t theData){
    lcd_RS_port |= (1<<lcd_RS_bit);
    lcd_E_port &= ~(1<<lcd_E_bit);
    lcd_write_4(theData);
    lcd_write_4(theData << 4);
}

void lcd_write_instructions_4d(uint8_t theInstructions){
    lcd_RS_port &= ~(1<<lcd_RS_bit);
    lcd_E_port &= ~(1<<lcd_E_bit);
    lcd_write_4(theInstructions);
    lcd_write_4(theInstructions << 4);
}

void lcd_write_4(uint8_t theByte) {
    lcd_D7_port &= ~ (1<<lcd_D7_bit);
    if (theByte & 1<<7) lcd_D7_port |= (1<<lcd_D7_bit);
    
    lcd_D6_port &= ~ (1<<lcd_D6_bit);
    if (theByte & 1<<6) lcd_D6_port |= (1<<lcd_D6_bit);
    
    lcd_D5_port &= ~ (1<<lcd_D5_bit);
    if (theByte & 1<<5) lcd_D5_port |= (1<<lcd_D5_bit);
    
    lcd_D4_port &= ~ (1<<lcd_D4_bit);
    if (theByte & 1<<4) lcd_D4_port |= (1<<lcd_D4_bit);

    lcd_E_port |= (1<<lcd_E_bit);
    _delay_us(1);

    lcd_E_port &= ~ (1<<lcd_E_bit);
    _delay_us(1);
}
