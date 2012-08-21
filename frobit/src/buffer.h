//============================================================================
// Project     : RoboCard
// File        : buffer.h
// Author      : Leon Bonde Larsen
// Version     : 2.0
// Copyright   : Open Source
// Format      : Ansi-style C
// Description : This module implements a buffer array taking characters and
//				 returning strings.
//============================================================================
// Usage       :
//						char string[SIZE];
//
//						buffer( PUSH , character );
//
//						if( buffer( POP , &string ) )
//							...
//============================================================================
#ifndef  RC_BUFFER
#define  RC_BUFFER

//=====   INCLUDES   =====
#include <avr/io.h>
#include <stdarg.h>
#include "global.h"

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 	30
#warning "BUFFER_SIZE was not defined. Defaults to 30"
#endif

#ifndef BUFFER_DEPTH
#define BUFFER_DEPTH 	3
#warning "BUFFER_DEPTH was not defined. Defaults to 3"
#endif

#ifndef END_CHAR
#define END_CHAR 		'\n'
#warning "END_CHAR was not defined. Defaults to newline"
#endif

//=====  ENUMERATIONS   =====
enum
{
	PUSH,
	POP
};

//=====   FUNCTION DECLARATIONS   =====

//buffer function taking characters and forming strings
int buffer( int cmd , ... );

#endif  // RC_BUFFER
//End of file
