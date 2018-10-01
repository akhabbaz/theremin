/*
 * mainRoutines.c
 *
 * Created: 9/29/2018 2:00:33 PM
 *  Author: akhabbaz
 */ 
#include "mainRoutines.h"
#include <avr/interrupt.h>
volatile uint8_t tot_overflow0r3;
uint8_t    numberInterrupts0r3 = 2;
uint8_t    counts0r3 = 111;
void init0r2(void)
{
	DDRB = (1 << DDB5); // set pin to output #5
	PORTB = (1 << PORTB0); // pull pin to high impedance
}
void init0r3(void)
{
	DDRD = (1 << DDD6); // set pin to output #6
	PORTD &= 0x8F; //set Pin6 to ground to start
	tot_overflow0r3 = 0;
}
void init0r3Timer0(void)
{
        TCCR0B |= (1 << CS01) | (1 << CS00);// set prescalar to 64
	TCNT0 = 0; // initialize counter to 0;
	TIMSK0 |= (1 << TOIE0); // enable overflow interrupt 
	sei(); // enable interrupts
}
ISR(TIMER0_OVF_vect)
{
	tot_overflow0r3++;	
}
// polling solution
void main0r2(void)
{
	while( 1)
	{
		uint8_t buttonpressed = !(PINB & ( 1 << PINB0)); 
	    	if ( buttonpressed) {
	   		PORTB  |= (1 << PORTB5);
	   	}
	   	else {
	      		PORTB &= 0xDF;
	   	}
	}
}
void main0r3(void)
{
	while( 1)
	{
		if (tot_overflow0r3 >= numberInterrupts0r3 &&  TCNT0 >= counts0r3) {
				PORTD ^= (1 << PORTD6);
				TCNT0 = 0;
				tot_overflow0r3 = 0;
		}
	}
}
