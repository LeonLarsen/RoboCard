/*============================================================================
// Project     : RoboCard
// File        : frobit.c
//==========================================================================*/

/*=====   HEADER FILE   =====*/
#include "frobit.h"

/*=====   FUNCTION IMPLEMENTATIONS   =====*/
void init_frobit( void )
{
	init_uart();
	init_led();
	init_scheduler();
	init_adc();
	init_hall();
	DDRB |= ( 1 << DDB2 );
	PORTB |= ( 1 << PB2 );
}

void transmit_adc( void )
{
	static char adc_string[STRING_SIZE];
	static message_t adc_message = { "RC" , "ADC" , "" , "" };

	unsigned char input[2];
	char string[10];
	char parser[20];

	/*perform A/D conversion on PC0*/
	set_adc_channel( 0 );
	start_adc();
	input[0] = get_adc();

	/*perform A/D conversion on PC1*/
	set_adc_channel( 1 );
	start_adc();
	input[1] = get_adc();

	/*parse adc value to message body*/
	itoa( input[0] , parser , 10 );
	string[0] = ',';
	string[1] = 0x00;
	strcat( parser , string );
	itoa( input[1] , string , 10 );
	strcat( parser , string);
	strcpy(adc_message.body , parser );

	/*generate NMEA string from message*/
	msg_to_str( &adc_message , adc_string );

	/*transmit string via uart*/
	uart_printf( "%s" , adc_string );
}

void update_velocities( void )
{
	/*nmea string and message object, declared static to increase function speed*/
	static char velocity_string[STRING_SIZE];
	static message_t velocity_message;

	/*temporary variables*/
	char parser_string[10];
	int i , offset_i;

	/*check buffer for received velocity*/
	if( buffer( POP , &velocity_string ) )
	{
		/*parse string to message*/
		str_to_msg( velocity_string , &velocity_message );

		/*extract first argument and insert end character*/
		i = 0;
		while ( velocity_message.body[i] != ',')
		{
			parser_string[i] = velocity_message.body[i];
			i++;
		}
		parser_string[i] = 0x00;

		/*parse from string to number*/
		left_setpoint_velocity = atoi( parser_string );

		/*jump comma*/
		i++;
		offset_i = i;
		i = 0;

		/*extract next argument and insert end character*/
		while ( velocity_message.body[offset_i] != 0x00 && velocity_message.body[offset_i] != ',' )
		{
			parser_string[i] = velocity_message.body[offset_i];
			i++;
			offset_i++;
		}
		parser_string[i] = 0x00;

		/*parse from string to number*/
		right_setpoint_velocity = atoi( parser_string );
	}
}

void update_duty_cycles( void )
{
	/*pointers to duty registers*/
	static REGISTER(*left_duty_forward)  = 0;
	static REGISTER(*right_duty_forward) = 0;
	static REGISTER(*left_duty_reverse)  = 0;
	static REGISTER(*right_duty_reverse) = 0;
	left_duty_forward  = PWM0(OC0A);
	left_duty_reverse = PWM2(OC2B);

	right_duty_forward = PWM0(OC0B);
	right_duty_reverse = PWM2(OC2A);

	if ( left_corrected_velocity )
	{
		if ( left_corrected_velocity < 0 )
		{
			*left_duty_forward = 0;
			*left_duty_reverse = (char)(0 - left_corrected_velocity);
		}
		else
		{
			*left_duty_reverse = 0;
			*left_duty_forward = (char)(left_corrected_velocity);
		}
	}
	else
	{
		*left_duty_reverse = 0;
		*left_duty_forward = 0;
	}

	if ( right_corrected_velocity )
	{
		if ( right_corrected_velocity < 0 )
		{
			*right_duty_forward = 0;
			*right_duty_reverse = (char)(0 - right_corrected_velocity);
		}
		else
		{
			*right_duty_reverse = 0;
			*right_duty_forward = (char)(right_corrected_velocity);
		}
	}
	else
	{
		*right_duty_reverse = 0;
		*right_duty_forward = 0;
	}
}


void transmit_pos( void )
{
	static char pos_string[STRING_SIZE];
	static message_t pos_message = {"RC" , "POS" , "" , ""};
	static int right_pos_local = 0, left_pos_local = 0;

	char string[10];
	char parser[20];

	cli();
	right_pos_local = right_pos;
	left_pos_local = left_pos;
	sei();

	/*parse encoder values to message body*/
	itoa( left_pos_local , parser , 10 );
	string[0] = ',';
	string[1] = 0x00;
	strcat( parser , string);
	itoa( right_pos_local , string , 10 );
	strcat( parser , string);
	strcpy(pos_message.body , parser );

	/*generate NMEA string from message*/
	msg_to_str( &pos_message , pos_string );

	/*transmit string via uart*/
	uart_printf( "%s" , pos_string );
}
