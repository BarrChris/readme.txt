/*
 * task3b.c
 *
 * Created: 3/23/2019 7:09:29 PM
 * Author : Chris Barr
 */ 

#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdio.h>

int main(void)
{
	DDRB |= (1<<5) | (1<<2); //Sets PB5/PB2 as outputs
	PORTB |= (1<<5) | (1<<2); //Clears PB5/PB2
	TCCR0B = 5; //Set prescaler to 1024
	TCCR0A = (1 << WGM01); //Set CTC Mode
	TIMSK0 = (1 << OCIE0A); //Set interrupt on compare match
	sei();
	OCR0A = 0xFF;

	while (1) //loop forever to keep program running
	{

	}
	return 0;
}

ISR (TIMER0_COMPA_vect)
{
	int x = 0; // Used to counter overflow through the 8 bit timer0
	if (!(PINC & (1 << PINC2))) //If the pushbutton is pressed, go through this if statement
	{
		PORTB &= ~(1<<2); //Keeps LED on until otherwise
		while (x <= 76/*TCNT0 != 19530*/) //Delay to keep LED off
		{
			while (TCNT0 != 253); // Delay for 1.25 seconds
			TCNT0 = 0; // Reset counter
			x++; // Over flow counter
		}
		while(TCNT0 != 51); // Additional delay
		TCNT0 = 0; //Reset counter
		x = 0;
	}
	else //else, if the pushbutton is not pressed, go through this else statement
	{
		PORTB |= (1<<2); //Keeps LED off until otherwise
		TCNT0 = 0; //Reset counter
	}
}
