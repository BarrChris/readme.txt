/*
 * DA4A.c
 *
 * Created: 4/12/2019 11:58:51 AM
 * Author : Chris
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile unsigned int ADCVal;				// Holds ADC Register value
char motor = 0;								// Holds the state of the motor (ON/OFF)

void timer_init (void);						// Function declaration for timer
void ADC_init (void);						// Function declaration for ADC

int main(void){
	
	timer_init();							// Initializes timer
	ADC_init();								// Initializes ADC
	
	while (1)
	{
		// main loop
		PORTB = (1 << PB5);					// Keeps that annoying LED on shield turned off
	}
}

ISR(PCINT1_vect)
{
	if(!(PINC & (1 << PINC1)))				//BUTTON HAS BEEN PRESSED
	{
		_delay_ms(50);						// Debounces button
		while(!(PINC & (1 << PINC1)));		// Checks if button was pressed
		
		if(motor)							//START MOTOR
		{
			PORTB |= (1 << PORTB1);			// Turns on motor
			ADCSRA |= (1 << ADSC);			// Starts conversion
			while((ADCSRA&(1<<ADIF))==0);	// Waits for conversion
			ADCVal = ADC & 0x03FF;			// Takes right 10-bits of ADC register
			OCR1A = 10*ADCVal;				// OCR1A value for duty cycle
		}
		
		else if(!motor)						//STOP MOTOR
		{
			OCR1A = 0;						// Reset register
			PORTB &= ~(1 << PORTB1);		// Turns off motor
		}
		
		motor ^= 1;							// Remembers state of button
	}
}

void timer_init(void)
{
	//Port directions
	DDRB = (1<<1);							// PB.1-2 (OC1A & OC1B) as output to generate PWM
	DDRB |= (1<<5);							// PB.1-2 (OC1A & OC1B) as output to generate PWM
	DDRC = 0;								// PORTC as input
	PORTB = 0;								// Initially turns off all PB5:0
	
	//Timer1
	TCCR1A |= (1 << COM1A1) | (1 << COM1B1) | 
			  (1 << WGM11);					// enable PWM for OC1A & OC1B, Fast PWM, Non-inverted mode
	TCCR1B |= (1 << WGM13) | (1 << WGM12) | 
		      (1 << CS11);					// Prescaler = 8
	ICR1 = 9999;							// Timer1 TOP
	
	//Interrupt Settings
	PORTC |= (1 << PORTC1);					  
	PCICR = (1 << PCIE1);					 
	PCMSK1 = (1 << PCINT9);					 
	sei();									// Enable global interrupts
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