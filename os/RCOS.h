//============================================================================
// Project     : RoboCard
// File        : RCOS.h
// Author      : Leon Bonde Larsen
// Version     : 2.0
// Copyright   : Open Source
// Format      : Ansi-style C
// Description : This module implements a simple run to complete scheduler
//============================================================================
// Usage       :
//						init_scheduler();
//						start_scheduler(); //will never return
//
//						void task_20ms( void )
//						{
//							//things to do every 20 ms
//						}
//
//						void task_100ms( void )
//						{
//							//things to do every 100 ms
//						}
//
//						void task_500ms( void )
//						{
//							//things to do every 500 ms
//						}
//============================================================================
#ifndef  RC_RCOS
#define  RC_RCOS

//=====   INCLUDES   =====
#include <avr/io.h>

extern unsigned char t20ms;

void init_scheduler(void);
void start_scheduler( void );
void task_20ms (void);
void task_100ms (void);
void task_500ms (void);
#endif //RC_RCOS
