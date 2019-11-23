#ifndef _REACTIVE_LED_MATRIX_SM_H_
#define _REACTIVE_LED_MATRIX_SM_H_

//#include "mux_8x1.h"
//#include "input_matrix_8x8.h"
#include "usart_ATmega1284.h"
#include "led_matrix_8x8.h"

unsigned char sensor_x;
unsigned char sensor_y;
unsigned char output_x;
unsigned char output_y;
//unsigned char  PUCK_x;
//unsigned char  PUCK_y;


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
            initUSART(0);
            sensor_x = 0x00;
            sensor_y = 0x00;
            break;
        case READ_SENSOR:
            sensor_x = USART_Receive(0);
            sensor_y = USART_Receive(0);
            break;
        default:
            sensor_x = 0x00;
            sensor_y = 0x00;
            break;
    }
    
    return state;
}


enum Coordinate_states{INIT_COORDINATE, CALCULATE_COORDINATE}Coordinate_state;
int Tick_Coordinate(int state) { // Get sensor input & puck position to create output
    switch (state) { //transitions
        case INIT_COORDINATE:
            output_x = 0x00;
            output_y = 0x00;
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
            //LEDMatrix8x8_display(output_x, output_y);
            LEDMatrix8x8_display(0xFF, 0xFF);
            break;
        default:
            // do nothing
            break;
    }
    
    return state;
}

#endif