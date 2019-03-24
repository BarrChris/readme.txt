/*
 * task3a.c
 *
 * Created: 3/23/2019 2:12:00 AM
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
	
	while(1) //infinite loop to keep the LED's to blink
	{
		//main loop
	}
	
	return 0;
}

ISR (TIMER0_COMPA_vect)
{
	int x = 0;
	TCNT0 = 0; //Reset counter
	x = 0;
	while (x <= 32) //TCNT to 4530
	{
		while(TCNT0 != 137){} // Delay for 0.29 seconds
		TCNT0 = 0; // Reset Counter
		x++; // Over flow counter
	} //Delay to keep LED off
	PORTB ^= (1<<2); //LED turns on
	TCNT0 = 0; //Reset counter
	x = 0;
	while (x <= 32) //TCNT to 6796
	{
		while(TCNT0 != 206){} // Delay for 0.435 seconds
		TCNT0 = 0; // Reset counter
		x++; // Over flow counter
	} //Delay to keep LED on
	PORTB ^= (1<<2); //LED turns off
}