/*
 * DA2A(part2_ccode).c
 *
 * Created: 3/4/2019 7:04:53 PM
 * Author : barrc1
 */ 

#include <avr/io.h>
#include <stdio.h>

int main(void)
{
	DDRB = (1<<2); //PB2 as an output
	PORTB = (1<<2); //Sets PB2
	DDRC = (0<<2); //PC2 as an input
	PORTC = (0<<2); //Sets PC2
	TCCR1B = 5; //Sets prescaler to 1024
	while (1) //loop forever to keep program running
	{
		if (!(PINC & (1 << PINC2))) //If the pushbutton is pressed, go through this if statement
		{
			PORTB &= ~(1<<2); //Keeps LED on until otherwise
			while (TCNT1 != 19530){} //Delay to keep LED off
			TCNT1 = 0; //Reset counter
		}
		else //else, if the pushbutton is not pressed, go through this else statement
		{
			PORTB |= (1<<2); //Keeps LED off until otherwise
			TCNT1 = 0; //Reset counter
		}
	}
	return 0;
}