#include <lpc21xx.h>
#include "buzzer.h"


void buzzer_init(void)
{
    IODIR0 |= BUZZER;
	IOCLR0=BUZZER;
}

void buzzer_on(void)
{
    IOSET0 = BUZZER;
}

void buzzer_off(void)
{
    IOCLR0 = BUZZER;
}

