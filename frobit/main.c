//============================================================================
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
// PB3 - Left PWM reverse		PC3 - ADC 3					PD3 - Right PWM reverse
// PB4 - INT4 Left hall A		PC4 - INT12 Right hall A	PD4 - USB D-
// PB5 - SCK					PC5 - Right hall B			PD5 - Left PWM forward
// PB6 - X-tal					PC6 - Reset 				PD6 - Right PWM forward
// PB7 - X-tal												PD7 - BL switch

//=====   DEFINES   =====
//uart.h
#define BAUDRATE    	115200

//led.h
#define LED_PORT		B
#define LED_PIN 		0

//buffer.h
#define BUFFER_SIZE 	40
#define BUFFER_DEPTH 	2
#define END_CHAR		'\n'

//nmea.h
#define MAX_NMEA_SIZE 	30

//timer0
#define TIMER0_PRESCALER 8

//timer2
#define TIMER2_PRESCALER 8

//=====   INCLUDES   =====
//device definitions
#include <avr/io.h>

//cli(), sei(), ISR()
#include <avr/interrupt.h>

//modules
#include "src/frobit.h"

//=====   GLOBAL VARIABLES   =====
unsigned char t20ms = 0;
int left_pos = 0, right_pos = 0;						//number of ticks since start
int left_setpoint_velocity, right_setpoint_velocity;	//desired speeds
int left_corrected_velocity, right_corrected_velocity;	//corrected speeds

//=====   INTERRUPT SERVICE ROUTINES   =====
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
//=====   TASK HANDLERS   =====
void task_500ms (void)
{
	toggle_led();
//	transmit_pos();
//	transmit_adc();
}

void task_100ms (void)
{
	regulator();
	update_velocities();
	update_duty_cycles();
}

void task_20ms (void)
{

}

int main(void)
{
	//initialize hardware
	init_frobit();

	//enable interrupts
	sei();

	//start scheduler
	start_scheduler();

	return 0;
}


//End of file
