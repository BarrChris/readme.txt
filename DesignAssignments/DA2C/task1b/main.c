/*
 * task1b.c
 *
 * Created: 3/23/2019 12:17:12 AM
 * Author : Chris Barr
 */ 

#include <avr/io.h>
#include <stdio.h>

int main(void)
{
	DDRB |= (1<<5) | (1<<2); //Sets PB5/PB2 as outputs
	PORTB |= (1<<5) | (1<<2); //Clears PB5/PB2
	DDRC = (0<<2); //PC2 as an input
	PORTC = (0<<2); //Sets PC2
	TCCR0B = 5; //Sets prescaler to 1024
	int x = 0;
	while (1) //loop forever to keep program running
	{
		if (!(PINC & (1 << PINC2))) //If the pushbutton is pressed, go through this if statement
		{
			PORTB &= ~(1<<2); //Keeps LED on until otherwise
			while (x <= 76/*TCNT0 != 19530*/) //Delay to keep LED on
			{
				while (TCNT0 != 253);
				TCNT0 = 0;
				x++;
			}
			while(TCNT0 != 51);
			TCNT0 = 0; //Reset counter
			x = 0;
		}
		else //else, if the pushbutton is not pressed, go through this else statement
		{
			PORTB |= (1<<2); //Keeps LED off until otherwise
			TCNT0 = 0; //Reset counter
		}
	}
	return 0;
}