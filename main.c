// flex sensor --> PC0
// servo --> PB1
// force LED red --> PD6
// force LED green -> PD5
// status LED --> PB0
// lock switch --> PD2

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

	// Set up force indicator LED.
	DDRD |= (1 << DDD6) | (1 << DDD5);
	TCCR0A |= (1 << COM0A1) | (1 << COM0B1) | (1 << WGM01) | (1 << WGM00);
	TCCR0B |= (1 << CS00);

	// Set up status LED.
	DDRB |= (1 << DDB0);

	// Set up lock switch.
	DDRD &= ~(1 << PD2);
}
