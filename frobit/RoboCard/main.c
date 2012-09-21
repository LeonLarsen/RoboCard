/*============================================================================
// Project     : Frobit
// File        : main.c
// Author      : Leon Bonde Larsen
// Version     : 1.0
// Copyright   : Open Source
// Format      : Ansi-style C
// Description : This file implements the firmware for the Frobit robot
//				 http://wiki.fieldrobot.dk/index.php/FroboMind_Robot:Frobit
//============================================================================
// Pin configuration:
// PB0 - Onboard LED			PC0 - ADC 0					PD0 - rx
// PB1 - Left hall B			PC1 - ADC 1					PD1 - tx
// PB2 - Enable H-bridges		PC2 - ADC 2					PD2 - USB D+
// PB3 - OC2A Right reverse		PC3 - ADC 3					PD3 - OC2B Left reverse
// PB4 - INT4 Left hall A		PC4 - INT12 Right hall A	PD4 - USB D-
// PB5 - 						PC5 - Right hall B			PD5 - OC0B Right forward
// PB6 - X-tal					PC6 - Reset 				PD6 - OC0A Left forward
// PB7 - X-tal												PD7 - BL switch
//==========================================================================*/

/*=====   INCLUDES   =====*/
/*device definitions*/
#include "src/global.h"
#include <avr/io.h>

/*cli(), sei(), ISR()*/
#include <avr/interrupt.h>

/*modules*/
#include "src/frobit.h"

/*=====   GLOBAL VARIABLES   =====*/
unsigned char t20ms = 0;
signed int left_pos = 0, right_pos = 0;						/*number of ticks since start*/
signed int left_setpoint_velocity, right_setpoint_velocity;	/*desired speeds in ticks/100ms*/
signed int left_corrected_velocity, right_corrected_velocity;	/*corrected speeds in duty cycle (-255 to 255)*/

/*=====   INTERRUPT SERVICE ROUTINES   =====*/
ISR (USART_RX_vect)
{
	buffer( PUSH, UDR0 );
}

ISR (TIMER1_COMPA_vect)
{
	t20ms ++;
}

ISR (PCINT0_vect)
{
	unsigned char input_A = ( ( PINB & ( 1 << PB1 ) ) >> 1 );
	unsigned char input_B = ( ( PINB & ( 1 << PB4 ) ) >> 4 );

	if( input_A == input_B )
		left_pos++;
	else
		left_pos--;
}

ISR (PCINT1_vect)
{
	unsigned char input_A = ( ( PINC & ( 1 << PC5 ) ) >> 5 );
	unsigned char input_B = ( ( PINC & ( 1 << PC4 ) ) >> 4 );

	if( input_A == input_B )
		right_pos--;
	else
		right_pos++;
}

/*=====   TASK HANDLERS   =====*/
void task_500ms (void)
{
	toggle_led();
	watchdog( TICK );
}

void task_100ms (void)
{
	regulator();
	update_velocities();
	update_duty_cycles();
	transmit_pos();
}

void task_20ms (void)
{

	/*transmit_adc();*/
}

/*=====   MAIN ENTRY POINT   =====*/
int main(void)
{
	/*initialize hardware*/
	init_frobit();

	/*enable interrupts*/
	sei();

	/*start scheduler*/
	start_scheduler();

	return 0;
}

