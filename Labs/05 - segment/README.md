# Lab 5: Tadeáš Bařina


   [https://github.com/...](https://github.com/Tadeas155/Digital-electronics2)


### 7-segment library

1. In your words, describe the difference between Common Cathode and Common Anode 7-segment display.
   * CC SSD common cathode has all the cathodes of the 7-segments connected directly together. For the use of this seven segment the common cathode connection must be grounded and power must be applied to appropriate segment in order to illuminate that segment.
   * CA SSD common anode has all the anodes of the 7-segments connected together. Applying a ground to a particular segment connection (a-g), the appropriate segment will light up.

2. Code listing with syntax highlighting of two interrupt service routines (`TIMER0_OVF_vect`, `TIMER0_OVF_vect`) from counter application with at least two digits, ie. values from 00 to 59:


```c
/**********************************************************************
 * Function: Timer/Counter1 overflow interrupt
 * Purpose:  Increment counter value from 00 to 59.
 **********************************************************************/
ISR(TIMER1_OVF_vect)
{
	cnt0++;
	
	if(cnt0 > 9)
	{
		cnt0 = 0;
		cnt1++;
		if(cnt1 > 5)
		{
			cnt1 = 0;
		}
	 }

}
```

```c
/**********************************************************************
 * Function: Timer/Counter0 overflow interrupt
 * Purpose:  Display tens and units of a counter at SSD.
 **********************************************************************/
ISR(TIMER0_OVF_vect)
{
    static uint8_t pos = 0;
	
    if(pos == 0)
	{
        SEG_update_shift_regs(cnt0, pos);
        pos = 1;
    }
    else
	{
        SEG_update_shift_regs(cnt1, pos);
        pos = 0;
    }

}
```

3. Flowchart figure for function `SEG_clk_2us()` which generates one clock period on `SEG_CLK` pin with a duration of 2&nbsp;us. The image can be drawn on a computer or by hand. Use clear descriptions of the individual steps of the algorithms.

   
   | **Digit** | **A** | **B** | **C** | **D** | **E** | **F** | **G** | **DP** |
   | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
   | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 1 |
   | 1 | 1 | 0 | 0 | 1 | 1 | 1 | 1 | 0 |
   | 2 | 0 | 0 | 1 | 0 | 0 | 1 | 0 | 0 |
   | 3 | 0 | 0 | 0 | 0 | 1 | 1 | 0 | 0 |
   | 4 | 1 | 0 | 0 | 1 | 1 | 0 | 0 | 0 |
   | 5 | 0 | 1 | 0 | 0 | 1 | 0 | 0 | 0 |
   | 6 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 1 |
   | 7 | 0 | 0 | 0 | 1 | 1 | 1 | 1 | 0 |
   | 8 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
   | 9 | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 1 |


### Kitchen alarm

Consider a kitchen alarm with a 7-segment display, one LED and three push buttons: start, +1 minute, -1 minute. Use the +1/-1 minute buttons to increment/decrement the timer value. After pressing the Start button, the countdown starts. The countdown value is shown on the display in the form of mm.ss (minutes.seconds). At the end of the countdown, the LED will start blinking.

1. Scheme of kitchen alarm; do not forget the supply voltage. The image can be drawn on a computer or by hand. Always name all components and their values.

   ![your figure]()
