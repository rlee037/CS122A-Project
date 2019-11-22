/*
 *
 */

#ifndef _SENSOR_MATRIX_H_
#define _SENSOR_MATRIX_H_

#include "spi.h"

#define DDR_INPUT  DDRA
#define PORT_INPUT PORTA
#define PIN_INPUT  PINA
#define DDR_POWER  DDRC
#define PORT_POWER PORTC

void SensorMatrix_init() {
    DDR_INPUT = 0x00; PORT_INPUT = 0xFF; //Initialize for input
    DDR_POWER = 0xFF; PORT_POWER = 0x00; //Initialize for output
    
    return;
}

unsigned short SensorMatrix_getInput() {
    unsigned char  x      = 0x00;
    unsigned char  y      = 0x00;
    unsigned short output = 0x0000;
    
    for (unsigned int i = 0; i < 8; ++i) {
        PORT_POWER = (1 << i);
        if (~PIN_INPUT) {
            y |= (1 << i);
        }
        x |= ~PIN_INPUT;
    }
    
    return out;
}

#endif