/*	
 *  Name & E-mail: Rick Lee, rlee037@ucr.edu
 *	Lab Section: 021
 *	Assignment: Project
 *	Description: Create a reactive 8x8 LED matrix that takes input from infrared sensors and
 *               output coordinates to a pair of shift registers over SPI.
 *               
 *               https://docs.google.com/document/d/1-BVMQTW_uwXY2UxapLD22iGklX0aL5ffLzS6oUiP10s/edit?usp=sharing
 *  
 *	I acknowledge all content contained herein, excluding template 
 * 	or example code, is my own original work.
 */

#include <avr/io.h>

#include "timer_functions.h"
#include "reactive_led_matrix_sm.h"

#include "io.h"

int main(void) {
    DDRA = 0x00; PORTA = 0xFF; //Initialize PORTA for input
    DDRD = 0xFF; PORTD = 0x00; //Initialize PORTD for output
    
    unsigned char i = 0;
    tasks[i].state       = INIT_SENSOR;
    tasks[i].period      = SENSOR_PERIOD;
    tasks[i].elapsedTime = 0;
    tasks[i].active      = 0x01;
    tasks[i].TickFct     = &Tick_Sensor;
    ++i;
    tasks[i].state       = INIT_LED8x8;
    tasks[i].period      = LED8x8_PERIOD;
    tasks[i].elapsedTime = 0;
    tasks[i].active      = 0x01;
    tasks[i].TickFct     = &Tick_LED8x8;
    ++i;
	
	DDRC = 0xFF; PORTC = 0x00;
	
    LCD_init();
    LCD_BacklightOn();
	LCD_Cursor(5);
    LCD_WriteData('a');
    
    TimerSet(GLOBAL_PERIOD);
    //TimerOn();
    
    while (1) {}
    
    return 0;
}

