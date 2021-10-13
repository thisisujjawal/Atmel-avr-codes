/*
 * LED blinking.c
 *
 * Created: 1/14/2020 6:13:22 PM
 * Author : Ujjawal
 */ 

#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
    /* Replace with your application code */
	DDRC = 0b11111111;
    while (1) 
    {
		PORTC = 0b00000001;
		_delay_ms(1000);
		PORTC = 0b00000010;
		_delay_ms(1000);
		PORTC = 0b00000100;
		_delay_ms(1000);
    }
}

