//============================================================================
// Project     : RoboCard
// File        : RCOS.c
//============================================================================

//=====   HEADER FILE   =====
#include "hall.h"

void init_hall( void )
{
    //All ports as input (PC3, PC4, PC5 and PB4)
    DDRC &= ~( 1 << DDC5 ) | ( 1 << DDC3) | ( 1 << DDC4);
    DDRB &= ~( 1 << DDB4 );

    //enable external interrupts
    PCICR =     (1<<PCIE0) | (1<<PCIE1);

    //interrupt on rising edge
    EICRA = (  ( 1 << ISC11 ) | ( 1 << ISC10 ) |
    		   ( 1 << ISC01 ) | ( 1 << ISC00 ) );

    //left encoder enable int 4 (PB4)
    PCMSK0 =    (1<<PCINT4);

    //right encoder enable int 12 (PC4)
    PCMSK1 =    (1<<PCINT12);

    //enable global pull-up
    MCUCR &= ~( 1 << PUD );

    //pull-up on all ports
    PORTB |=  ( 1 << PB4 );
    PORTC |=  ( 1 << PC4 ) | ( 1 << PC3 ) | ( 1 << PC5 );



}
