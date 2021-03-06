
#include <avr/io.h>
#include <util/delay.h>

#define datapin PORTB
#define commandpin PORTD
#define rs PD0
#define rw PD1
#define en PD2

void lcd_cmd(unsigned char com);     //command function
void lcd_data(unsigned char data);   //data function
void lcd_string (unsigned char *str);  //string function that will takeaddresses of the char array



int main(void)
{
	DDRB = 0xff;    //data pins configure as output pin 
	DDRD = 0xff;	//command pins configure as output pin 
	
	lcd_cmd(0x02);  //home location
	lcd_cmd(0x38);  //2x16 lcd 4bit mode
	lcd_cmd(0x0C);  //display on cursor blink
	lcd_cmd(0x06);   //increment
    while (1) 
    {
		lcd_cmd(0x80);      //for first row
		lcd_string("My name is");
		lcd_cmd(0xc0);    //for second row
		lcd_string("Ujjawal Singhal");
    }
}

void lcd_cmd(unsigned char com)
{
	datapin=com;   //in this we will copy the command that was sent to it from the the main function
	commandpin &= ~(1<<rs);   // this will select the command mode by giving logic 0 to rs
	commandpin &=~ (1<<rw);	// this will select the write mode by giving logic 0 to rw
	commandpin |= (1<<en);   // this will enable the process of the command given to it by enabling en by giving it logic 1
	_delay_ms(10);
	commandpin &=~ (1<<en);    //after enabling en, it is very important for you to turn it off by giving it logic 0
	
}

void lcd_data(unsigned char data)
{
	datapin=data;	//in this we will copy a character that was sent to it from the the string function .... we cannot send direct dta from main function as at a time it can process only single character so we have made a seperate funcction call string for this work
	commandpin |= (1<<rs);	// this will select the data mode by giving logic 1 to rs
	commandpin &=~ (1<<rw);	// this will select the write mode by giving logic 0 to rw
	commandpin |= (1<<en);	// this will enable the process of the command given to it by enabling en by giving it logic 1
	_delay_ms(1);
	commandpin &=~ (1<<en); //after enabling en, it is very important for you to turn it off by giving it logic 0
}

void lcd_string(unsigned char *str)  //this function is just for suppling character by character to the data function
{
	int i=0;
	while(str[i]!='\0')
	{
		lcd_data(str[i]);
		i++;
	}
}