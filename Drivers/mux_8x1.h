/*  
 *  
 *  Get input from two 8x1 multiplexers
 *  
 */

#ifndef _8x1_MUX_INPUT_H_
#define _8x1_MUX_INPUT_H_

//#include <util/delay.h> //TESTING

#define PORT_MUX_IN PORTA
#define PIN_MUX_IN  PINA
#define DDR_MUX_IN  DDRA
#define MUX_IN1     0
#define MUX_IN2     1

// MUX input pins
#define MUX_INPUT1 ~(PIN_MUX_IN & 0x01)
#define MUX_INPUT2 ~(PIN_MUX_IN & 0x02)

// Select line port & pin numbers
#define PORT_MUX_SEL PORTD
#define DDR_MUX_SEL  DDRD
#define MUX_SEL1     4
#define MUX_SEL2     5
#define MUX_SEL3     6

void MUX8x1_init() {
    DDR_MUX_IN  &= ~((1 << MUX_IN1) | (1 << MUX_IN2));                  // Set MUX output pins as input
    PORT_MUX_IN |=   (1 << MUX_IN1) | (1 << MUX_IN2);
    
    DDR_MUX_SEL |= (1 << MUX_SEL1) | (1 << MUX_SEL2) | (1 << MUX_SEL3); // Set MUX select pins as output
    PORT_MUX_SEL = 0x00;
    
    return;
}

void MUX8x1_select(unsigned char channel) {
    PORT_MUX_SEL &= ~(0x07 << MUX_SEL1);             // Clear MUX select pins
    PORT_MUX_SEL |= ((channel & 0x01) << MUX_SEL1) | // Get the last 3 bits and shift them to the MUX select pins
                    ((channel & 0x02) << MUX_SEL2) |
                    ((channel & 0x04) << MUX_SEL3);
    
    return;
}

unsigned short MUX8x1_getData() {
    unsigned char  upperByte = 0x00;
    unsigned char  lowerByte = 0x00;
    unsigned short muxInput  = 0x0000;
    
    for (unsigned char i = 0; i < 8; ++i) { // for each MUX channel
        MUX8x1_select(i);
        //_delay_ms(1000); //TESTING
        if (MUX_INPUT1) {                      // if the selected row has a triggered sensor
            upperByte |= 0x01;                    // set the last bit of the upper byte to 1
        }
        if (MUX_INPUT2) {                      // if the selected column has a triggered sensor
            lowerByte |= 0x01;                    // set the last bit of the lower byte to 1
        }
        upperByte = upperByte << 1;            // bit shift to prepare for the next MUX input bit
        lowerByte = lowerByte << 1;
    }
    
    muxInput = (upperByte << 8) | lowerByte;   // store bytes in short to return both inputs as one piece of data
    
    return muxInput;
}

#endif