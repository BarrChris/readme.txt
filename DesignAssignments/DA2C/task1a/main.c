/*
 * task1a
 *
 * Created: 3/22/2019 10:13:32 PM
 * Author : Chris Barr
 */ 

#include <avr/io.h>
#include <stdio.h>

int main(void)
{
	DDRB |= (1<<5) | (1<<2); //Sets PB5/PB2 as outputs
	PORTB |= (1<<5) | (1<<2); //Clears PB5/PB2
	TCCR0B = 5; //Set prescaler to 1024
	int x=0;
	
	while(1) //infinite loop to keep the LED's to blink
	{
		TCNT0 = 0; //Reset counter
		x = 0;
		while (x <= 32) //TCNT to 4530
			{
			while(TCNT0 != 137){}
			TCNT0 = 0;
			x++;
			} //Delay to keep LED off
		PORTB ^= (1<<2); //LED turns on
		TCNT0 = 0; //Reset counter
		x = 0;
		while (x <= 32) //TCNT to 6796
			{
			while(TCNT0 != 206){}
			TCNT0 = 0;
			x++;
			} //Delay to keep LED on
		PORTB ^= (1<<2); //LED turns off
	}
	
	return 0;
}