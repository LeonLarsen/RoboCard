//============================================================================
// Project     : RoboCard
// File        : timer0.h
// Author      : Leon Bonde Larsen
// Version     : 2.0
// Copyright   : Open Source
// Format      : Ansi-style C
// Description : This module implements pwm on timer0
//============================================================================
// Usage       :
//						char string[SIZE];
//						message_t msg;
//
//						str_to_msg( string , &msg );
//						msg_to_str( &msg , string );
//============================================================================
#ifndef _RC_timer0_
#define _RC_timer0_

//=====   INCLUDES   =====
#include "global.h"
#include <avr/io.h>

//=====   MACROS  =====
#ifndef     TIMER0_PRESCALER
#define     TIMER0_PRESCALER     0
#warning "No prescaler defined for timer0. Default to none."
#endif

//Timer 0
#if         TIMER0_PRESCALER ==  0
#define     _PS_0         1                 //frequency 62.5 kHz = period 16 µS
#elif       TIMER0_PRESCALER ==  8
#define     _PS_0         2                 //frequency 7.8 kHz = period 128 µS
#elif       TIMER0_PRESCALER ==  64
#define     _PS_0         3                 //frequency 976 Hz = period 1 mS
#elif       TIMER0_PRESCALER ==  256
#define     _PS_0         4                 //frequency 244 Hz = period 4 mS
#elif       TIMER0_PRESCALER ==  1024
#define     _PS_0         5                 //frequency 61 Hz = period 16 mS
#else
#define     _PS_0         1
#warning "Wrong prescaler defined for timer0. Default to none"
#endif

//datatype for pointer to register
#ifndef REGISTER
#define REGISTER(x) uint8_t(x)
#endif

//necessary cast from address (i.e. PORTB) to pointer
#ifndef ADDRESS
#define ADDRESS(x)    (uint8_t*)(x)
#endif

//macro to make pointing really easy
#define PWM0(x) ADDRESS(init_fast_pwm0(x))

//=====   ENUMERATIONS  =====
enum {OC0A,OC0B};

//=====   FUNCTION DECLARATIONS  =====
uint16_t init_fast_pwm0( int outputpin );

#endif  //_RC_timer0_

//End of file
