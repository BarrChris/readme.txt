/*
 * DA2A(part1_ccode).c
 *
 * Created: 3/4/2019 6:25:28 PM
 * Author : barrc1
 */ 

#include <avr/io.h>
#include <stdio.h>

int main(void)
{
	DDRB = (1<<2); //Sets PB2 as an output
	TCCR1B = 5; //Set prescaler to 1024
	
	while(1) //infinite loop to keep the LED's to blink
	{
		TCNT1 = 0; //Reset counter
		while (TCNT1 != 4530){} //Delay to keep LED off
		PORTB ^= (1<<2); //LED turns on
		TCNT1 = 0; //Reset counter
		while (TCNT1 != 6796){} //Delay to keep LED on
		PORTB ^= (1<<2); //LED turns off
	}
	
	return 0;
}