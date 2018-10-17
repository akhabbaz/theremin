/*
 * mainRoutines.c
 *
 * Created: 9/29/2018 2:00:33 PM
 *  Author: akhabbaz
 */ 
#include "mainRoutines.h"
#include <avr/interrupt.h>
#include <stdio.h>
#include "UART.h"
volatile uint8_t tot_overflow0r3;
uint8_t    numberInterrupts0r3 = 1;
uint8_t    counts0r3 = 111;
uint16_t TimeOnCompare_HIGH= 500;
uint16_t NumberPulses_HIGH = 500;
uint16_t TimeOnCompare_MEDIUM= 1000;
uint16_t NumberPulses_MEDIUM = 200;
uint16_t TimeOnCompare_LOW= 7000;
uint16_t NumberPulses_LOW = 50;
volatile uint16_t TimeOnCompare= 70;
volatile uint16_t NumberPulses = 20;
volatile char HiOrLo = 0;
volatile int pccnt = 0;
void chooseTimer(enum Tone x)
{
	switch (x){
	case HIGH:
		TimeOnCompare   = TimeOnCompare_HIGH;
		NumberPulses    = NumberPulses_HIGH;
		break;
	case MEDIUM:
		TimeOnCompare   = TimeOnCompare_MEDIUM;
		NumberPulses    = NumberPulses_MEDIUM;
		break;
	case LOW:
		TimeOnCompare   = TimeOnCompare_LOW;
		NumberPulses    = NumberPulses_LOW;
		break;
	}
}
ISR(TIMER1_COMPA_vect){
	OCR1A += TimeOnCompare;
	// HiOrLo ^= 1; for debugging
	//PORTB ^= (1 <<PORTB1);
	pccnt--;
	if (pccnt == 0){
		TIMSK1 = 0;
		PORTB &=~(1 <<PORTB1);
		//TCCR1A = 0;
	}
}
void initToneGenerator()
{
	DDRB |= (1 << DDB1); // set port 2 to output
	// may possible to now use OCR1A directly
	TCCR1A |= (1 << COM1A0); // toggle on compare match
	TCCR1B |= (1 << CS11); // prescalar to 256
	sei();
	printf("T %u, N %u \n ", TimeOnCompare, NumberPulses);
	printf("TCCR1A %x, TIMSK1 %x\n", TCCR1A, TIMSK1); 
}
void resetToneGenerator()
{
	OCR1A = TCNT1 + 16;  //pull HIGH quickly
	pccnt = 2 * NumberPulses -1;
	OCR1A += TimeOnCompare;
	TIMSK1 |= (1 << OCIE1A); //enable interrupt on OCR1A
	//sei();
	printf("resetTone \n");
}
void playTone(enum Tone x)
{
	
	chooseTimer(x);
	resetToneGenerator();	
};
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
void mainPlayTone(void)
{
	 initToneGenerator(); // do this once
	
	 while(1)
	 {
		 //_delay_ms(0);
		 //printf("HL %u, Pls %u\n", HiOrLo, pccnt);
		  playTone(MEDIUM);
		  _delay_ms(1000);
		  playTone(HIGH);
		  _delay_ms(2000);
		  playTone(LOW);
		  _delay_ms(3000);
		 
	 }
}