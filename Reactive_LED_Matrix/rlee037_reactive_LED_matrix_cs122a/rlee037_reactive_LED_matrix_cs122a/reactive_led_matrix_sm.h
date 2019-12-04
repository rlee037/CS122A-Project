#ifndef _REACTIVE_LED_MATRIX_SM_H_
#define _REACTIVE_LED_MATRIX_SM_H_

//#include "mux_8x1.h"
//#include "input_matrix_8x8.h"
#include "usart_ATmega1284.h"
//#include "led_matrix_8x8.h"
#include "led_matrix_8x8_port.h"

#include "shift_register.h"

unsigned char sensor_x;
unsigned char sensor_y;
unsigned char output_x;
unsigned char output_y;
unsigned char PUCK_x;
unsigned char PUCK_y;

enum Sensor_states{INIT_SENSOR, READ_SENSOR}Sensor_state;
int Tick_Sensor(int state) { //Get input from sensors through USART
    switch (state) { //transitions
        case INIT_SENSOR:
            sensor_x = 0x00;
            sensor_y = 0x00;
            state = READ_SENSOR;
            break;
        case READ_SENSOR:
            //stay in this state to continuously read input from USART
            break;
        default:
            state = INIT_SENSOR; //reinitialize USART reader SM
            break;
    }
    
    switch (state) { //actions
        case INIT_SENSOR:
            //initUSART(0);
            sensor_x = 0x00;
            sensor_y = 0x00;
            break;
        case READ_SENSOR:
            //sensor_x = USART_Receive(0);
            //sensor_y = USART_Receive(0);
            break;
        default:
            sensor_x = 0x00;
            sensor_y = 0x00;
            break;
    }
    
    return state;
}

//0x00: no shift
//0x01: shift left
//0x02: shift right
void move(int x, int y) {
    switch (x) {
        case 0x00: //do nothing
            break;
        case 0x01:
            if (!(PUCK_x & 0x80)) {
                PUCK_x = PUCK_x << 1;
            }
            break;
        case 0x02:
            if (!(PUCK_x & 0x01)) {
                PUCK_x = PUCK_x >> 1;
            }
            break;
        default: //do nothing
            break;
    }
    
    switch (y) {
        case 0x00: //do nothing
            break;
        case 0x01:
            if (!(PUCK_x & 0x80)) {
                PUCK_x = PUCK_y << 1;
            }
            break;
        case 0x02:
            if (!(PUCK_x & 0x01)) {
                PUCK_x = PUCK_y >> 1;
            }
            break;
        default: //do nothing
            break;
    }
    
    return;
}

enum Coordinate_states{INIT_COORDINATE, CALCULATE_COORDINATE}Coordinate_state;
int Tick_Coordinate(int state) { // Get sensor input & puck position to create output
    static unsigned char prev_x;
    static unsigned char prev_y;
    
    static unsigned char temp; //TEST
    
    switch (state) { //transitions
        case INIT_COORDINATE:
            PUCK_x = 0x01;
            PUCK_y = 0x01;
            output_x = 0x00;
            output_y = 0x00;
            temp = 0;
            state = CALCULATE_COORDINATE;
            break;
        case CALCULATE_COORDINATE:
            // stay in this state
            break;
        default:
            state = INIT_COORDINATE;
            break;
    }
    
    switch (state) { //actions
        case INIT_COORDINATE:
            output_x = 0x00;
            output_y = 0x00;
            break;
        case CALCULATE_COORDINATE:
            if (temp < 8) {
                ++temp;
            } else {temp = 0;}
            output_x = 0xFF;//PUCK_x << temp;
            output_y = PUCK_y << temp;
            prev_x = PUCK_x;
            prev_y = PUCK_y;
            if (prev_x | prev_y) {}
            break;
        default:
            output_x = 0x00;
            output_y = 0x00;
            break;
    }
    
    return state;
}

enum LED8x8_states{INIT_LED8x8, DISPLAY_LED8x8}LEDMatrix8x8_state;
int Tick_LED8x8(int state) {
    switch (state) { //transitions
        case INIT_LED8x8:
            state = DISPLAY_LED8x8;
            LEDMatrix8x8_init();
            ShiftReg_init();
            break;
        case DISPLAY_LED8x8:
            // stay in this state to continuously output to 8x8 LED matrix
            break;
        default:
            state = INIT_LED8x8; //reinitialize LED matrix SM
            break;
    }
    
    switch (state) { //actions
        case INIT_LED8x8:
            LEDMatrix8x8_init();
            break;
        case DISPLAY_LED8x8:
            LEDMatrix8x8_display(output_x, output_y);
            break;
        default:
            // do nothing
            break;
    }
    
    return state;
}

#endif