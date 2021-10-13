/*
 * LCD_4bit.c
 *
 * Created: 1/15/2020 5:49:59 PM
 * Author : Ujjawal
 */ 
#include <avr/interrupt.h>
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 1000000UL
#define lcd PORTB
#define rs PB0
#define rw PB1
#define en PB2

void lcd_cmd(unsigned char com);
void lcd_data(unsigned char data);
void lcd_string (unsigned char *str);

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
	DDRB = 0xff;
	DDRD = 0b11111011;
	_delay_ms(50);
	
	GICR |= (1<<INT0);  //General Interrupt Control Registor (used to configure the PIN D2 as an interrupt PIN as
	MCUCR |= (1<<ISC00); //MCU Control Register (defines that any logical change in the INT0/PIND2 Pin will interrupt
	
	//TCCR1A = 0;
	
	int16_t COUNTA = 0;
	char SHOWA [16];
		
	lcd_cmd(0x02);  //home location
	lcd_cmd(0x28);  //2x16 lcd 4bit mode
	lcd_cmd(0x0C);  //display on cursor blink
	lcd_cmd(0x06);   //increment
	
	sei();
    while (1) 
    {
		PORTD |= (1<<PIND0);  //Triggering the ultrasonic sensor (HIGH)
		_delay_us(15);
		PORTD&=~(1<<PIND0);
		_delay_us(15);
		
		COUNTA = pulse/58;  //calculatong distance cm
		
		lcd_cmd(0x80);
		lcd_string("Ultrasonic sensor");
		lcd_cmd(0xc0);
		lcd_string("Distance=");
		itoa(COUNTA,SHOWA,10);
		lcd_string(SHOWA);
		lcd_string("cm   ");
    }
}

void lcd_cmd(unsigned char com)
{
	//for command rs = 0 , rw = 0 , en = 1 , en = 0
	char cmd1;
	cmd1 = (com & (0xf0));   //upper 4 bit data
	lcd = cmd1;
	lcd&=~(1<<rs);  //rs=0
	lcd&=~(1<<rw);  //rw=0
	lcd|=(1<<en);  //en=1
	_delay_ms(1);
	lcd&=~(1<<en);
	
	cmd1=((com<<4)&(0xf0));  //lower 4 bit data
	lcd = cmd1;
	lcd&=~(1<<rs);  //rs=0
	lcd&=~(1<<rw);  //rw=0
	lcd|=(1<<en);  //en=1
	_delay_ms(1);
	lcd&=~(1<<en);
}

void lcd_data(unsigned char data)
{
	unsigned char data1;
	data1=(data&(0xf0));  //upper 4 bit 
	lcd=data1;
	lcd|=(1<<rs);  //rs=1
	lcd&=~(1<<rw);  //rw=0
	lcd|=(1<<en);  //en=1
	_delay_ms(1);
	lcd&=~(1<<en);
	
	data1=((data<<4)&(0xf0)); //lower 4 bit data
	lcd = data1;
	lcd=data1;
	lcd|=(1<<rs);  //rs=1
	lcd&=~(1<<rw);  //rw=0
	lcd|=(1<<en);  //en=1
	_delay_ms(1);
	lcd&=~(1<<en);
}

void lcd_string(unsigned char *str)
{
	int i=0;
	while(str[i]!='\0')
	{
		lcd_data(str[i]);
		i++;
	}
}