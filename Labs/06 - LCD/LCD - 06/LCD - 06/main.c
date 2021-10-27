/***********************************************************************
 * 
 * Stopwatch with LCD display output.
 * ATmega328P (Arduino Uno), 16 MHz, AVR 8-bit Toolchain 3.6.2
 *
 * Copyright (c) 2017-Present Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 * 
 **********************************************************************/

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC
#include "lcd.h"            // Peter Fleury s LCD library
#include <stdlib.h>         // C library. Needed for conversion function



uint8_t customChar[16] = {
    0b11011,
    0b10101,
    0b10101,
    0b01010,
    0b01010,
    0b10101,
    0b10101,
    0b11011,
    0b11011,
    0b10101,
    0b10101,
    0b01010,
    0b01010,
    0b10101,
    0b10101,
    0b11011,
};






int main(void)
{
    // Initialize LCD display
    lcd_init(LCD_DISP_ON);
    
    // Set pointer to beginning of CGRAM memory
    lcd_command(1 << LCD_CGRAM);
    for (uint8_t i = 0; i < 16; i++)
    {
        // Store all new chars to memory line by line
        lcd_data(customChar[i]);
    }
    // Set DDRAM address
    lcd_command(1 << LCD_DDRAM);
    
    // Display first custom character
    lcd_putc(0);
    lcd_gotoxy(12, 0);
    lcd_putc(0x01);

       
       
       
    // Put string(s) at LCD display
    lcd_gotoxy(1, 0);
    lcd_puts("00:00.0   a");
    lcd_gotoxy(1, 1);
    lcd_puts("b         c");    
    //    lcd_putc('!');

    // Configure 8-bit Timer/Counter2 for Stopwatch
    // Set the overflow prescaler to 16 ms and enable interrupt
    TIM2_overflow_16ms();
    TIM2_overflow_interrupt_enable();

    // Enables interrupts by setting the global interrupt mask
    sei();

    // Infinite loop
    while (1)
    {
        /* Empty loop. All subsequent operations are performed exclusively 
         * inside interrupt service routines ISRs */
    }

    // Will never reach this
    return 0;
}

/* Interrupt service routines ----------------------------------------*/
/**********************************************************************
 * Function: Timer/Counter2 overflow interrupt
 * Purpose:  Update the stopwatch on LCD display every sixth overflow,
 *           i e approximately every 100 ms (6 x 16 ms = 100 ms).
 **********************************************************************/
ISR(TIMER2_OVF_vect)
{
    
    static uint8_t number_of_overflows = 0;
    static uint8_t desetiny = 0;        // Tenths of a second
    static uint8_t sek = 0;        // Seconds
    static uint8_t minut = 0;        // Seconds
    static uint16_t squa = 0;
    char lcd_string[2] = "  ";      // String for converting numbers by itoa()

    number_of_overflows++;
    if (number_of_overflows >= 6)
    {
        // Do this every 6 x 16 ms = 100 ms
        number_of_overflows = 0;

        // WRITE YOUR CODE HERE
        desetiny++;
        if (desetiny >= 10)
        {
            desetiny = 0;
            sek++;
            squa = sek * sek;
//            itoa(squa, lcd_string, 100);
//            lcd_gotoxy(11,0);
//            lcd_puts(squa);
            if (sek >= 60)
            {
                sek = 0;
                lcd_gotoxy(4, 0);
                lcd_puts("00");
                minut++;
                if (minut >= 60)
                {
                    minut = 0;
                    lcd_gotoxy(1, 0);
                    lcd_puts("00");
                    
                }
            }
        }
        itoa(desetiny, lcd_string, 10);     // Convert decimal value to string
        lcd_gotoxy(7, 0);
        lcd_puts(lcd_string);
        
        itoa(sek, lcd_string, 10);
        if (sek < 10) {
            lcd_gotoxy(5, 0);
            } else {
            lcd_gotoxy(4, 0);
        }
        lcd_puts(lcd_string);

        itoa(minut, lcd_string, 10);
        if (minut < 10) {
            lcd_gotoxy(2, 0);
            } else {
            lcd_gotoxy(1, 0);
        }
        lcd_puts(lcd_string);
        

    }
}