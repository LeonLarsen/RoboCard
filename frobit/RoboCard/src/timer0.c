/*============================================================================
// Project     : RoboCard
// File        : timer0.c
//==========================================================================*/

/*=====   HEADERFILE   =====*/
#include "timer0.h"

/*=====   INITIALIZATION   =====*/
uint16_t init_fast_pwm0( int outputpin )
{
	/*set prescaler*/
    TCCR0B &= ~( 7 << CS00 );
    TCCR0B |= (_PS_0 << CS00 );

    /*fast PWM*/
    TCCR0A |= ( 1 << WGM01 ) | ( 1 << WGM00 );

    switch(outputpin)
    {
    case OC0A:
    	/*output on PD6*/
        DDRD |= ( 1 << PD6 );
        TCCR0A |= ( 1 << COM0A1 );

        /*return pointer to duty register*/
        return (uint16_t)&OCR0A;

    case OC0B:
    	/*output on PD6*/
        DDRD |= (1<<PD5);
        TCCR0A |= (1<<COM0B1);

        /*return pointer to duty register*/
        return (uint16_t)&OCR0B;

    default:
    	return 0;
    }
}
