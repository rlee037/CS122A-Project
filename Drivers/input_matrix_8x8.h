/*  
 *  
 *  Get input from a 8x8 matrix of inputs connected to two ports
 *  
 */

#ifndef _INPUT_MATRIX_8x8_H_
#define _INPUT_MATRIX_8x8_H_

#define DDR_X  DDRA
#define DDR_Y  DDRB
#define PIN_X  PINA
#define PIN_Y  PINB
#define PORT_X PORTA
#define PORT_Y PORTB

void InputMatrix8x8_init() {
    DDR_X  = 0x00; PORT_X = 0xFF; //Set ports for input
    DDR_Y  = 0x00; PORT_Y = 0xFF;
    
    return;
}

unsigned char getAxisX() {
    return ~PIN_X;
}

unsigned char getAxisY() {
    return ~PIN_Y;
}

unsigned short getData() {
    unsigned char upperByte = getAxisX();
    unsigned char lowerByte = getAxisY();
    
    return (upperByte << 8) | lowerByte; // store bytes in short to return both inputs as one piece of data
}

#endif