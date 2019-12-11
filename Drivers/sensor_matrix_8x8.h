/*
 *   Address and get input from up to an 8x8 matrix of QRD1114 Optical Detectors
 *   PINS ON SENSOR (https://learn.sparkfun.com/tutorials/qrd1114-optical-detector-hookup-guide)
 *    Pin 1: Connect to power through a 10k Ohm resistor. This pin also functions as the output of the sensor (connect to ADC input pin). Has dot on sensor.
 *    Pin 2: GND (on white side)
 *    Pin 3: VCC through 330 Ohm resistor (connect to output pin).
 *    Pin 4: GND (on black side, opposite of pin 1)
 */

#ifndef _SENSOR_MATRIX_H_
#define _SENSOR_MATRIX_H_

#include "adc.h"

//Controls which row gets read as input
#define DDR_CONTROL  DDRB
#define PORT_CONTROL PORTB

void SensorMatrix_init() {
    DDR_CONTROL = 0xFF; PORT_CONTROL = 0x00; //Initialize to output
    
    ADC_init();
    ADC_on();
    return;
}

void SensorMatrix_getInput(unsigned char positions[]) { //position array should always contain 8 chars
    for (unsigned char i = 0; i < 2; ++i) {
        if (ADC_read(i) < 200) {PORTD |= (1 << i);}
        else {PORTD &= ~(1 << i);}
        /*
        PORT_CONTROL = (1 << i);
        for (unsigned char j = 0; j < 8; ++j) {
            if (ADC_read(j) > 200) {
                positions[i] |= (1 << j);
            } else {
                positions[i] &= ~(1 << j);
            }
        }
        */
    }
    
    
    return;
}

#endif