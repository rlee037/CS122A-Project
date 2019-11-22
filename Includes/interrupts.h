#ifndef _INTERRUPTS_H_
#define _INTERRUPTS_H_

#include <avr/interrupt.h>

void EnableInterrupts(void) {
    sei(); //Set Global Interrupt Flag
    return;
}

void DisableInterrupts(void) {
    cli(); //Clear Global Interrupt Flag
    return;
}

#endif