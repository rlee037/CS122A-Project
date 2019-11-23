/*
 *
 *   SPI - Serial Peripheral Interface
 *     Pin        | Direction (Master) | Direction (Servant)
 *    ------------|--------------------|--------------------
 *     MOSI (PB5) | User Defined       | Input
 *     MISO (PB6) | Input              | User Defined
 *     SCK  (PB7) | User Defined       | Input
 *     SS   (PB4) | User Defined       | Input\
 *
 *   UNCHECK CLKDIV8 FUSE WHEN PROGRAMMING
 * 
 */

#ifndef _SPI_H_
#define _SPI_H_

#include <avr/interrupt.h>

#define SS1  3
#define SS2  4
#define MOSI 5
#define MISO 6
#define SCK  7

#define DDR_SPI  DDRB
#define PORT_SPI PORTB

#define SERVANT_SELECT1   PORT_SPI &= ~(1 << SS1)
#define SERVANT_DESELECT1 PORT_SPI |= (1 << SS1)
#define SERVANT_SELECT2   PORT_SPI &= ~(1 << SS2)
#define SERVANT_DESELECT2 PORT_SPI |= (1 << SS2)

void SPI_MasterInit(void) {
    // Set MOSI and SCK as output, all others as input
    DDR_SPI = (1 << MOSI) | (1 << SCK);
    
    // Enable SPI, Master, set clock rate fck/16, enable interrupts
    SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);// | (1 << SPIE);
    
    return;
}

void SPI_ServantInit(void) {
    // Set MISO as output, all others as input
    DDR_SPI = (1 << MISO);
    
    // Enable SPI, enable interrupts
    SPCR = (1 << SPE);// | (1 << SPIE);
    
    sei();
    
    return;
}

void SPI_Transmit(unsigned char data) {
    //Start transmission
    SPDR = data;
    //wait for transmission to complete
    while(!(SPSR & (1 << SPIF))) {}
    
    return;
}

unsigned char SPI_Receive(void) {
    //SERVANT_SELECT;
    
    //wait for transmission
    while (!(SPSR & (1 << SPIF))) {}
    
    //SERVANT_DESELECT;
    
    //return data register
    return SPDR;
}

#endif

/*
//Sky's SPI driver
#ifndef _SPI_H_
#define _SPI_H_

#define SS   4
#define MOSI 5
#define MISO 6
#define SCK  7


//slave SPI init-----------------------------
void SPI_ServantInit(void)
{
	DDRB = (1<<MISO);//output
	SPCR = (1<<SPE);//SPI enabled
}

//transceiver---------------------------------
unsigned char SPI_Tranceive(unsigned char data)
{
	SPDR = data;
	while((SPSR & (1<<SPIF))== 0);
	data=SPDR;
	return data;

}
//transmit only------------------------------
void SPI_Transmit(unsigned char data)
{
	SPDR = data;
	while((SPSR & (1<<SPIF))== 0);
}

//receive only--------------------------------
unsigned char SPI_Receive()
{
	while((SPSR & (1<<SPIF))== 0);
	unsigned char data=SPDR;
	return data;
}

#endif
*/
