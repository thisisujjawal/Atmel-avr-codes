/*
 * LCD_4bit.c
 *
 * Created: 1/15/2020 5:49:59 PM
 * Author : Ujjawal
 */ 

#include <avr/io.h>
#include <util/delay.h>

#define lcd PORTB
#define rs PB0
#define rw PB1
#define en PB2

void lcd_cmd(unsigned char com);
void lcd_data(unsigned char data);
void lcd_string (unsigned char *str);



int main(void)
{
    /* Replace with your application code */
	DDRB = 0xff;
	
	lcd_cmd(0x02);  //home location
	lcd_cmd(0x28);  //2x16 lcd 4bit mode
	lcd_cmd(0x0C);  //display on cursor blink
	lcd_cmd(0x06);   //increment
    while (1) 
    {
		lcd_cmd(0x80);
		lcd_string("Hello");
		lcd_cmd(0xc0);
		lcd_string("World");
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