//============================================================================
// Project     : RoboCard
// File        : adc.h
// Author      : Leon Bonde Larsen
// Version     : 2.0
// Copyright   : Open Source
// Format      : Ansi-style C
// Description : This module implements settings and functions for analog to
//               digital conversion on the RoboCard.
//============================================================================
#ifndef RC_ADC
#define RC_ADC

//=====   INCLUDES   =====
#include <avr/io.h>

//=====   ADC SETTINGS   =====
//#define USE_INTERRUPT
#define TEN_BIT_MODE
//#define EIGHT_BIT_MODE

//=====   FUNCTION DECLARATIONS   =====
void init_adc (void);
void start_adc();
unsigned long get_adc();
void set_adc_channel(unsigned int ch);

#endif  //RC_ADC
//End of file
