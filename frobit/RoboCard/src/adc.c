/*============================================================================
// Name        : RC_adc.h
// Author      : Leon Bonde Larsen
// Version     : 1.0
// Copyright   : Open Source
// Description : Functions related to RoboCard A/D converter,C Ansi-style
//==========================================================================*/

/*=====   INCLUDES   =====*/
#include "adc.h"

/*=====   FUNCTION IMPLEMENTATIONS  =====*/
void init_adc (void)
{
	ADCSRA |=  (1<<ADEN);                 /*enable ADC conversion*/
	ADCSRA |= ((1<<ADPS2) |               /*prescale 128*/
	           (1<<ADPS1) |
	           (1<<ADPS0));
	ADMUX |= (1<<ADLAR);
#ifdef USE_INTERRUPT
	ADCSRA |=  (1<<ADIE);                 /*interrupt enable*/
#endif
}

void start_adc()
{
	/*request adc conversion*/
	ADCSRA |= (1<<ADSC);                 
}

unsigned long get_adc()
{
	/*wait if conversion is in progress*/
	while (  ADCSRA & ( 1 << ADSC ) );	
	
#ifdef EIGHT_BIT_MODE
	int data = ADCH;                     
	return data;
#endif
	
#ifdef TEN_BIT_MODE
	return ((ADCL) | ((ADCH)<<8));
#endif
}

void set_adc_channel(unsigned int ch)
{
	/*change channel if argument is within range*/
	if(ch<6)                             
		ADMUX = (1<<ADLAR) + ch;         
}


