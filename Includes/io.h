/*
 *  
 *  CS120B LCD Driver
 *
 *  CHECKLIST FOR USE
 *    1. Wire the LCD correctly
 *    2. Make sure the macros in io.c are set correctly to the ports & pins used
 *    3. Initialize the ports correctly
 *  
 *  WIRING THE LCD
 *    - Pins are 1-16 starting from the left
 *    | #  | Symbol |     Function     |    Conncection   |    Notes
 *    |----|--------|------------------|------------------|--------------
 *    |  1.|    VSS |           Ground |          GND (-) |   Breadboard
 *    |  2.|    VDD |            Power |           5V (+) |   Breadboard
 *    |  3.|     V0 |         Contrast |    Potentiometer |   Breadboard
 *    |  4.|     RS |   H:Data L:Instr |           RS pin | User Defined
 *    |  5.|     RW |   H:Read L:Write |          GND (-) |   Breadboard
 *    |  6.|      E |           Enable |            E pin | User Defined
 *    |  7.|    DB0 |         Data Bus |        Data Port | User Defined
 *    |  8.|    DB1 |         Data Bus |        Data Port | User Defined
 *    |  9.|    DB2 |         Data Bus |        Data Port | User Defined
 *    | 10.|    DB3 |         Data Bus |        Data Port | User Defined
 *    | 11.|    DB4 |         Data Bus |        Data Port | User Defined
 *    | 12.|    DB5 |         Data Bus |        Data Port | User Defined
 *    | 13.|    DB6 |         Data Bus |        Data Port | User Defined
 *    | 14.|    DB7 |         Data Bus |        Data Port | User Defined
 *    | 15.|      A |  Backlight Power | Backlight Pin/5V | User Defined
 *    | 16.|      K | Backlight Ground |          GND (-) |   Breadboard
 *  
 *  MACROS
 *    - DATA_BUS    | Set this to the port attached to pins 7~14  of the LCD
 *    - CONTROL_BUS | Set this to the port attached to pins 4 & 6 of the LCD
 *    - RS          | Set this to the microcontroller pin attached to pin 4 of the LCD
 *    - E           | Set this to the microcontroller pin attached to pin 6 of the LCD
 *  
 *  PORTS
 *    - DATA_BUS & CONTROL_BUS are both initialized as output ports
 *  
 */
 
#ifndef __io_h__
#define __io_h__

void LCD_BacklightOn(void);
void LCD_BacklightOff(void);

void LCD_init();
void LCD_ClearScreen(void);
void LCD_WriteCommand(unsigned char Command);
void LCD_WriteData(unsigned char Data);
void LCD_Cursor(unsigned char column);
void LCD_DisplayString(unsigned char column, const unsigned char *string);
void delay_ms(int miliSec);

#endif

