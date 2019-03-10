/*
 * DA2B_CCODE.c
 *
 * Created: 3/9/2019 3:08:37 PM
 * Author : Chris
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int main(void)
{
	//Port Direction/Set-up
	DDRB |= (1<<5) | (1<<2); //Sets PB5/PB2 as outputs
	PORTB |= (1<<5) | (1<<2); //Clears PB5/PB2
	PORTD = 1<<2; //Enables PD2
	
	//Interrupts
	EICRA = 0x02;
	EIMSK = 1<<INT0; //Enable PC set 0 interrupt
	sei(); //Enables global interrupt
	
	while (1);
}

ISR(INT0_vect)
{
	PORTB ^= (1<<2); //Toggle PB2 when interrupt
	_delay_ms(1250); //Delays for 1.25 seconds
}
