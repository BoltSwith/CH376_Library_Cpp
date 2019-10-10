// This library called SPI.h is written for the general functionality of the AVR 8-bit MCU SPI feature
// It contains the basic functions for SPI control, speed and mode settings.
// File Name: SPI.h
// Author: Gata Stephen. D.
// Date Created: 21 September, 2019.
// Date Last Edited: 10th October, 2019.
// Contact: BoltSwith -----> github.com
// Version: 1.0.1
// File: Source File (C++)
// License: GNU General Public License v3.0

#ifndef _SPI_
#define _SPI_

 
 
#define SPI_DDR		DDRB
#define SPI_PORT	PORTB
#define SPI_PIN		PINB
#define MOSI_PIN	PB2
#define MISO_PIN	PB3
#define SCK_PIN		PB1
#define SS_PIN		PB0
 

// The following #defines list the various common SPI mode set/use/control. you can add yours if not on the list.

#define MASTER_MODE_1 0x50					// MASTER, CLK = FOSC/4, 	CPOL = 0, CPHA = 0	MSB First.
#define MASTER_MODE_2 0x51					// MASTER, CLK = FOSC/16,	CPOL = 0, CPHA = 0	MSB First.
#define MASTER_MODE_3 0x52					// MASTER, CLK = FOSC/64,	CPOL = 0, CPHA = 0	MSB First.
#define MASTER_MODE_4 0x53					// MASTER, CLK = FOSC/128,	CPOL = 0, CPHA = 0	MSB First.

#define MASTER_MODE_5 0x58					// MASTER, CLK = FOSC/4		CPOL = 1, CPHA = 0	MSB First.
#define MASTER_MODE_6 0x59					// MASTER, CLK = FOSC/16	CPOL = 1, CPHA = 0	MSB First.
#define MASTER_MODE_7 0x5A					// MASTER, CLK = FOSC/64	CPOL = 1, CPHA = 0	MSB First.
#define MASTER_MODE_8 0x5B					// MASTER, CLK = FOSC/128	CPOL = 1, CPHA = 0	MSB First.

#define SLAVE_MODE_1	0xC0				//	SLAVE, INTERRUPT ENABLED.	CPOL = 0, CPHA = 0	MSB First.
#define SLAVE_MODE_2	0x40				//	SLAVE, INTERRUPT DISABLED.	CPOL = 0, CPHA = 0	MSB First.

#define SLAVE_MODE_3	0xC8				//	SLAVE, INTERRUPT ENABLED.	CPOL = 1, CPHA = 0	MSB First.
#define SLAVE_MODE_4	0x48				//	SLAVE, INTERRUPT DISABLED.	CPOL = 1, CPHA = 0	MSB First.


#define YES 1
#define NO 0

#include <avr/io.h>

class SPI_Feat {
//static uint8_t cur_spi_speed;				// static variable used to monitor current SPI set speed. Modes: 1->4MHz 2->1MHz 3->250KHz 4->125KHz

uint8_t	spi_speed_mode;							// SPI speed select of the current SPI user-device.
uint8_t spi2x_state;						// if 1, SPI2X is ON, if 0, SPI2X is OFF.
void	spi_init(void);

public:

void	spi_Disable(void);						// deactivate the spi feature.
uint8_t spi_Exchange_Data(uint8_t);			// send and receive spi data
void	spi_Exchange_Field(uint8_t* send,uint8_t* recieve,uint16_t length); // send entire array1 content saving return data in array2.
void	spi_Send_Field(uint8_t* send, uint16_t length);


void	spi_Ready(void);					// activate the spi feature setting the speed to the object predefined speed.
void	spi_Change_Rate(uint8_t);			// change the rate  of data transfer for the particular object.
void	spi2x_Activate(uint8_t);					// double/undouble the speed of the current spi data rate.

SPI_Feat(){									// Contructor for SPI class without parameters.
	spi_speed_mode = MASTER_MODE_1;
	spi2x_state = YES;
	spi_init();
	}
SPI_Feat(uint8_t mode_select, uint8_t double_spi2x = NO){		// constructor for SPI class specifying spi mode.
	spi_speed_mode = mode_select;
	if (double_spi2x){ spi2x_state = YES; SPSR |= (1<<SPI2X);}
	else {spi2x_state = NO; SPSR &= ~(1<<SPI2X);}
	spi_init();	
	}

};
#endif