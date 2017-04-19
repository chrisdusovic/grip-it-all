// flex sensor --> PC0
// servo --> PB1
// force LED red --> PD6
// force LED green -> PD5
// status LED --> PB0
// lock switch --> PD2

#include <avr/io.h>
#include <util/delay.h>

#define PIN_SET(PORT, PIN) PORT |= 1 << PIN
#define PIN_CLEAR(PORT, PIN) PORT &= ~(1 << PIN)

// Re-maps a number from one range to another
inline int map(int x, int in_min, int in_max, int out_min, int out_max);

int main(void)
{
	// Set up flex sensor.
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1);
	ADMUX |= (1 << REFS0);
	ADMUX |= 0;
	ADCSRA |= (1 << ADATE);
	ADMUX |= (1 << ADLAR);
	ADCSRA |= (1 << ADEN);
	ADCSRA |= (1 << ADSC);

	// Set up servo.
	DDRB |= (1 << DDB1);
	TCCR1A |= (1 << WGM11) | (1 << COM1A1);
	TCCR1B |= (1 << WGM13) | (1 << WGM12) | (1 << CS11);
	ICR1 = 19999;

	// Set up force indicator LED.
	DDRD |= (1 << DDD6) | (1 << DDD5);
	TCCR0A |= (1 << COM0A1) | (1 << COM0B1) | (1 << WGM01) | (1 << WGM00);
	TCCR0B |= (1 << CS00);

	// Set up status LED.
	DDRB |= (1 << DDB0);

	// Set up lock switch.
	DDRD &= ~(1 << PD2);

	// Enable status LED.
	PIN_SET(PORTB, PORTB0);

	while (1)
	{
		// Operation is dependent on lock switch position.
		if (PIND & (1<<PD2))
		{
			// Set servo position based on flex sensor reading.
			OCR1A = map(ADCH, 150, 200, 1075, 1700);
		}
		_delay_ms(10);
	}
}


inline int map(int x, int in_min, int in_max, int out_min, int out_max)
{
	return floor((x - in_min) * ((float) out_max - out_min) / (in_max - in_min) + out_min);
}
