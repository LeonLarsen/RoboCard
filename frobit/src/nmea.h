/*============================================================================
// Project     : RoboCard
// File        : nmea.h
// Author      : Leon Bonde Larsen
// Version     : 2.0
// Copyright   : Open Source
// Format      : Ansi-style C
// Description : This module implements the NMEA protocol as a data link layer
//============================================================================
// Usage       :
//						char string[SIZE];
//						message_t msg;
//
//						str_to_msg( string , &msg );
//						msg_to_str( &msg , string );
//==========================================================================*/
#ifndef  RC_NMEA
#define  RC_NMEA

/*=====   INCLUDES   =====*/
#include "global.h"
#include <avr/io.h>

/*=====  DEFINES   =====*/
#ifndef MAX_NMEA_SIZE
#define MAX_NMEA_SIZE 	30
#warning "MAX_NMEA_SIZE was not defined. Defaults to 30"
#endif

#define MAX_DATA_SIZE 	( MAX_NMEA_SIZE - 12 )

/*=====   TYPES   =====*/
typedef struct message
{
	char id[3];
	char type[4];
	char body[MAX_DATA_SIZE];
	char checksum[3];
} message_t;

/*=====   FUNCTION DECLARATIONS   =====*/

/*parse from nmea message struct to array of chars*/
void msg_to_str( message_t *msg , char *str );

/*parses from array of chars to nmea message struct*/
void str_to_msg( char *str , message_t *msg );

/*generates checksum for str and stores it in chk*/
void generate_checksum( char *str , char *chk );

#endif  /* RC_NMEA*/
