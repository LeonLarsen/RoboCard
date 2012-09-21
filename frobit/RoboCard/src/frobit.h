/*============================================================================
// Project     : RoboCard
// File        : frobit.h
// Author      : Leon Bonde Larsen
// Version     : 2.0
// Copyright   : Open Source
// Format      : Ansi-style C
// Description : This module implements function used in the Frobit firmware
//============================================================================
// Usage       :
//==========================================================================*/
#ifndef  RC_FROBIT
#define  RC_FROBIT

/*=====   INCLUDES   =====*/
/*device definitions*/
#include <avr/io.h>

/*cli(), sei(), ISR()*/
#include <avr/interrupt.h>

/*itoa(), atoi()*/
#include <stdlib.h>

/*strcat(), strcpy()*/
#include <string.h>

/*modules*/
#include "uart.h"
#include "led.h"
#include "nmea.h"
#include "buffer.h"
#include "adc.h"
#include "timer0.h"
#include "timer2.h"
#include "RCOS.h"
#include "hall.h"
#include "control.h"

/*=====   DEFINES   =====*/
#define STRING_SIZE		30
#define WATCHDOG_TIME 	2   /*x times 500ms*/

enum {CHECK,KICK,TICK};

/*=====   FUNCTION DECLARATIONS   =====*/
void init_frobit( void );
void transmit_adc( void );
void update_velocities( void );
void update_duty_cycles( void );
void transmit_pos( void );
unsigned char watchdog( unsigned char );

/*=====   EXTERNAL VARIABLES   =====*/
extern int left_pos;
extern int right_pos;
extern int left_setpoint_velocity;
extern int right_setpoint_velocity;
extern int left_corrected_velocity;
extern int right_corrected_velocity;

#endif
