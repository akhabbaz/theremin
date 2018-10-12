/*
 * Theremin.c
 *
 * Created: 9/29/2018 1:25:35 PM
 * Author : akhabbaz
 */ 
#include "mainRoutines.h"

int main(void)
{
	uart_init();
	//init0r2();
	//main0r2();
	//init0r3();
	//init0r3Timer0();
	//main0r3();
	enum Tone thisTone;
	//playTone(thisTone = HIGH);
    /* Replace with your application code */
    mainPlayTone();

}

