//============================================================================
// Project     : RoboCard
// File        : control.h
// Author      : Leon Bonde Larsen
// Version     : 2.0
// Copyright   : Open Source
// Format      : Ansi-style C
// Description : This module implements a regulator for the frobit platform
//============================================================================
// Usage       :
//============================================================================
#ifndef  RC_CONTROL
#define  RC_CONTROL

//=====   INCLUDES   =====
//device definitions
#include <avr/io.h>

//cli(), sei(), ISR()
#include <avr/interrupt.h>

//=====   DEFINES   =====
#define P_TERM			2
#define I_TERM 			1
#define INTEGRATOR_MAX 	20

#define VELOCITY_MIN	30
#define VELOCITY_MAX	250

//=====   FUNCTION DECLARATIONS   =====
void regulator( void );

//=====   EXTERNAL VARIABLES   =====
extern int left_pos;
extern int right_pos;
extern int left_setpoint_velocity;
extern int right_setpoint_velocity;
extern int left_corrected_velocity;
extern int right_corrected_velocity;

#endif /*RC_CONTROL*/