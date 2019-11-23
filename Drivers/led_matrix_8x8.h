/*
 *  8x8 LED Matrix Driver
 *   | This driver encodes the coordinates of the positions lit on a 8x8 LED matrix as a pair of 8 bit values
 *   | Values are output by SPI to a pair of shift registers
 *   | The LED matrix has an AND gate at each coordinate and turns on when the signal for each axis is powered 
 *  
 */

#ifndef _8x8_LED_MATRIX_OUTPUT_
#define _8x8_LED_MATRIX_OUTPUT_

#include "spi.h"

#define SHIFT_REG_X 0x01
#define SHIFT_REG_Y 0x02

#define PORT_GND PORTC

//unsigned char x_axis;
//unsigned char y_axis;

// SPI 
void LEDMatrix8x8_init() {
    SPI_MasterInit();
    DDRC = 0xFF; PORTC = 0x00; //Initialize PORTC for output
    DDRD = 0xFF; PORTD = 0x00; //TEMP
    //x_axis = 0x00;
    //y_axis = 0x00;
    
    return;
}

/*
void LEDMatrix8x8_setX(unsigned char x) {
    x_axis = x;
    return;
}
*/

/*
void LEDMatrix8x8_setY(unsigned char y) {
    y_axis = y;
    return;
}
*/

/*
void LEDMatrix8x8_set(unsigned char x, unsigned char y) {
    LEDMatrix8x8_setX(x);
    LEDMatrix8x8_setY(y);
    
    return;
}
*/

/*
void LEDMatrix8x8_display() {
    SPI_Transmit(x_axis, SHIFT_REG_X);
    SPI_Transmit(y_axis, SHIFT_REG_Y);
    
    return;
}
*/

void LEDMatrix8x8_display(unsigned char x, unsigned char y) {
    SPI_Transmit(x);
    //PORT_GND = ~y;
    PORTC = 0x00;
    PORTD = 0xFF;
    
    return;
}

/*
void LEDMatrix8x8_display(unsigned char x, unsigned char y) {
    //LEDMatrix8x8_set(x, y);
    
    //SPI_Transmit(x_axis, SHIFT_REG_X);
    //SPI_Transmit(y_axis, SHIFT_REG_Y);
    SPI_Transmit(x, SHIFT_REG_X);
    SPI_Transmit(y, SHIFT_REG_Y);
    
    return;
}
*/

#endif