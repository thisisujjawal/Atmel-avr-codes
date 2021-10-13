
#include <avr/io.h>
#include <util/delay.h>

#define datapin PORTB
#define commandpin PORTD
#define rs PD0
#define rw PD1
#define en PD2

void lcd_cmd(unsigned char com);
void lcd_data(unsigned char data);
void lcd_string (unsigned char *str);



int main(void)
{
    /* Replace with your application code */
	DDRB = 0xff;
	DDRD = 0xff;
	
	lcd_cmd(0x02);  //home location
	lcd_cmd(0x38);  //2x16 lcd 4bit mode
	lcd_cmd(0x0C);  //display on cursor blink
	lcd_cmd(0x06);   //increment
    while (1) 
    {
		lcd_cmd(0x80);
		lcd_string("Namaste");
		lcd_cmd(0xc0);
		lcd_string("Ujjawal");
    }
}

void lcd_cmd(unsigned char com)
{
	/*datapin=com;
	commandpin &= ~(1<<rs);
	commandpin &=~ (1<<rw);
	commandpin |= (1<<en);
	_delay_ms(1);
	commandpin &=~ (1<<en); */
	
	datapin=com;
	commandpin = 0b00000100;
	/*commandpin = 0b00000000;
	commandpin = 0b00000100;*/
	_delay_ms(10);
	commandpin = 0b00000000;
	
}

void lcd_data(unsigned char data)
{
	/* datapin=data;
	commandpin |= (1<<rs);
	commandpin &=~ (1<<rw);
	commandpin |= (1<<en);
	_delay_ms(1);
	commandpin &=~ (1<<en);	*/
	
	datapin=data;
	commandpin = 0b00000101;
	/*commandpin = 0b00000000;
	commandpin = 0b00000100;*/
	_delay_ms(10);
	commandpin = 0b00000000;
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