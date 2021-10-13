/*
 * sevensegmentdisplay.c
 *
 * Created: 1/15/2020 12:59:38 PM
 * Author : Ujjawal
 */ 

#include <avr/io.h>
#include <util/delay.h>
 //this is for common anode that means give 0 for glow and 1 for not glow
void check (void)
{
	PORTA = 0b01111111; //a
	_delay_ms(1000);
	PORTA = 0b10111111; //b
	_delay_ms(1000);
	PORTA = 0b11011111; //c
	_delay_ms(1000);
	PORTA = 0b11101111; //d
	_delay_ms(1000);
	PORTA = 0b11110111; //e
	_delay_ms(1000);
	PORTA = 0b11111011; //f
	_delay_ms(1000);
	PORTA = 0b11111101; //g
	_delay_ms(1000);
	PORTA = 0b11111110; //dp
	_delay_ms(1000);
	
}

void num_display (void)
{
	PORTA = 0b10011111;      //1
	_delay_ms(1000);
	
	PORTA = 0b00100100;      //2
	_delay_ms(1000);
	
	PORTA = 0b00001101;      //3
	_delay_ms(1000);
	
	PORTA = 0b10011000;      //4
	_delay_ms(1000);
	
	PORTA = 0b01001001;      //5
	_delay_ms(1000);
	
	PORTA = 0b01000000;      //6
	_delay_ms(1000);
	
	PORTA = 0b00011111;      //7
	_delay_ms(1000);
	
	PORTA = 0b00000000;      //8
	_delay_ms(1000);
	
	PORTA = 0b00001001;      //9
	_delay_ms(1000);
	
	PORTA = 0b00000010;      //0
	_delay_ms(1000);
}
	
int main(void)
{
    /* Replace with your application code */
	DDRA = 0xff;
	
	check();
    while (1) 
    {
		num_display();
    }
}

