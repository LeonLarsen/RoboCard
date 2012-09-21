/*============================================================================
// Project     : RoboCard
// File        : uart.h
// Author      : Leon Bonde Larsen
// Version     : 2.0
// Copyright   : Open Source
// Format      : Ansi-style C
// Description : This module implements settings and functions for UART on the 
//               RoboCard and depends on a 16 MHz clock frequency.
//============================================================================
// Usage       :
//						#define BAUDRATE 115200
//
//					  	init_uart();
//						sei();
//
//						ISR (USART_RX_vect)
//						{
//							received = UDR0;
//						}
//
//						uart_printf(
//							"integer: %d, string: %s, decimal: %f, hex: %h",
//							integer , string , decimal , hex);
//==========================================================================*/
#ifndef  RC_USART
#define  RC_USART

/*=====   INCLUDES   =====*/
#include "global.h"
#include <avr/io.h>
#include <stdarg.h>
#include <stdlib.h>

/*=====   DEFINES   =====*/
#define DECIMAL_SEPARATOR '.'
#define NEGATIVE_INDICATOR '-'

/*=====   MACROS   =====*/
#ifndef BAUDRATE
#warning "BAUDRATE not defined. Defaults to 115200"
#define BAUDRATE    115200
#endif

#if     BAUDRATE == 2400                            /*baudrate in bps @ 16MHz clock*/
#define     UBRR             832
#elif   BAUDRATE == 4800
#define     UBRR             416
#elif   BAUDRATE == 9600
#define     UBRR             207
#elif   BAUDRATE == 14400
#define     UBRR             138
#elif   BAUDRATE == 19200
#define     UBRR             103
#elif   BAUDRATE == 28800
#define     UBRR             68
#elif   BAUDRATE == 38400
#define     UBRR             51
#elif   BAUDRATE == 57600
#define     UBRR             34
#elif   BAUDRATE == 76800
#define     UBRR             25
#elif   BAUDRATE == 115200
#define     UBRR             16
#elif   BAUDRATE == 230400
#define     UBRR             8
#elif   BAUDRATE == 250000
#define     UBRR             7
#endif

/*=====   FUNCTION DECLARATIONS   =====*/

/*hardware inits for using UART*/
void init_uart (void);

/*simple version of printf for formatted output via UART*/
void uart_printf(char *data, ...);

/*transmit one character*/
void tx (char character);

/*transmit integer*/
void print_d(int number);

/*transmit string*/
void print_s(char *string);

/*transmit floating point*/
void print_f(double number, uint8_t decimals);

/*transmit hex*/
void print_h(unsigned char number);

/*simple math function for evaluatig powers*/
uint32_t power(uint8_t base , uint8_t exponent);

#endif  /* RC_USART*/

