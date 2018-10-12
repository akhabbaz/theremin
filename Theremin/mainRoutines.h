/*
 * mainRoutines.h
 *
 * Created: 9/29/2018 1:56:33 PM
 *  Author: akhabbaz
 */ 


#ifndef MAINROUTINES_H_
#define MAINROUTINES_H_

#include "setFreq.h"
#include "UART.h"
#include <util/delay.h>

void init0r2(void);
void main0r2(void);

void init0r3(void);
void main0r3(void);
void mainPlayTone(void);
void init0r3Timer0(void);

enum Tone {LOW= 0, MEDIUM, HIGH};

void playTone(enum Tone x);


#endif /* MAINROUTINES_H_ */
