/*
 *  Watchdog Timer Header file
 *  
 *  Information:
 *    - WDTCSR: Watchdog Timer Control Register
 *       * Bit 7 - WDIF : Watchdog Interrupt Flag
 *          | This bit is set when a time-out occurs in the Watchdog Timer and the Watchdog Timer is configured for interrupt.
 *          | WDIF is cleared by hardware when executing the corresponding interrupt handling vector.
 *          | Alternatively, WDIF is cleared by writing a logic one to the flag. When the I-bit in SREG and WDIE are set, the Watchdog Time-out Interrupt is executed.
 *       * Bit 6 - WDIE : Watchdog Interrupt Enable
 *          | When this bit is written to one and the I-bit in the Status Register is set, the Watchdog Interrupt is enabled.
 *          | If WDE is cleared in combination with this setting, the Watchdog Timer is in Interrupt Mode, and the corresponding interrupt is executed
 *          | if time-out in the Watchdog Timer occurs.
 *          |
 *          | If WDE is set, the Watchdog Timer is in Interrupt and System Reset Mode. The first time-out in the Watchdog Timer will set WDIF.
 *          | Executing the corresponding interrupt vector will clear WDIE and WDIF automatically by hardware (the Watchdog goes to System Reset Mode).
 *          | This is useful for keeping the Watchdog Timer security while using the interrupt. To stay in Interrupt and System Reset Mode,
 *          | WDIE must be set after each interrupt. This should however not be done within the interrupt service routine itself, as
 *          | this might compromise the safety-function of the Watchdog System Reset mode. If the interrupt is not executed before the next time-out,
 *          | a System Reset will be applied.
 *       * Bit 5 - WDP3 : Watchdog Timer Prescaler 3
 *       * Bit 4 - WDCE : Watchdog Change Enable
 *          | This bit is used in timed sequences for changing WDE and prescaler bits. To clear the WDE bit,
 *          | and/or change the prescaler bits, WDCE must be set.
 *          | Once written to one, hardware will clear WDCE after four clock cycles.
 *       * Bit 3 - WDE  : Watchdog System Reset Enable
 *          | WDE is overridden by WDRF in MCUSR. This means that WDE is always set when WDRF is set.
 *          | To clear WDE, WDRF must be cleared first. This feature ensures multiple resets during
 *          | conditions causing failure, and a safe start-up after the failure.
 *       * Bit 2 - WDP2 : Watchdog Timer Prescaler 2
 *       * Bit 1 - WDP1 : Watchdog Timer Prescaler 1
 *       * Bit 0 - WDP0 : Watchdog Timer Prescaler 0
 *    - Watchdog Timer Configuration
 *        WDTON | WDE | WDIE | MODE                            | Action on Timeout
 *       -------|-----|------|---------------------------------|------------------------------------------
 *          0   |  0  |   0  | Stopped                         | None
 *          0   |  0  |   1  | Interrupt Mode                  | Interrupt
 *          0   |  1  |   0  | System Reset Mode               | Reset
 *          0   |  1  |   1  | Interrupt and System Reset Mode | Interrupt, then go to System Reset Mode
 *          1   |  x  |   x  | System Reset Mode               | Reset
 *    - Watchdog Timer Prescale Select
 *       * 0000:    2048 clock cycles (~16    ms @ V_cc = 5.0 V)
 *       * 0001:    4096 clock cycles (~32    ms @ V_cc = 5.0 V)
 *       * 0010:    8192 clock cycles (~64    ms @ V_cc = 5.0 V)
 *       * 0011:   16384 clock cycles (~0.125 s  @ V_cc = 5.0 V)
 *       * 0100:   32768 clock cycles (~0.25  s  @ V_cc = 5.0 V)
 *       * 0101:   65536 clock cycles (~0.5   s  @ V_cc = 5.0 V)
 *       * 0110:  131072 clock cycles (~1.0   s  @ V_cc = 5.0 V)
 *       * 0111:  262144 clock cycles (~2.0   s  @ V_cc = 5.0 V)
 *       * 1000:  524288 clock cycles (~4.0   s  @ V_cc = 5.0 V)
 *       * 1001: 1048476 clock cycles (~8.0   s  @ V_cc = 5.0 V)
 *    
 */

#ifndef _WATCHDOG_TIMER_
#define _WATCHDOG_TIMER_

#include <avr/wdt.h>
#include <avr/interrupt.h>

void WDT_Init(void) {
    cli();                                           // Disable interrupts (critical timing section)
    wdt_reset();                                     // Reset watchdog (use avr/wdt.h)
    WDTCSR = (1 << WDCE) | (1 << WDE);               // Set up WDT interrupt
    WDTCSR = (1 << WDIE) | (1 << WDE) | (1 << WDP3); // Start watchdog with Xs prescaler
    sei();                                           // Re-enable global interrupts
    
    return;
}

void WDT_off(void) {
    cli();
    wdt_reset();
    /* Clear WDRF in MCUSR */
    MCUSR &= ~(1<<WDRF);
    /* Write logical one to WDCE and WDE */
    /* Keep old prescaler setting to prevent unintentional time-out */
    WDTCSR |= (1<<WDCE) | (1<<WDE);
    /* Turn off WDT */
    WDTCSR = 0x00;
    sei();
    
    return;
}

void WDT_Prescaler_Change(unsigned char scale) {
    cli();
    wdt_reset();
    /* Start timed equence */
    WDTCSR |= (1<<WDCE) | (1<<WDE);
    /* Set new prescaler(time-out) value = 64K cycles (~0.5 s) */
    WDTCSR = (scale & 0x27);
    sei();
    
    return;
}

void WDT_Feed() {
    wdt_reset();
}

ISR(WDT_vect) {
    PORTD |= (1 << 5); //turns on backlight
}

#endif