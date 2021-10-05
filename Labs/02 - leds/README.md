# Lab 2: Tadeáš Bařina

   (https://github.com/Tadeas155/Digital-electronics2)

#### Active-low and active-high LEDs

1. Complete tables according to the AVR manual.

| **DDRB** | **Description** |
| :-: | :-- |
| 0 | Input pin |
| 1 | Output pin |

| **PORTB** | **Description** |
| :-: | :-- |
| 0 | Output low value |
| 1 | Output high value |

| **DDRB** | **PORTB** | **Direction** | **Internal pull-up resistor** | **Description** |
| :-: | :-: | :-: | :-: | :-- |
| 0 | 0 | input | no | Tri-state, high-impedance |
| 0 | 1 | input | yes | Pxn will source current if ext. pulled low |
| 1 | 0 | output |no | Output Low (Sink) |
| 1 | 1 | output | no | Output High (Source) |

2. Part of the C code listing with syntax highlighting, which blinks alternately with a pair of LEDs; let one LED is connected to port B and the other to port C:

```c
int main(void)
{
	// Green LED at port B
	// Set pin as output in Data Direction Register...
	DDRB = DDRB |    (1<<LED_GREEN);
	// ...and turn LED off in Data Register
	PORTB = PORTB & ~(1<<LED_GREEN);
	// Configure the second LED at port C
	// Set pin as output in Data Direction Register...
	DDRC = DDRC |    (1<<LED_BLUE);
	// ...and turn LED off in Data Register
	PORTC = PORTC & ~(1<<LED_BLUE);

	// Infinite loop
	while (1)
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

	// Will never reach this
	return 0;
}
```


### Push button

```c
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
```
