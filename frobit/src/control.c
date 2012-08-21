/*============================================================================
// Project     : RoboCard
// File        : control.c
//==========================================================================*/

/*=====   HEADER FILE   =====*/
#include "control.h"
#include "uart.h"

/*=====   FUNCTION IMPLEMENTATIONS   =====*/
void regulator( void )
{
	static int left_pos_old = 0 , right_pos_old = 0;	/*saved tick count from last entry*/
	static int left_vel_old = 0 , right_vel_old = 0;	/*saved velocity from last entry*/
	static int left_integrator = 0, right_integrator = 0;

	int left_pos_local , right_pos_local;		/*current tick count*/
	int left_ticks, right_ticks;				/*number of ticks since last entry*/
	int left_error, right_error;		/*difference between desired and actual ticks*/

	/*copy tick counts to avoid race conditions*/
	cli();
	left_pos_local = left_pos;
	right_pos_local = right_pos;
	sei();

	/*calculate number of ticks since last entry*/
	left_ticks = left_pos_local - left_pos_old;
	right_ticks = right_pos_local - right_pos_old;

	/*calculate difference between desired and actual ticks*/
	left_error = left_setpoint_velocity - left_ticks;
	right_error = right_setpoint_velocity - right_ticks;

	/*calculate integrator*/
	left_integrator += left_error;
	if ( left_integrator > INTEGRATOR_MAX )
		left_integrator = INTEGRATOR_MAX;
	else if ( left_integrator < - INTEGRATOR_MAX )
		left_integrator = - INTEGRATOR_MAX;

	right_integrator += right_error;
	if ( right_integrator > INTEGRATOR_MAX )
		right_integrator = INTEGRATOR_MAX;
	else if ( right_integrator < - INTEGRATOR_MAX )
		right_integrator = - INTEGRATOR_MAX;

	/*update global velocities*/
	left_corrected_velocity = (left_vel_old + (left_error * P_GAIN) + (left_integrator * I_GAIN)) / 2;
	if ( left_corrected_velocity > VELOCITY_MAX )
		left_corrected_velocity = VELOCITY_MAX;
	else if ( left_corrected_velocity < - VELOCITY_MAX )
		left_corrected_velocity = - VELOCITY_MAX;

	right_corrected_velocity = (right_vel_old + (right_error * P_GAIN) + (right_integrator * I_GAIN)) / 2;
	if ( right_corrected_velocity > VELOCITY_MAX )
		right_corrected_velocity = VELOCITY_MAX;
	else if ( right_corrected_velocity < - VELOCITY_MAX )
		right_corrected_velocity = - VELOCITY_MAX;

	/*upkeep*/
	left_pos_old = left_pos_local;
	right_pos_old = right_pos_local;
	left_vel_old = left_corrected_velocity;
	right_vel_old = right_corrected_velocity;



}
