/*  
 *  Initialize ports by inputting the port label and a char to set the DDR value 
 *  
 */

#ifndef _INITIALIZE_PORT_H_
#define _INITIALIZE_PORT_H_

#define A 0x00;
#define B 0x01;
#define C 0x03;
#define D 0x04;

// DDR values
//  - 0 to set pin for input
//  - 1 to set pin for output
//  - 0x00 to set port for input
//  - 0xFF to set port for output
//
// Port values
//  - initialize to 1 when pin is input
//  - initialize to 0 when pin is output
//  - initialize to 0xFF when DDR is set for input
//  - initialize to 0x00 when DDR is set for output

void Port_init(unsigned char DDR, unsigned char port) {
    switch (port) {
        case A:
            DDRA = DDR; PORTA = ~DDR;
            break;
        case B:
            DDRB = DDR; PORTB = ~DDR;
            break;
        case C:
            DDRC = DDR; PORTC = ~DDR;
            break;
        case D:
            DDRD = DDR; PORTD = ~DDR;
            break;
        default:
            break;
    }
    
    return;
}

#endif