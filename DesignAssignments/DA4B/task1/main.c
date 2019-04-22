/*
 * DA4B.c
 *
 * Created: 4/20/2019 3:36:08 PM
 * Author : Chris
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

volatile unsigned int ADCVal;			 // Holds ADC Register value

int main(void)
{
	int period;
	timer_init();
	ADC_init();
	
	while(1)
	{
		ADCSRA |= (1 << ADSC);			// Starts conversion
		while((ADCSRA&(1<<ADIF))==0);	// Waits for conversion
		ADCVal = ADC & 0x03FF;			// Takes right 10-bits of ADC register
		OCR1A = 10*ADCVal;				// OCR1A value for duty cycle

		PORTB = 0x09;					// Forward the step
		while(!(TIFR1 & (1<<OCF1A)));   // Delays using CTC
		TIFR1 |= (1 << OCF1A);			// Resets flag, now it repeats 3 times
		PORTB = 0x03;
		while(!(TIFR1 & (1<<OCF1A)));
		TIFR1 |= (1 << OCF1A);	
		PORTB = 0x06;
		while(!(TIFR1 & (1<<OCF1A)));
		TIFR1 |= (1 << OCF1A);	
		PORTB = 0x0C;
		while(!(TIFR1 & (1<<OCF1A)));
		TIFR1 |= (1 << OCF1A);	
	}
}

void timer_init(void)
{
	//Port directions
	DDRB = 0x0F;							// Set PORTB3:0 as outputs
	DDRC = 0;								// PORTC as input
	PORTB = 0;								// Initially turns off all PB5:0
	
	//Timer1
	//TCCR1A = (1 << COM1A1);
	TCCR1B = (1 << WGM12) | (1 << CS11);	// Prescaler = 8
}

void ADC_init (void)
{
	// ADC initialization
	DIDR0 = 0x1;							// disable digital input on ADC0 pin
	ADMUX = (1<<REFS0);						// Reference = Aref, ADC0 (PC.0) used as analog input
	
	// right-justified data
	ADCSRA |= (1<<ADEN) | (1<<ADPS2) |
	(1<<ADPS1) | (1<<ADPS0);				// enable ADC, system clock used for ADC
	ADCSRB = 0x0;							// free running mode
}