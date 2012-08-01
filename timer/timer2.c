//============================================================================
// Project     : RoboCard
// File        : timer2.c
//============================================================================

//=====   HEADERFILE   =====
#include "timer2.h"

//=====   INITIALIZATION   =====
uint16_t init_fast_pwm2( int outputpin )
{
	//set prescaler
    TCCR2B &= ~( 7 << CS00 );
    TCCR2B |= (_PS_2 << CS00 );

    //fast PWM
    TCCR2A |= ( 1 << WGM21 ) | ( 1 << WGM20 );

    switch(outputpin)
    {
    case OC2A:
    	//output on PD6
    	DDRB |= ( 1 << PB3 );
        TCCR2A |= ( 1 << COM2A1 );

        //return pointer to duty register
        return (uint16_t)&OCR2A;

    case OC2B:
    	//output on PD6
    	DDRD |= ( 1 << PD3 );
        TCCR2A |= (1<<COM2B1);

        //return pointer to duty register
        return (uint16_t)&OCR2B;

    default:
    	return 0;
    }
}

