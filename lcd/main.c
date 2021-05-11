/*
 * lcd.c
 *
 * Created: 10.05.2021 18:36:46
 * Author : User
 */ 
#define F_CPU 4000000
#include <avr/io.h>
#include <util/delay.h>


#define VDD PIND0
#define RS PIND1
#define E PIND2
#define D4 PIND3
#define D5 PIND4
#define D6 PIND5
#define D7 PIND6

void init()
{
	DDRD |= (1<<VDD)|(1<<RS)|(1<<E)|(1<<D4)|(1<<D5)|(1<<D6)|(1<<D7);
	PORTD &= ~((1<<VDD)|(1<<RS)|(1<<E)|(1<<D4)|(1<<D5)|(1<<D6)|(1<<D7));
	PORTD |= (1<<VDD);
	_delay_ms(20);
	PORTD |= (1<<E);
	_delay_us(50);
	PORTD |= (1<<D4)|(1<<D5);
	PORTD &= ~(1<<E);
	_delay_us(4200);
	PORTD |= (1<<E);
	_delay_us(50);
	PORTD &= ~(1<<E);
	_delay_us(150);
	PORTD |= (1<<E);
	_delay_us(50);
	PORTD &= ~(1<<E);
	_delay_ms(1);
	PORTD |= (1<<E);
	_delay_us(50);
	PORTD &= ~(1<<D4);
	PORTD &= ~(1<<E);
	_delay_ms(1);
}

void command (unsigned char data)
{
	PORTD &= ~(1<<RS);
	unsigned char data_h = data>>1;
	data_h &= 0b01111000;
	unsigned char data_l = data<<3;
	data_l &= 0b01111000;
	PORTD |= (1<<E);
	_delay_us(50);
	PORTD &= ~((1<<D4)|(1<<D5)|(1<<D6)|(1<<D7));
	PORTD |= data_h;
	PORTD &= ~(1<<E);
	_delay_us(50);
	PORTD |= (1<<E);
	_delay_us(50);
	PORTD &= ~((1<<D4)|(1<<D5)|(1<<D6)|(1<<D7));
	PORTD |= data_l;
	PORTD &= ~(1<<E);
	_delay_ms(1);
}

void send (unsigned char data)
{
	PORTD |= (1<<RS);
	unsigned char data_h = data>>1;
	data_h &= 0b01111000;
	unsigned char data_l = data<<3;
	data_l &= 0b01111000;
	PORTD |= (1<<E);
	_delay_us(50);
	PORTD &= ~((1<<D4)|(1<<D5)|(1<<D6)|(1<<D7));
	PORTD |= data_h;
	PORTD &= ~(1<<E);
	_delay_us(50);
	PORTD |= (1<<E);
	_delay_us(50);
	PORTD &= ~((1<<D4)|(1<<D5)|(1<<D6)|(1<<D7));
	PORTD |= data_l;
	PORTD &= ~(1<<E);
	_delay_ms(1);
}

void set_position (unsigned char stroka, unsigned char symb)
{
	command((0x40*stroka+symb)|0b10000000);
}

int main(void)
{
	
	init();
	command(0b00101000); //4-bit, 2-lines
	//command(0b00001100); //display_on, cursor_off, blink_off
	command(0b00001111); //display_on, cursor_on, blink_on
	command(0b00000110); //cursor_right, no_display_shift
	
	command(0b01000000);
	send(0b00011111);
	send(0b00011110);
	send(0b00011110);
	send(0b00011100);
	send(0b00011100);
	send(0b00011000);
	send(0b00011000);
	send(0b00010000);

	send(0b00010000);
	send(0b00011000);
	send(0b00011000);
	send(0b00011100);
	send(0b00011100);
	send(0b00011110);
	send(0b00011110);
	send(0b00011111);
	
	send(0b00000000);
	send(0b00000001);
	send(0b00000001);
	send(0b00000011);
	send(0b00000011);
	send(0b00000111);
	send(0b00000111);
	send(0b00001111);
	
	send(0b00001111);
	send(0b00000111);
	send(0b00000111);
	send(0b00000011);
	send(0b00000011);
	send(0b00000001);
	send(0b00000001);
	send(0b00000000);
	
	send(0b00010001);
	send(0b00001110);
	send(0b00010001);
	send(0b00010101);
	send(0b00010001);
	send(0b00001110);
	send(0b00001010);
	send(0b00011011);
	
	set_position(0,0);
	send('W');_delay_ms(200);
	send('a');_delay_ms(200);
	send('k');_delay_ms(200);
	send('e');_delay_ms(200);
	send(' ');_delay_ms(200);
	send('u');_delay_ms(200);
	send('p');_delay_ms(200);
	send(',');_delay_ms(200);
	send(' ');_delay_ms(200);
	send('N');_delay_ms(200);
	send('e');_delay_ms(200);
	send('o');_delay_ms(200);
	send('!');	_delay_ms(200);
	send(' ');_delay_ms(200);
	send(' ');_delay_ms(200);
	
	
	set_position(1,0);
	send('Y');_delay_ms(200);
	send('o');_delay_ms(200);
	send('u');_delay_ms(200);
	send(' ');_delay_ms(200);
	send('o');_delay_ms(200);
	send('b');_delay_ms(200);
	send('o');_delay_ms(200);
	send('s');_delay_ms(200);
	send('r');_delay_ms(200);
	send('a');_delay_ms(200);
	send('l');_delay_ms(200);
	send('s');_delay_ms(200);
	send('y');_delay_ms(200);
	send('a');_delay_ms(200);
	send('!');_delay_ms(200);

	set_position(0,15);
	send(4);
	set_position(1,15);
	
	
    /* Replace with your application code */
    while (1) 
    {
    }
}

