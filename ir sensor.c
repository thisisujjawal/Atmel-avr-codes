/*
 * IR_sensor.c
 *
 * Created: 1/15/2020 2:08:59 PM
 * Author : Ujjawal
 */ 

#include <avr/io.h>
 void one (void)
 {
	 PORTA = 0b10011111;
 }
  void zero (void)
  {
	  PORTA = 0b00000011;
  }

int main(void)
{
	DDRA = 0xff;
	DDRC = 0x00;
    /* Replace with your application code */
    while (1) 
    {
		int x = PINC & 0b00000001;
		if (x==0b00000001)
		{
			one();
		}
		else if (x==0b00000000)
		{
			zero();
		}
	}
	return 0 ;
}

