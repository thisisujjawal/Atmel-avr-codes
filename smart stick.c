/*
 * LCD_4bit.c
 *
 * Created: 1/15/2020 5:49:59 PM
 * Author : Ujjawal
 */ 
#define F_CPU 1000000UL
#include <avr/interrupt.h>
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>



static volatile int pulse = 0;  //The variable "pulse" is used to store the count value from the TCNT register
static volatile int echo_pin = 0;  // The variable "echo_pin" is used as a flag to indicate the current status of the echo

ISR(INT0_vect) //Interrupt service routine
{
	if(echo_pin==1)
	{
		TCCR1B = 0; //TIMER COUNTER CONTROL REGISTER (Stop the counter)
		pulse = TCNT1;  // store the value of counter
		TCNT1 = 0; //reset the counter
		echo_pin = 0;
	}
	if (echo_pin==0)
	{
		TCCR1B |= (1<<CS10);  //used to start the internal counter of microcontroller
		echo_pin=1;
	}
}

int main(void)
{
    /* Replace with your application code */
	DDRD = 0b11111011;
	DDRA = 0xff;
	_delay_ms(50);
	
	GICR |= (1<<INT0);  //General Interrupt Control Registor (used to configure the PIN D2 as an interrupt PIN as
	MCUCR |= (1<<ISC00); //MCU Control Register (defines that any logical change in the INT0/PIND2 Pin will interrupt
	
	//TCCR1A = 0;
	
	int16_t COUNTA = 0;
	
	sei();
    while (1) 
    {
		PORTD |= (1<<PIND0);  //Triggering the ultrasonic sensor (HIGH)
		_delay_us(15);
		PORTD&=~(1<<PIND0);
		_delay_us(15);
		
		COUNTA = pulse/58;  //calculating distance cm
		if(COUNTA >= 0 && COUNTA <=20){
			PORTA = 0xff;
			_delay_ms(50);
			PORTA = 0x00;
			_delay_ms(50);
		}
		_delay_ms(10);
    }
}

