/*
 * task2a.c
 *
 * Created: 3/23/2019 1:13:59 AM
 * Author : Chris Barr
 */ 

#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdio.h>

int main(void)
{
	DDRB |= (1<<5) | (1<<2); //Sets PB5/PB2 as outputs
	PORTB |= (1<<5) | (1<<2); //Clears PB5/PB2
	TIMSK0 |= (1 << TOIE0);
	sei();
	//enables interrupt
	TCCR0B = 5; //Set prescaler to 1024
	
	while(1) //infinite loop to keep the LED's to blink
	{

	}
	
	return 0;
}

ISR (TIMER0_OVF_vect)
{
	int x = 0;
	TCNT0 = 0; //Reset counter
	x = 0;
	while (x <= 32) //TCNT to 4530 with overflow 32 times
	{
		while(TCNT0 != 137){} 
		TCNT0 = 0; //Reset counter
		x++; // Increment Over Flow Counter
	} //Delay to keep LED off
	PORTB ^= (1<<2); //LED turns on
	TCNT0 = 0; //Reset counter
	x = 0;
	while (x <= 32) //TCNT to 6796 with overflow 32 times
	{
		while(TCNT0 != 206){}
		TCNT0 = 0; //Reset counter
		x++; // Increment Over Flow Counter
	} //Delay to keep LED on
	PORTB ^= (1<<2); //LED turns off
}