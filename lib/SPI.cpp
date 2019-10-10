// This library is written for the general functionality of the AVR 8-bit MCU SPI feature
// It contains the basic functions for SPI control, data transfer rate and mode settings.
// File Name: SPI.h
// Author: Gata Stephen. D.
// Date Created: 21 September, 2019.
// Date Last Edited: 9th October, 2019.
// Contact: BoltSwith -----> github.com
// Version: 1.0.1
// File: Source File (C++)




#include <avr/io.h>
#include "CH376/SPI.h"

/*
INSTRUCTION FOR USE:
	Follow the instructions below to set this library to work with your MCU's SPI peripheral.
	
1. #include the SPI.h file in the file(s) that calls SPI.h functions e.g. in LCD.cpp or CH376.cpp files.
2. make a global declaration of an SPI_Feat object in the file(s) that calls SPI.h functions e.g. LCD.cpp or CH376.cpp.
	Make the global declaration specifying the preferred data rate for the module/device's communication 
	e.g. CH376_Feat LCD_SPI(MASTER_MODE_1); for communication with an LCD via SPI. This initializes and saves SPI setup for LCD_SPI object.
3. Now place LCD_SPI.spi_Ready(); function call in YOUR CHIP SELECT function. By doing this, the SPI peripheral of the
	MCU is reset to LCD's required data transfer rate whenever the MCU wishes to communicate with the LCD.
	Use LCD_SPI.spi_Exchange_Data() to send a byte to the spi peripheral while receiving output of SPI device at the same time.
4. If this is done for every device that uses the HW SPI to communicate with the MCU, every device is reset to it's preferred
	data rate just before it begins to transfer/receive data. There's no need to restore the previous SPI data transfer rate setup because
	the next use of the SPI peripheral will be set automatically by the spi_Ready() call in the Chip Select function.
5. The library can be further modified or discarded by the user to suit his/her particular need or design.*/



void SPI_Feat::spi_init(void){
		SPI_DDR |= ((1<<SCK_PIN)|(1<<MOSI_PIN)|(1<<SS_PIN));	// Set SPI MOSI and SCK pins as outputs. pull-up SS_PIN. 
		SPI_DDR &= ~(1<<MISO_PIN);								// Set SPI MISO pin as input.
}

void SPI_Feat::spi_Ready(void){
	SPCR = spi_speed_mode;						// SPI enabled for master mode
	if (spi2x_state) SPSR |= (1<<SPI2X);
	else SPSR &= ~(1<<SPI2X);
}

void SPI_Feat::spi_Change_Rate(uint8_t new_mode){
	spi_speed_mode = new_mode;					// change the speed of the object.
	}				

void SPI_Feat::spi_Disable(void){
	SPCR = 0;							// Turn off the SPI feature
	SPSR &= ~(1<<SPI2X);				// SPI speed undoubled for the sake of ADC
}

uint8_t SPI_Feat::spi_Exchange_Data(uint8_t data){
	SPDR = data;						// write command to CH376
	while (!(SPSR & 0x80));		// wait for SPI transfer to complete
	data = SPDR;
	return data;
}

void SPI_Feat::spi_Exchange_Field(uint8_t* send,uint8_t* receive,uint16_t length){ // Send bulk of data and receive bulk from device.
	
	for (uint16_t i = 0; i < length; i++) {
		SPDR = send[i];
		while (!(SPSR & 0x80));		// wait for SPI transfer to complete
		receive[i] = SPDR;
	}
}

void	SPI_Feat::spi_Send_Field(uint8_t* send, uint16_t length){ // Only send an entire bulk of data without receiving any.
	
	for (uint16_t i = 0; i < length; i++) {
		SPDR = send[i];
		while (!(SPSR & 0x80));
	}
}

void SPI_Feat::spi2x_Activate(uint8_t query){		// double/undouble the speed of the current spi speed.
	if(query){spi2x_state = YES;}
	else{spi2x_state = NO;}		// SPI speed undoubled
}
	
	