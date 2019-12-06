/*
 *  ADC
 *   A0 ADC0
 *   A1 ADC1
 *   etc
 *  Make sure to connect the pin on PORTA that is above the power/ground wires to power (AREF)
 */

#ifndef _ANALOG_TO_DIGITAL_CONVERTER_H_
#define _ANALOG_TO_DIGITAL_CONVERTER_H_

#define PORT_ADC PORTA

void ADC_init(void) {
    ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
    // ADEN: setting this bit enables analog-to-digital conversion.
    // ADSC: setting this bit starts the first conversion.
    // ADATE: setting this bit enables auto-triggering. Since we are
    //        in Free Running Mode, a new conversion will trigger whenever
    //        the previous conversion completes.
    
    return;
}

unsigned char ADC_read(unsigned char channel) {
    channel &= 0x07;                   //remove excess bits, keep values 0~7
    ADMUX |= channel;
    ADCSRA |= (1 << ADSC);             //ADC start conversion
    
    while (!(ADCSRA & (1 << ADIF))) {} //wait for conversion to finish
    
    ADCSRA |= (1 << ADIF);             //clear ADIF by writing 1
    
    ADMUX = 0x00;
    
    return ADC >> 2;
}

void ADC_on(void) {
    ADCSRA |= (1 << ADEN); //ADC Enable
    return;
}

void ADC_off(void) {
    ADCSRA &= ~(1 << ADEN); //ADC Disable
    return;
}

#endif