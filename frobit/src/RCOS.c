//============================================================================
// Project     : RoboCard
// File        : RCOS.c
//============================================================================

//=====   HEADER FILE   =====
#include "RCOS.h"

//=====   FUNCTION IMPLEMENTATIONS   =====
void init_scheduler(void)
{
	//normal mode
	TCCR1A = 0;

	//prescaler 8
	TCCR1B = ( 1 << CS11 );

	//enable compare match interrupt
	TIMSK1 = ( 1 << OCIE1A );

	//set compare value
    OCR1AH = (40000 >> 8);
    OCR1AL = (40000 & 0xFF);
}

void start_scheduler( void )
{
	unsigned char t100ms = 0 , t500ms = 0;

	while( 1 )
	{
		//if interrupt has occurred
		if (t20ms)
		{
			t20ms = 0;
			task_20ms();
			t100ms++;

			//if 100 ms has lapsed
			if (t100ms == 5)
			{
				task_100ms();
				t100ms = 0;
				t500ms++;

				//if 500 ms has lapsed
				if (t500ms == 5)
				{
					task_500ms ();
					t500ms = 0;
				}
			}
		}
	}
}
