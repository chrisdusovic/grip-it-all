#include <avr/io.h>

#define PIN_SET(PORT, PIN) PORT |= 1 << PIN
#define PIN_CLEAR(PORT, PIN) PORT &= ~(1 << PIN)

int main(void)
{
}
