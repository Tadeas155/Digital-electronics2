/***********************************************************************
 * 
 * Alternately toggle two LEDs when a push button is pressed.
 * ATmega328P (Arduino Uno), 16 MHz, AVR 8-bit Toolchain 3.6.2
 *
 * Copyright (c) 2018-Present Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 * 
 **********************************************************************/

/* Defines -----------------------------------------------------------*/
#define LED_GREEN   PB4     // AVR pin where green LED is connected
#define LED_BLUE    PB3
#define BLINK_DELAY 250
#define PUSH_BUTTON PD1
#define LED_TWO     PC1
#define BUTTON      PD0
#ifndef F_CPU
#define F_CPU 16000000     // CPU frequency in Hz required for delay
#endif

/* Includes ----------------------------------------------------------*/
#include <util/delay.h>     // Functions for busy-wait delay loops
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/sfr_defs.h>

/* Functions ---------------------------------------------------------*/
/**********************************************************************
 * Function: Main function where the program execution begins
 * Purpose:  Toggle two LEDs when a push button is pressed.
 * Returns:  none
 **********************************************************************/

int main(void)
{
	DDRB  = DDRB  |   (1<<LED_GREEN);
	PORTB = PORTB & ~ (1<<LED_GREEN);
	DDRC  = DDRC  |   (1<<LED_BLUE);
	PORTC = PORTC & ~ (1<<LED_BLUE);
	DDRD  = DDRD  & ~ (1<<PUSH_BUTTON);
	PORTD = PORTD & ~ (1<<PUSH_BUTTON);

	// Infinite loop
	while (1)
	{
		if (PIND & (1<<PUSH_BUTTON) == 1)
		{
			PORTB = PORTB |  (1<<LED_GREEN);
			// Pause several milliseconds
			_delay_ms(BLINK_DELAY);
			PORTB = PORTB & ~(1<<LED_GREEN);
			// Pause several milliseconds
			_delay_ms(BLINK_DELAY);
			PORTC = PORTC |  (1<<LED_BLUE);
			// Pause several milliseconds
			_delay_ms(BLINK_DELAY);
			PORTC = PORTC & ~(1<<LED_BLUE);
			// Pause several milliseconds
			_delay_ms(BLINK_DELAY);
		}
	}

	// Will never reach this
	return 0;
}
