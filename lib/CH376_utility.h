// This Library is written to manage and communicate with the CH376 IC
// which is used for USB data connection and MMC file manager for MCUs.
// Author: Gata S. D.
// Date Created: 21 September, 2019.
// Date Last Edited: 21 September, 2019.
// Email: gatstev2@gmail.com
// Version: 1.0
// File: Header File

#include <avr/io.h>

#ifndef CH376_UTIL
#define CH376_UTIL

#define MODE_HOST_0 0x05
#define MODE_HOST_1 0x06
#define MODE_HOST_2 0x07
#define MODE_HOST_3 0X03

#define COMPLETE		0XFF	
#define SELECT			1
#define DESELECT		0
#define CREATE			14
#define MODIFY			22

//************THE FOLLOWING DEFINES ARE FOR CH376 CONTROL PINS ON MCU WHICH INCLUDE BZ,#INT, and CS PINS.
#define CH376_DDR	DDRJ		// Set your desired DDR to be used for CH376 control
#define CH376_PORT	PORTJ		// Set your desired PORT to be used for CH376 control
#define CH376_PIN	PINJ		// Set your desired PIN to be used for CH376 control
#define CH376_SEL	PJ3			// CH376 chip select pin number
#define CH376_BZ	PJ4			// CH376 busy pin number on your MCU
#define INTR_NO		INT6		// Specify the external interrupt number.
#define INTR_PORT	PORTE		// Specify the external interrupt port.
#define EXT_INT_MSK_REG EIMSK	// External interrupt mask register.

#define DELAY_MS(d)	_delay_ms(d)	//Place your MCU ms delay function here.
#define DELAY_US(d)	_delay_us(d)	//Place your MCU us delay function here.

#define CH376_SPI_BUSY	while(CH376_PIN&(1<<CH376_BZ))	// If BZ pin of CH376 is not used, replace this macro with a
														// delay of 2 or 3 micro seconds. E.g. DELAY_US(2)

//******************************************************************************************************

class CH376{
	private:
	char	interrupt_Buffer[256];	
	uint8_t dir_Info_Read(void);
	uint8_t dir_Info_Save(void);
	uint8_t read_Block(char* buf);
	void ch376s_CS(uint8_t);			
	void	init_Ext_Int(uint8_t status);
	uint8_t exchange_CH376_Data(uint8_t);
	uint8_t send_CH376_Cmd(uint8_t);
	uint32_t read_32bit_Data(void);
		
		
	//void	end_Dir_Info(void);		
	uint8_t byte_Locate(uint32_t offset);	
	uint8_t write_Block(const char* buf);
	
	uint8_t read_Var8(uint8_t var);//! Read CH376 internal 8bit variable.
	//uint32_t read_Var32(uint8_t var);	// Read CH376 internal 32 bit variable.
	//void	write_Var8(uint8_t var, uint8_t dat);//! Write CH376 internal 8bit variable.
	//void	write_Var32(uint8_t var, uint32_t dat);//! Write CH376 internal 32bit variable.
	void	write_Ofset_Block(char*,uint8_t,uint8_t);
	uint8_t set_File_Name(const char*);		// set file name before operation is executed.
	uint32_t rtc_To_Fat();	//Get time from RTC and save to file info directory.
	
	uint8_t open_File(const char*);		// file is created if not already exist. Else existing file with same name is open for write/read operation.
	uint8_t create_Dir(const char*);	// Create a new Directory.
	//uint8_t delete_File(const char*);	// delete file.
	//uint8_t rename_File(const char*,const char*); // rename a file.
	uint8_t set_Time(uint8_t);
	
	public:
	//char file_Name[14];			// Not implemented yet. Check next version.
	char time_File_Created[8];
	char time_File_Modified[8];
	char date_File_Created[10];
	char date_File_Modified[10];
	char recent_Path_Record[256];	// Holds the most recent file or dir path that has just been accessed.
	uint8_t ch376_status_update;
	uint8_t usb_Mode_Set;
	void msg(const char*);			// Display interrupt messages to LCD w.r.t interrupt status code.
	uint8_t init_CH376(void);		// Initialize the CH376 chip and return the status (successful or not).
	uint8_t get_IC_Version(void);	// Get the IC version of the current CH376s being used.
	uint8_t get_Disk_Status(void);	// Get disk status (Mounted or Unmounted) and File System Status.
	uint8_t disk_Req_Sense(void);	//	Check disk error i.e. drive corrupt or not.
	uint8_t check_CH376_Circuit(void);	// Check the connection between your MCU and CH376. 1- Successful, 0- Unsuccessful.
	void	sleep_CH376(uint8_t);				// Sleep CH376 for power saving. Wake by initiating Chip Select and wait for 30ms.
	void	reset_all(void);				// Perform hardware reset of CH376 using software.
	uint8_t	set_USB_Mode(uint8_t);			// Set USB mode.
	uint8_t disk_Connect(void);				// check the disk of current plugged device connection status.
	uint8_t disk_Mount(void);				//Initialize disk and test disk ready
	
	
	void	get_Interrupt_Status(void);			// Get interrupt request status code from CH376.
	void	print_interrupt_status(void);		// Prints the status msg given after ch376 interrupts MCU.
	
	uint32_t disk_Capacity(void);		// Query the capacity of the current disk drive (MMC or USB drive).
	uint32_t disk_Free_Space(void);		// Query the free space left in the drive.
	uint32_t get_File_Size(void);		// Get the size in bytes of the currently opened file.
	void update_File_Time();
	
	int32_t read_File_Byte(char* buffer,uint32_t read_OffSet,uint16_t length);	// Read a series of bytes from the opened file given by count.
	int32_t write_File_Byte(const char* buffer, uint32_t write_Ofset = 0, uint16_t length = 0); // Write a series of bytes to the opened file given the count and position.
	int32_t append_File_Byte(const char* buffer, uint16_t length = 0);	// Append a series of byte to the end of the currently opened file.
	uint8_t close_File(uint8_t update = SELECT);	// Close the current file being worked upon.
	
	uint8_t create_File(const char*);	// Use if you wish to create a file without an extension. But first open the path/folder. Otherwise use file_Dir_Create();
	//*****SPECIAL FUNTIONS*****************************************************************************************************************
	uint8_t file_Dir_Open(const char* path_Name);	//Open the directory or file indicated by path. Path includes directory/file name.
	uint8_t	file_Dir_Create(const char* path_Name); //create the directory or file in the path given. Path includes the file/directory name.
	uint8_t file_Dir_Delete(const char* path_Name); // delete the directory or file indicated by the path.
	uint8_t file_Dir_Rename(const char* old_Path, const char* new_Name);// Rename the directory or file indicated by the path.
};

#endif  //#endif CH376_UTIL