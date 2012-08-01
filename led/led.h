//============================================================================
// Project     : RoboCard
// File        : led.h
// Author      : Leon Bonde Larsen
// Version     : 2.0
// Copyright   : Open Source
// Format      : Ansi-style C
// Description : This module implements the onboard
//============================================================================
// Usage       :
//					#define LED_PORT	B
//					#define LED_PIN 	0
//
//					init_led();
//
//					led( 1 );
//
//					toggle_led();
//============================================================================
#ifndef RC_LED
#define RC_LED

#include <avr/io.h>

//=====   MACROS   =====
#ifndef LED_PORT                                    //default to onboard led
#warning "LED_PORT was not defined. Defaults to B"
#define   LED_PORT       B
#endif

#ifndef   LED_PIN
#warning "LED_PIN was not defined. Defaults to 0"
#define   LED_PIN        0
#endif

#if       LED_PORT ==    B
#define   LED_PORT_REG   PORTB
#define   LED_DDR        DDRB
#elif     LED_PORT ==    C
#define   LED_PORT_REG   PORTC
#define   LED_DDR        DDRC
#elif     LED_PORT ==    D
#define   LED_PORT_REG   PORTD
#define   LED_DDR        DDRD
#endif

//======   LED   =====

//init LED
void init_led(void);

//set LED state
void led(char on);

//toggle LED
void toggle_led(void);

#endif  // RC_LED
//End of file
