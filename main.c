// flex sensor --> PC0
// servo --> PB1

#include <avr/io.h>

#define PIN_SET(PORT, PIN) PORT |= 1 << PIN
#define PIN_CLEAR(PORT, PIN) PORT &= ~(1 << PIN)

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
}
