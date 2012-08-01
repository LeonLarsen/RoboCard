//============================================================================
// Project     : RoboCard
// File        : buffer.c
//============================================================================
#include "buffer.h"

int buffer(int cmd , ...)
{
	//state variables
	static int array = 0 , slot = 0 , next_out = 0, new_flag = 0;
	static char buf[BUFFER_DEPTH][BUFFER_SIZE];

	//temporary variables
	va_list args;
	int i = 0,out = 0;
	char *str;
	char input = 0;

	//point list to first argument
	va_start( args , cmd );

	//push or pop
	switch( cmd )
	{
	case PUSH:

		//interpret input af char
		input = (char) va_arg( args , int );

		//if end of string
		if ( input == END_CHAR )
		{
			//insert end characters
			buf[ array ][ slot++ ] = END_CHAR;
			buf[ array ][ slot++ ] = 0x00;

			//make this string next out
			next_out = array;

			//go to next buffer for incoming
			array++;
			if ( array == BUFFER_DEPTH )
				array = 0;
			slot = 0;
			new_flag = 1;
		}
		else

			//else save input in next slot
			buf[ array ][ slot++ ] = input;

		break;

	case POP:

		//if new data is available
		if( new_flag )
		{
			//interpret argument as receive string
			str = va_arg( args , char* );

			//copy from buffer to receive string
			while( ( buf[next_out][i] != 0x00 ) && ( i < BUFFER_SIZE - 2 ) )
			{
				str[i] = buf[next_out][i];
				i++;
			}

			//insert end character
			str[i] = 0x00;

			//clear flag and return 1
			out = 1;
			new_flag = 0;
		}
		break;

	default:
		break;
	}
	return out;
}
