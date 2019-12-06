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

#include "sensor_matrix_8x8.h"

int main(void)
{
    DDRA = 0x00; PORTA = 0xFF;
    DDRD = 0xFF; PORTD = 0x00;
    SensorMatrix_init();
    
    unsigned char inputs[8] = {0x00};
    
    while (1) {
        //PORTD = ADC_read(0);
        SensorMatrix_getInput(inputs);
        /*
        for (unsigned char i = 0; i < 8; ++i) {
			if (inputs[i] != 0) {
                PORTD |= (1 << i);
            } else {
                PORTD &= ~(1 << i);
            }
        }
        */
    }
}

