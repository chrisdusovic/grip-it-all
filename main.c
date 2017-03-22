#include <avr/io.h>

#define PIN_SET(PORT, PIN) PORT |= 1 << PIN
#define PIN_CLEAR(PORT, PIN) PORT &= ~(1 << PIN)

// flex sensor --> PC0

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
}
