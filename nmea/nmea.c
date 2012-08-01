//============================================================================
// Project     : RoboCard
// File        : nmea.c
//============================================================================

//=====   HEADERFILE   =====
#include "nmea.h"

//=====   FUNCTION IMPLEMENTATIONS   =====
void msg_to_str( message_t *msg , char *str )
{
	int i = 0 , j = 0;
	
	//generate header
	str[i++] = '$';
	str[i++] = msg->id[0];
	str[i++] = msg->id[1];
	str[i++] = msg->type[0];
	str[i++] = msg->type[1];
	str[i++] = msg->type[2];
	str[i++] = ',';
	
	//parse body
	for (j = 0 ; msg->body[j] != 0x00 ; j++)
		str[i++] = msg->body[j];
	str[i++] = '*';
	
	//generate checksum
	generate_checksum(str , msg->checksum);
	
	//insert checksum
	str[i++] = msg->checksum[0];
	str[i++] = msg->checksum[1];
	
	//terminate with <CR> <LF> 
	str[i++] = 13;
	str[i++] = 10;
	
	//terminate string
	str[i++] = 0x00;
}

void str_to_msg ( char *str , message_t *msg )
{
	int i = 0 , j = 0 , k = 1;
	
	//process only if string begins with $
	if( str[i++] == '$')
	{
		//parse header
		msg->id[0]   = str[i++];
		msg->id[1]   = str[i++];
		msg->id[2]   = 0x00;
		msg->type[0] = str[i++];
		msg->type[1] = str[i++];
		msg->type[2] = str[i++];
		msg->type[3] = 0x00;
		
		//skip leading comma
		if( str[i] == ',' )
			i++;
		
		//parse body 
		while ( k == 1 )
		{
			//break if termination or end of string is reached
			if( str[i] == '\r' || str[i] == '\n' || str[i] == 0x00)
			{
				k = 0;
				msg->body[j] = 0x00;
			}
			//parse checksum and break if * is reached
			else if( str[i] == '*')
			{
				msg->body[j] = 0x00;
				i++;
				msg->checksum[0] = str[i++];
				msg->checksum[1] = str[i++];
				msg->checksum[2] = 0x00;
				k = 0;
			}
			else	
				msg->body[j++] = str[i++];
		}
	}
}

void generate_checksum ( char *str , char *chk )
{
	int i = 0;
	char checksum = 0;
	char nibble = 0;
	
	//parse only if string begins with $
	if( str[0] == '$' )						
	{
		//calculate checksum
		for ( i = 1 ; str[i] != '*' ; i++)	
			checksum ^= str[i];
			
		//process high nibble
		nibble = (checksum >> 4) & 0x0F;	
		if(nibble < 10)
			chk[0] = nibble + '0';
		else
			chk[0] = nibble - 10 + 'A';
		
		//process low nibble
		nibble = checksum & 0x0F;			
		if(nibble < 10)
			chk[1] = nibble + '0';
		else
			chk[1] = nibble - 10 + 'A';
	}	
}
