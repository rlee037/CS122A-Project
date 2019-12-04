/*
 *  8x8 LED Matrix Driver
 *   | This driver encodes the coordinates of the positions lit on a 8x8 LED matrix as a pair of 8 bit values
 *   | Values are output by SPI to a pair of shift registers
 *   | The LED matrix has an AND gate at each coordinate and turns on when the signal for each axis is powered 
 *  
 */

#ifndef _8x8_LED_MATRIX_OUTPUT_
#define _8x8_LED_MATRIX_OUTPUT_

#define DDR_VCC  DDRC
#define PORT_VCC PORTC
#define DDR_GND  DDRD
#define PORT_GND PORTD

//unsigned char x_axis;
//unsigned char y_axis;
 
void LEDMatrix8x8_init() {
    DDR_VCC = 0xFF; PORT_VCC = 0x00; //Initialize for output
    DDR_GND = 0xFF; PORT_GND = 0x00;
    
    return;
}

void LEDMatrix8x8_display(unsigned char x, unsigned char y) {
    PORT_VCC = x;
    PORT_GND = ~y;
    
    return;
}


#endif