//============================================================================
// Project     : RoboCard
// File        : uart.c
//============================================================================

//=====   HEADERFILE   =====
#include "uart.h"

//=====   FUNCTION IMPLEMENTATIONS   =====
void init_uart ( void )
{
	//set baud rate
	UBRR0H      =   ( UBRR >> 8 );
	UBRR0L      =   (unsigned char)( UBRR );

	//set to asynchronous operation
	UCSR0A		= 	( 1 << U2X0 );

	//enable rx interrupt, rx and tx
	UCSR0B      =   ( 1 << RXCIE0 ) |
	                ( 1 << RXEN0 )  |
	                ( 1 << TXEN0 );

	//8-bit, one stop-bit, no handshake
	UCSR0C      =   ( 1 << UCSZ01 ) | ( 1 << UCSZ00 );
}

void uart_printf ( char *string , ... )
{
	va_list args;
	char *ptr, *string_value;
	int int_value;
	double fp_value;
	
	//point list to first argument
	va_start( args , string );
	
	//iterate through format string
	for ( ptr = string ; *ptr ; ptr++ )
	{
		//transmit characters if not %
		if(*ptr != '%')
		{
			tx( *ptr );
			continue;
		}
		
		//format arguments according to format string
		switch ( *++ptr )
		{
			//format as integer
			case 'd':
			int_value = va_arg( args , int );
			print_d( int_value  );
			break;
			
			//format as string
			case 's':
			string_value = va_arg( args , char*);
			print_s( string_value );
			break;
			
			//format as decimal number
			case 'f':
			fp_value = va_arg( args , double);
			int_value = va_arg( args, int);
			print_f( fp_value , int_value);
			break;
			
			//formats as hex
			case 'h':
			int_value = va_arg( args, int);
			print_h( int_value);
			break;
		}
	}
}

void tx (char character)
{
	//wait if line is busy
	while ( !( UCSR0A & ( 1 << UDRE0 ) ) );   
	
	//transmit one character       
	UDR0 = character;                              
}

void print_d ( int number )
{
	//insert - if negative
	if ( number < 0 )
	{
		tx( NEGATIVE_INDICATOR );
		number = 0 - number;
	}
	
	//stream number recursively as chars
	if ( number / 10 )
		print_d( number / 10 );
	tx( number % 10 + '0' );
}

void print_s( char *string )
{
	//stream string
	while( *string != 0x00 )
		tx( *string++ );
}

void print_f ( double number , uint8_t decimals )
{
	int int_value;
	float fp_value;
	char string[10];
	
	//truncate decimals
	int_value = (int) number;
	
	//convert integer to string and print
	itoa( int_value , string , 10 );
	print_s( string );
	
	//insert separator
	tx( DECIMAL_SEPARATOR );
	
	//calculate decimals
	fp_value = ( number - int_value ) * power( 10 , decimals );
	
	//convert decimals to string and print
	itoa( (int) fp_value , string , 10 );
	print_s( string );
}

void print_h ( unsigned char number )
{
	//print high nibble
	unsigned char nibble = ( number >> 4 ) & 0x0F;
	if( nibble < 10 )
		tx( nibble + '0' );
	else
		tx( ( nibble-10 ) + 'A');
		
	//print low nibble
	nibble = number & 0x0F;
	if( nibble < 10 )
		tx( nibble + '0' );
	else
		tx( ( nibble-10 ) + 'A');
}

uint32_t power ( uint8_t base , uint8_t exponent )
{
	//calculate power recursively
	if( exponent <= 0 )
		return( 1 );
	return( base * power( base, exponent-1 ) );
}

