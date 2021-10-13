 #include <avr/io.h>
 #include <util/delay.h>

 #define datapin PORTB
 #define commandpin PORTD
 #define rs PD0
 #define rw PD1
 #define en PD2

 void lcd_cmd(unsigned char com);     //command function
 void lcd_data(unsigned char data);   //data function
 void lcd_string (unsigned char *str);  //string function that will take addresses of the char array



 int main(void)
 {
	 DDRB = 0xff;    //data pins configure as output pin
	 DDRD = 0xff;	//command pins configure as output pin
	 
	 lcd_cmd(0x02);  //home location
	 lcd_cmd(0x38);  //2x16 lcd 4bit mode
	 lcd_cmd(0x0C);  //display on cursor blink
	 lcd_cmd(0x06);   //increment
	 lcd_cmd(0x01);	//for clearing screen
	 
	 unsigned int A1 = 0; //Variable to hold ADC Result (in this ,for binary code of adc value will come and after storing in this variable it will converted into integer type)
	 char x[7];		//Array to hold ADC value in string form (for eg. 124 is the ADC value in variable A1 so '1' '2' '4' will be converted into char and then store into the array)
	 
	 
	 
	  /*Initializations*/
	  ADCSRA = (1<<ADEN)/*To enable ADC*/ | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0) /*To set pre-scaler at 128KHz so we have given 111*/ ;
	  // Basically '|' is used so that previous values that have been given before does not lose.
	  ADMUX = (1<<REFS0);     //AVcc is used as Reference Voltage
	  
	  
	  
	 while (1)
	 {
		 int ADCvalue , Ahigh , Alow; //these variable will store ADC value .. as ADC has 10 bit resolution so there are 2 registers ADCH and ADCL to store ADC value.........as I am not giving giving 1 in ADLAR in ADCSRA register ,so  default value of ADLAR bit is 0 so that means ADCL register will store 8 bit data and remaining 2 bit data will be stored in ADCH register    
		 int channel=1;    //Select PA1 for ADC work(PA0---> 0, PA2---> 2.....).... you can select any Channel but remeber one thing that microcontroller can do ADC only 1 channel at a time.
		 ADMUX |= channel;	  //so basically it will convert 1 into binary and then assign in the ADMUX register. 	
		 ADCSRA |= (1<<ADSC);   // after declaring all important things to the ADC's Register its time to start conversion
		 while (ADCSRA & (1<<ADSC))  // Basically this is the loop only for checking whether the conversion have been finised or not...there is also another methord ADIF that can be used to check it..
		 {
		 }
		 
		 /*ADIF methord (ADIF-Analog Digital Inturrupt flag) (1--> conversion complete , 0 --> conversion in process)*/
		 /*while(! (ADCSRA & (1<<ADIF))
		 {}
		 */
		 
		 
		 Alow= (int)ADCL;
		 Ahigh=(int)ADCH*256;
		 
		 ADCvalue=Ahigh+Alow ;   // Assigning the ADC value after conversion into the variable that we have initialized 
		 
		 // Now we will use a function itoa(integer to array)..... now we will convert that adc value into string so that we can display it on LCD
		 //itoa function takes 3 arguments 1. integer  2. array name   3. integer base i.e if 10 it will convert integer into decimal and then store it in the array...2 for binary.....16 for hex etc.
		 itoa(ADCvalue , x ,10 );
		 lcd_cmd(0x80);      //for first row
		 lcd_string("ADC value");
		 lcd_cmd(0xc0);    //for second row
		 lcd_string(x);
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
	 _delay_ms(10);
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