/*
 * DA4B.c
 *
 * Created: 4/20/2019 3:36:08 PM
 * Author : Chris
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

void timer_init(void);
void ADC_init(void);

int main(void)
{
	timer_init();
	ADC_init();
	
	while(1)
	{
		ADC_init();
		ICR1 = 4999;											// fPWM = 50Hz
		DDRB |= (1<<PB1);										// Enables PB1 as output
		OCR1A = ADC;											// Grabs value from potentiometer to timer1
		_delay_ms(30);											// Delays from potentiometer to relay 
	}
}

void timer_init(void)
{
	//Timer1
	TCCR1A = (1 << COM1A1) | (1<<COM1B1) | (1<<WGM11);			// Non-inverting Mode, Fast PWM Mode
	TCCR1B = (1<<WGM13) | (1<<WGM12) | (1<<CS11) | (1<<CS10);	// Prescaler = 64
}

void ADC_init (void)
{
	// ADC initialization
	ADMUX = (1<<REFS0);											// Reference = Aref, ADC0 (PC.0) used as analog input
	
	// right-justified data
	ADCSRA |= (1<<ADEN) | (1 << ADSC) | (1<<ADPS2) | 
	(1<<ADPS1) | (1<<ADPS0);									// enable ADC, system clock used for ADC
	ADCSRB = 0x0;												// free running mode
}