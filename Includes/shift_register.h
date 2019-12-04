/*	
 *  Shift register driver
 */

#ifndef _SHIFT_REGISTER_H_
#define _SHIFT_REGISTER_H_

//Shift register macros
#define SR_DDR     DDRB
#define SHIFT_REG  PORTB //shift register port; numbers in macros below indicate pin
#define SER        0     //set SER = next bit of data to be sent
#define OE         1     //enable output when set low, disable when high
#define RCLK       2     //shift register transferred to storage register when set to 1
#define SRCLK      3     //clear before sending data
#define SRCLR      4     //allows data to be set when 1

#define reg_8 unsigned char

void ShiftReg_init() {
    SR_DDR |= (1 << SER) | (1 << OE) | (1 << RCLK) | (1 << SRCLK) | (1 << SRCLR); //set pins to output
    
    return;
}

void enableOutputSR() {
    SHIFT_REG &= ~(1 << OE);
    return;
}

void disableOutputSR() {
    SHIFT_REG |= (1 << OE);
    return;
}

void ShiftReg_transmit(reg_8 data) {   // Transmit data to a shift register
    SHIFT_REG |= (1 << SRCLR);        // Set SRCLR to 1 allowing data to be set
    SHIFT_REG &= ~(1 << RCLK);        // Set RCLK to 0
    for (reg_8 i = 0; i < 8; ++i) {   // for each bit of data
        SHIFT_REG &= ~(1 << SRCLK);      // Also clear SRCLK in preparation of sending data
        if ((data >> i) & 0x01) {        // set SER = next bit of data to be sent.
            SHIFT_REG |= (1 << SER);     //
        } else {                         //
            SHIFT_REG &= ~(1 << SER);    //
        }                                //
                                         //
        SHIFT_REG |= (1 << SRCLK);       // set SRCLK = 1. Rising edge shifts next bit of data into the shift register
    }                                 // end for each bit of data
    
    SHIFT_REG |= (1 << RCLK);         // set RCLK = 1. Rising edge copies data from the "Shift" register to the "Storage" register
    
    SHIFT_REG = 0x00;                 // clears all lines in preparation of a new transmission
    
    return;
}

#endif