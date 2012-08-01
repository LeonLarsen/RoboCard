//============================================================================
// Project     : RoboCard
// File        : uart.c
//============================================================================
#include "led.h"

void led(char on)
{
	//turn onboar LED on or off
	if (on)
		LED_PORT_REG &= ~(1<<LED_PIN);               //set PB0 output to GND turning led on
	else
		LED_PORT_REG |= (1<<LED_PIN);                //set PB0 output to VCC turning led off
}

//=====
void init_led(void)
{
	//initialize onboard LED
	led(0);                                          //make sure the led is off
	LED_DDR |= (1<<LED_PIN);                         //enable PB0 (led pin) as output
}

//=====
void toggle_led(void)
{
	//toggle onboard LED
	LED_PORT_REG ^= (1<<LED_PIN);                    //XOR with 1 to toggle
}

//=====
void wait(long ms)
{
	//wait a number of milli seconds
	float count = ms*16000;                           //factor @ 16MHz
	while(count>0)
	count--;
}

