// This Library is written to manage and communicate with the CH376 IC
// which is used for USB data connection and MMC file manager for MCUs.
// Author: Gata S. D.
// Date Created: 21 September, 2019.
// Date Last Edited: 21 September, 2019.
// Email: gatstev2@gmail.com
// Version: 1.0
// File: Source File (C++)
#ifndef F_CPU
#define F_CPU 16000000UL					//Input your CPU clock Freq. here.
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include "CH376/CH376_Cmd.h"
#include "CH376/SPI.h"
#include "CH376/CH376_utility.h"


SPI_Feat CH376_SPI(MASTER_MODE_1);	// Set prefer SPI Mode here for CH376 chip.
// This is a global declaration of an SPI_Feat object.
// Must be made if the SPI.h library provided is to be used.
//*************************************************************************************************
//The following are CH376 status report messages after interrupt request.
//They are used for debugging purposes. If debugging is required as CH376 executes commands,
//then uncomment the following constant characters.
//Note:They've been commented out simply to save RAM on low RAM MCUs.
/*
const char operation_Successful[] = "Operation Successful.";
const char op_Success_Done[] = "Op. success, done.";
const char usb_Flash_Plugged[] = "USB flash plugged.";
const char usb_Flash_Unplugged[]= "USB flash unplugged!";
const char device_Ready[] = "Device is ready.";
const char disk_Read_Operation[] = "Disk read operation.";
const char disk_Write_Operation[] = "Disk write operation";

const char operation_Failure[] = "Operation failure.";
const char buffer_Overflow[] = "Buffer overflow";
const char file_open_cmd_on_Dir[] = "FILE_OPEN cmd on Dir.";
const char file_Not_Found[] = "File not found.";
const char err_Found_Name[] = "File already exist.";
const char disk_Disconnected[] = "Disk disconnected.";
const char err_Large_Sector[] = "Sector size != 512b";
const char invalid_Partition_Type[] = "Invalid partition type";
const char partition_Not_Formatted[] = "Partition not formatted";
const char disk_Full[]= "Disk Full.";
const char directory_Full[]= "Directory full";
const char closed_File_Operation[] = "Op. on a Clsd. File.";
const char status_Code_0x22[] = "Processing....";
const char unimplemented_Status[] = "UnImplemented Status.";
const char mode_Set_Unsuccessful[] = "Drive mode set unsuccessful.";
const char mmc_Mode_Set_Success[] = "MMC mode set success.";
const char usb_Mode2_Set_Success[]= "USB mode2 set success.";
const char usb_Mode0_Set_Success[] = "USB mode0 set success.";
const char usb_Mode1_Set_Success[] = "USB mode1 set success.";*/

//****************************************************

void CH376::msg(const char* message){
	/*Place code here for debugging purposes.
	If you wish to display debug messages as CH376s
	execute commands, you can place a printf(message); here.
	See set_USB_Mode() and print_interrupt_status() functions for more information.*/
}

//***************************************************************************************

void CH376::ch376s_CS(uint8_t state){				// this function is used to select/de-select the CH376 chip for spi communication.
	CH376_SPI.spi_Ready();							// spi_Ready is placed in chip select function to (re)set MCU SPI data rate to work with CH376.
	if (state) CH376_PORT &= ~(1<<CH376_SEL);		// activate chip_select of the CH376
	else  CH376_PORT |= (1<<CH376_SEL);				// deactivate chip_select of the CH376
	DELAY_US(1);
}

uint8_t CH376::exchange_CH376_Data(uint8_t data){	// Exchange raw data between MCU and CH376
	data = CH376_SPI.spi_Exchange_Data(data);
	CH376_SPI_BUSY;
	return data;
}


uint8_t CH376::send_CH376_Cmd(uint8_t command){	// Send commands to CH376. This is the general command send function. the CH376 CS is pulled down (0)
	ch376s_CS(SELECT);							// before every command. This is to notify the chip that it is about to receive a command and not a
	command = exchange_CH376_Data(command);		// data.
	return command;
}

	uint8_t CH376::init_CH376(void){		// Initialize the CH376 chip and return the status (successful or not).
		DELAY_MS(500);				// Wait for voltage to stabilize.
		init_Ext_Int(SELECT);				// Initialize the external interrupt pin and setup of the MCU to receive interrupt requests from CH376
		CH376_DDR |= (1<<CH376_SEL);		// Set CH376 chip select pin on MCU as output.
		CH376_DDR &= ~(1<<CH376_BZ);		// Set CH376 busy pin on MCU as input.
		return check_CH376_Circuit();		// Return 1 to indicate proper hardware chip circuitry connection, else return 0;
	}

 uint8_t CH376::get_IC_Version(void){		// Get CH376 firmware version number. Ready CH376 datasheet to compare your chip version with returned value.
	uint8_t version;						// Returns the version number of the installed CH376  chip.
	send_CH376_Cmd(CMD_GET_IC_VER);
	version = exchange_CH376_Data(COMPLETE);
	ch376s_CS(DESELECT);
	return version;
}

 uint8_t CH376::check_CH376_Circuit(){				// Check for proper external circuitry  connection of MCU to CH376.
	 uint8_t status;									// Returns 1 if connection is sound, else returns 0;
	 send_CH376_Cmd(CMD_CHECK_EXIST);
	 exchange_CH376_Data(COMPLETE);
	 status = exchange_CH376_Data(COMPLETE);
	 ch376s_CS(DESELECT);
	 return status == (255-COMPLETE)? YES:NO;
 }
	

uint8_t	CH376::set_USB_Mode(uint8_t mode){	// Set USB mode (USB host or USB device) or MMC/microSD mode. See macros in CH376_Utility.h or see 
	uint8_t status;							// datasheet for more information.
	send_CH376_Cmd(CMD_SET_USB_MODE);
	exchange_CH376_Data(mode);
	DELAY_US(10);
	usb_Mode_Set = mode;
	status = exchange_CH376_Data(COMPLETE);
	ch376s_CS(DESELECT);
// If you wish to see debug messages as CH376 executes, then uncomment the following cascaded if-else statements. 
/*
	if((status == USB_RET_SUCCESS) && (mode == MODE_HOST_1)){
		msg(usb_Mode1_Set_Success); 
		 return YES;}
	else if((status == USB_RET_SUCCESS) && (mode == MODE_HOST_0)){
		msg(usb_Mode0_Set_Success);
		return YES;}
	else if((status == USB_RET_SUCCESS) && (mode == MODE_HOST_2)){
		msg(usb_Mode2_Set_Success);
		return YES;}
	else if((status == USB_RET_SUCCESS) && (mode == MODE_HOST_3)){
		msg(mmc_Mode_Set_Success);
	return YES;}
		
	else {msg(mode_Set_Unsuccessful);*/
		return status;//}					//Returns status code.
}

void CH376::print_interrupt_status(){		// Print interrupt status message of CH376. Goto msg(const char*)
											// This function works in conjuction with msg(const char*) to print the status report
											// messages on installed display of your project or on your PC monitor.
											// Both function definitions should be uncommented if the user requires debug messages as CH376
											// execute commands. They've simply been commented out to save RAM for small ram MCUs.
											// This print_interrupt_status() function is called from the ISR after CH376 initiates an interrupt request.
/*
											// to place your print code for debugging.
	switch (ch376_status_update){			// To save RAM for small MCUs, comment out both in this
											//  file and CH376_Utility the following functions: 
	case USB_RET_SUCCESS: msg(operation_Successful);//#1. This print_interrupt_status() function. #2. msg() function 
		break;											// #3. print_interrupt_status() call in Interrupt Service Routine.
	case USB_INT_SUCCESS: msg(op_Success_Done);
		break;
	case USB_INT_CONNECT: msg(usb_Flash_Plugged);
		break;
	case USB_INT_DISCONNECT: msg(usb_Flash_Unplugged);
		break;
	case USB_INT_USB_READY: msg(device_Ready);
		break;
	case USB_INT_DISK_READ: msg(disk_Read_Operation);
		break;
	case USB_INT_DISK_WRITE: msg(disk_Write_Operation);
		break;
		
	case ERR_RET_ABORT: msg(operation_Failure);
		break;
	case USB_INT_BUF_OVER: msg(buffer_Overflow);
		break;
	case ERR_OPEN_DIR: msg(file_open_cmd_on_Dir);
		break;
	case ERR_MISS_FILE: msg(file_Not_Found);
		break;
	case ERR_FOUND_NAME: msg(err_Found_Name);
		break;
	case ERR_DISK_DISCON: msg(disk_Disconnected);
		break;
	case ERR_LARGE_SECTOR: msg(err_Large_Sector);
		break;
		
	case ERR_TYPE_ERROR: msg(invalid_Partition_Type);
	break;
	case ERR_BPB_ERROR: msg(partition_Not_Formatted);
	break;
	case ERR_DISK_FULL: msg(disk_Full);
	break;
	case ERR_FDT_OVER: msg(directory_Full);
	break;
	case ERR_FILE_CLOSE: msg(closed_File_Operation);
	break;
	//case USB_STATUS_CODE22: msg(status_Code_0x22);
	//break;
	default: msg(unimplemented_Status);
	}*/
	//ch376s_CS(DESELECT);				
}

void CH376::sleep_CH376(uint8_t query){		// Put CH376 to sleep to save power.
	if(query){								// To wake chip, send NO or 0 to this function.
	send_CH376_Cmd(CMD_ENTER_SLEEP);
	} else {ch376s_CS(SELECT); DELAY_US(10);}
	ch376s_CS(DESELECT);
}

void CH376::reset_all(void){					// Perform hardware reset of CH376.
	send_CH376_Cmd(CMD_RESET_ALL);
	DELAY_MS(40);
	sleep_CH376(NO);
}


 void CH376::get_Interrupt_Status(void){					//Get the interrupt status message after CH376 requests an interrupt.
	 send_CH376_Cmd(CMD_GET_STATUS);						//To get most recent status code, simply query drive.ch376_status_update
	 ch376_status_update = exchange_CH376_Data(COMPLETE);	//in the user specific execution code e.g. main(). drive.ch376_status_update holds the
	 ch376s_CS(DESELECT);									// most recent interrupt status code.
 }
 
 uint8_t CH376::read_Block(char* buff){			// read a block of raw data from CH376.
	 uint8_t w, b;
	 send_CH376_Cmd(CMD_RD_USB_DATA0);
	 w = b = exchange_CH376_Data(COMPLETE); 
	 if (b){
		 do{
			 *buff = exchange_CH376_Data(COMPLETE);
			 buff ++;
			}while ( -- b );
	 }
	 ch376s_CS(DESELECT);
	 return w;
 }
 
 uint8_t CH376::write_Block(const char* buf){	//Write a block of raw data to CH376.
	 uint8_t	w, b;
	 send_CH376_Cmd(CMD_WR_REQ_DATA);
	 w = b = exchange_CH376_Data(COMPLETE); 
	 if (b){
			do{
				exchange_CH376_Data( *buf );
				buf ++;
				}while (--b);
	 }
	 ch376s_CS(DESELECT);
	 return w ;
 }

uint32_t CH376::read_32bit_Data(void){ //Read 32bit variable e.g. the disk capacity of flash drive in bytes.
	uint32_t capacity = 0;
	for(uint8_t shifter = 0;shifter<25;shifter+=8){ capacity |= (((uint32_t)(exchange_CH376_Data(0))<<shifter));}
	return capacity;
}

	
	uint8_t CH376::read_Var8(uint8_t var){
		    uint8_t	temp;
		    send_CH376_Cmd(CMD_READ_VAR8);
		    exchange_CH376_Data(var);
		    temp = exchange_CH376_Data(COMPLETE);
		    ch376s_CS(DESELECT);
		    return(temp);
	}
 

 /*void	CH376s::write_Var8(uint8_t var, uint8_t dat){
	  send_CH376_Cmd(CMD_WRITE_VAR8);
	  exchange_CH376_Data(var);
	  exchange_CH376_Data(dat);
	  ch376s_CS(DESELECT);
 }
 
*//*
 uint32_t	CH376::read_Var32(uint8_t var){		//Read 32bit variable from CH376. Function is used to get Disk Capacity.
	 send_CH376_Cmd(CMD_READ_VAR32);
	  exchange_CH376_Data(var);
	 return(read_32bit_Data()); 
 }*/
 /*
 void	CH376s::write_Var32(uint8_t var, uint32_t dat){
		 send_CH376_Cmd(CMD_WRITE_VAR32);
		 exchange_CH376_Data(var);
		 for(uint8_t shifter = 0;shifter<25;shifter+=8) exchange_CH376_Data((uint8_t)(dat>>shifter));
		 ch376s_CS(DESELECT);
 }*/
 
 void	CH376::write_Ofset_Block(char* buffer,uint8_t offSet,uint8_t length){	// Write block of raw data specifying an offset.
	     send_CH376_Cmd(CMD_WR_OFS_DATA);
	     exchange_CH376_Data(offSet);  
	     exchange_CH376_Data(length); 
	     if (length){
	     do{
			exchange_CH376_Data(*buffer);
			buffer ++;
		  }while (--length);
	     }
	    ch376s_CS(DESELECT);
 }
/*
 
 void	CH376s::end_Dir_Info(void){
	 write_Var8(0x0D,0x00);	
 }
 */

 
 void CH376::update_File_Time(){					// Updates the file creation and/or modify time and date. These variables are gotten from the
	uint16_t time_Create,time_Modify,date_Create,date_Modify;// user's installed RTC. See rtc_To_Fat() for more information.
	uint8_t t_create = CREATE, t_modify = MODIFY, d_create = CREATE+2,d_modify = MODIFY+2;
	uint8_t tim_Cre[3],tim_Mod[3];
	uint16_t dat_Cre[3],dat_Mod[3];
	
	char temp[64];
	 dir_Info_Read();
	 read_Block(temp);
	 
	for(uint8_t shifter=0;shifter<9;shifter+=8)time_Create |= ((temp[t_create++])<<shifter);
	for(uint8_t shifter=0;shifter<9;shifter+=8)time_Modify |= ((temp[t_modify++])<<shifter);
	for(uint8_t shifter=0;shifter<9;shifter+=8)date_Create |= ((temp[d_create++])<<shifter);
	for(uint8_t shifter=0;shifter<9;shifter+=8)date_Modify |= ((temp[d_modify++])<<shifter);
	
	
	tim_Cre[0] = (uint8_t) ((time_Create>>11) & 0x001f);		//HOUR
	tim_Cre[1] = (uint8_t) ((time_Create>>5) & 0x003f);		//MIN
	tim_Cre[2] = (uint8_t) ((time_Create & 0x001f)<<1);		//SEC
	
	tim_Mod[0] = (uint8_t) ((time_Modify>>11) & 0x001f);		//HOUR
	tim_Mod[1] = (uint8_t) ((time_Modify>>5) & 0x003f);		//MIN
	tim_Mod[2] = (uint8_t) ((time_Modify & 0x001f)<<1);		//SEC
	
	dat_Cre[0] = (uint8_t) ((date_Create>>9) & 0x007f);		//YEAR
	dat_Cre[1] = (uint8_t) ((date_Create>>5) & 0x000f);		//MONTH
	dat_Cre[2] = (uint8_t) (date_Create & 0x001f);				//DAY
	
	dat_Mod[0] = (uint8_t) ((date_Modify>>11) & 0x007f);		//YEAR
	dat_Mod[1] = (uint8_t) ((date_Modify>>5) & 0x000f);		//MONTH
	dat_Mod[2] = (uint8_t) (date_Modify & 0x001f);				//DAY
	 
	for(uint8_t m = 0;m<8;m++)  time_File_Created[m] = time_File_Modified[m] = temp[m] = '\0';		//Clear out time_Holder and temp.
	for(uint8_t m = 0;m<10;m++)  date_File_Created[m] = date_File_Modified[m] = temp[m] = '\0';		//Clear out time_Holder and temp.
	
	for(uint8_t j=0; j<3 ;++j){							// Constructing integer times to strings representing the times and dates.
		ltoa(tim_Cre[j],temp,10);
		strcat(time_File_Created,temp);
		if(j<2) time_File_Created[strlen(time_File_Created)] = ':';
	
		ltoa(tim_Mod[j],temp,10);
		strcat(time_File_Modified,temp);
		if(j<2) time_File_Modified[strlen(time_File_Modified)] = ':';
	}
	
	ltoa(dat_Cre[2],temp,10);
	strcat(date_File_Created,temp);
	date_File_Created[strlen(date_File_Created)] = '/';
	ltoa(dat_Cre[1],temp,10);
	strcat(date_File_Created,temp);
	date_File_Created[strlen(date_File_Created)] = '/';
	dat_Cre[0]+=1980;
	ltoa(dat_Cre[0],temp,10);
	strcat(date_File_Created,temp);
	
	ltoa(dat_Mod[2],temp,10);
	strcat(date_File_Modified,temp);
	date_File_Modified[strlen(date_File_Modified)] = '/';
	ltoa(dat_Mod[1],temp,10);
	strcat(date_File_Modified,temp);
	date_File_Modified[strlen(date_File_Modified)] = '/';
	dat_Mod[0]+=1980;
	ltoa(dat_Cre[0],temp,10);
	strcat(date_File_Modified,temp);
 } //
 
 
 uint32_t CH376::get_File_Size(void){				// Get the size in bytes of the currently opened file.
	 uint32_t result =	0;/*//	read_Var32(VAR_FILE_SIZE);
							 ch376s_CS(DESELECT);
								return result;*/
		 char temp[64];
		 dir_Info_Read();
		 read_Block(temp);
		 
		 for(uint8_t i = 28, shifter = 0; i<32;++i, shifter+=8){result |= ((uint32_t)temp[i])<<shifter;}
		
		return result;
		 
 }
 
 
 uint8_t CH376::get_Disk_Status( void ){			// Get disk status (Mounted or Unmounted) and File System Status.
	 uint8_t result = read_Var8(VAR_DISK_STATUS);
	 ch376s_CS(DESELECT);
	 return result;									// Returns disk status code. Check datasheet for code info.
 }
 
 uint8_t CH376::disk_Req_Sense(void){				//	Check disk error i.e. drive corrupt or not.
		 uint8_t s;
		DELAY_MS(5);
		 s = send_CH376_Cmd(CMD_DISK_R_SENSE);
		DELAY_MS(5);
		ch376s_CS(DESELECT);
		 return(s);									// Returns sense code. Check datasheet for code info.
 }
 
 
 uint8_t CH376::byte_Locate(uint32_t offset){	// Move the data pointer to any position within the opened file. max. position is 0xFFFFFFFF.
	send_CH376_Cmd(CMD_BYTE_LOCATE);
	for(uint8_t shifter = 0;shifter<25;shifter+=8) exchange_CH376_Data((uint8_t)(offset>>shifter));
	ch376s_CS(DESELECT);
	return ch376_status_update==USB_INT_SUCCESS ?  YES:NO;
 }
 
 
 uint8_t CH376::dir_Info_Read(void){			//Read FAT directory info of file. This command is executed before data is read.
	 send_CH376_Cmd(CMD_DIR_INFO_READ);
	 exchange_CH376_Data(COMPLETE);
	 ch376s_CS(DESELECT);
	 return ch376_status_update==USB_INT_SUCCESS ?  YES:NO;
 }
	 
uint8_t CH376::dir_Info_Save(void){			//Save FAT directory info of file. This command is executed after FAT data is written/updated.
	send_CH376_Cmd(CMD_DIR_INFO_SAVE);
	ch376s_CS(DESELECT);
	return ch376_status_update==USB_INT_SUCCESS ?  YES:NO;
}


uint8_t CH376::set_Time(uint8_t create_modif){	// Automatic time of file creation or modification setting. Time is gotten from installed RTC.
		char temp[64];							// See rtc_To_Fat() for more information.
		dir_Info_Read();
		read_Block(temp);
		uint32_t current_Time = rtc_To_Fat();
		for(uint8_t shifter = 0,i = create_modif; shifter<25; shifter+=8) 
		temp[i++] = (uint8_t)(current_Time>>shifter); 
		dir_Info_Read();
		write_Ofset_Block(temp,0,32);
		dir_Info_Save();
		return ch376_status_update==USB_INT_SUCCESS ?  YES:NO;
}

uint8_t CH376::disk_Mount(void){					//Mount disk and test disk ready for writing and reading. (USB drive and MMC/microSD).
	send_CH376_Cmd(CMD_DISK_MOUNT);
	ch376s_CS(DESELECT);
	return ch376_status_update==USB_INT_SUCCESS ?  YES:NO;
}

uint8_t CH376::disk_Connect(void){					// check the disk of currently plugged device connection status. (USB storage devices only....!!!).
	send_CH376_Cmd(CMD_DISK_CONNECT);
	ch376s_CS(DESELECT);
	return ch376_status_update==USB_INT_SUCCESS ?  YES:NO;
}

uint8_t CH376::set_File_Name(const char* name){	// Set name of file or directory to create, open, rename or delete.
	uint8_t name_Length;
	send_CH376_Cmd(CMD_SET_FILE_NAME);
	name_Length = strlen(name);
	if(name_Length < 14){
		for(int i = 0; i<name_Length; ++i){
			exchange_CH376_Data(name[i]);
		}
		exchange_CH376_Data('\0');
		ch376s_CS(DESELECT);
		return YES;
		} else {/*msg(operation_Failure);*/ ch376s_CS(DESELECT); return NO;}	// Uncomment msg(operation_Failure); if debugging is allowed.
	}

uint32_t CH376::rtc_To_Fat(){					/*Uncomment the following codes after the criteria written below has been fulfilled
													
													//File Date and Time creation/modification are set automatically by acquiring
	uint32_t fat_Time = 0;							//the time and date from the user's installed RTC.
	uint32_t temp = GetYear() - 1980;				//Users are to provide function definitions for the following time functions:
	fat_Time = (temp << 25);			//YEAR		//1. GetYear() 2. GetMonth() 3. GetDay() 4. GetHour() 5. GetMinute() 6. GetSecond()
	temp = GetMonth();								//The above functions are to return decimal equivalents of their respective names.
	fat_Time |= (temp << 21);			//MONTH		//E.g. GetMonth() is to return decimal "8" without the quotes i.e. representing the month of August.
	temp = GetDay();								//GetYear() is to return the 2019 which is the year this program was written.
	fat_Time |= (temp << 16);			//DAY		//Time returned by all these individual functions is packed into a 32bit variable and
													//used to set file time.
	
	temp = GetHour();								//Note: GetYear() is to return 16bit variable representing the particular year.
	fat_Time |= ( temp << 11);			//HOUR		//All other functions are to return 8bit variables.
	temp = GetMinute();								//
	fat_Time |= (temp << 5);			//MINUTE	//
	temp = GetSecond();								//
	fat_Time |= (temp>>1);				//Second	//
													//
	return	fat_Time;		// Time and Date is packed into a 32bit variable.*/
	
	return 0x4F48A467;		//Default time set for all files created and modified. Comment out after the above criteria has been fulfilled.
}							//Current default date is today Tuesday 8th October, 2019. Time is 08:35:14 PM. Check file creation date to confirm.


uint32_t CH376::disk_Capacity(void){				// Query physical capacity of disk drive. Value is in bytes.
	uint32_t total_Disk_Capacity = 0;
	send_CH376_Cmd(CMD_DISK_CAPACITY);
	ch376s_CS(DESELECT);
		send_CH376_Cmd(CMD_RD_USB_DATA0);
		exchange_CH376_Data(COMPLETE);
		total_Disk_Capacity = read_32bit_Data(); 
		ch376s_CS(DESELECT);
	return ch376_status_update==USB_INT_SUCCESS ? (total_Disk_Capacity*512):NO;
}

uint32_t CH376::disk_Free_Space(void){				// Query free space in disk drive available for data storage. Value return is in bytes.
	uint32_t free_Disk_Capacity = 0;
	send_CH376_Cmd(CMD_DISK_QUERY);
	ch376s_CS(DESELECT); 
		send_CH376_Cmd(CMD_RD_USB_DATA0);
		for(uint8_t p = 0; p<5 ;++p)exchange_CH376_Data(COMPLETE);
		free_Disk_Capacity = read_32bit_Data();
		exchange_CH376_Data(COMPLETE);
		ch376s_CS(DESELECT);
	return ch376_status_update==USB_INT_SUCCESS ?   (free_Disk_Capacity*512):NO;
}

uint8_t CH376::create_File(const char* name){	// Create file and Open for writing. Truncates file if already in existence with similar name.
	if(set_File_Name(name));
	else {/*msg(operation_Failure);*/ return NO;}
	send_CH376_Cmd(CMD_FILE_CREATE);
	set_Time(CREATE);
	set_Time(MODIFY);
	ch376s_CS(DESELECT);
	return ch376_status_update==USB_INT_SUCCESS ?  YES:NO;
}

uint8_t CH376::create_Dir(const char* name){	// Create new Directory or open existing directory.
	if(set_File_Name(name)){send_CH376_Cmd(CMD_DIR_CREATE);
	set_Time(CREATE);
	set_Time(MODIFY);
	ch376s_CS(DESELECT);}
	return ch376_status_update==USB_INT_SUCCESS ?  YES:NO;
}


uint8_t CH376::close_File(uint8_t update){		// Close currently opened file. Send 1 or 0 to update file record. See datasheet for more info.
	send_CH376_Cmd(CMD_FILE_CLOSE);
	exchange_CH376_Data(update);
	ch376s_CS(DESELECT);
	return ch376_status_update==USB_INT_SUCCESS ?  YES:NO;
}

uint8_t CH376::open_File(const char* name){			//Open file or directory if it exists. Returns ERR_MISS_FILE if file is not found.
if(set_File_Name(name)){
	send_CH376_Cmd(CMD_FILE_OPEN);					// execute any other operation e.g. create another file. Do not close file after reading from it.
	ch376s_CS(DESELECT);
	}												// Important Notice: Do not close_file() after you open and READ from it. Only 
													// execute close_File() after WRITING to the file. After reading  an opened file ONLY, simply go ahead to
													// If you open file, read the file, AND THEN WRITE to the same file, you may go ahead to close it. 
return ch376_status_update==USB_INT_SUCCESS ?  YES:NO;
}


/*
uint8_t CH376s::delete_File(const char* name){
		if(set_File_Name(name));
		else {statusPrint.msg(operation_Failure); return NO;}
		send_CH376_Cmd(CMD_FILE_ERASE);
		ch376s_CS(DESELECT);
		return YES;
	}
	*/
	/*uint8_t CH376s::rename_File(const char* old_Name,const char* new_Name){
		if(strlen(new_Name)){			// check if new_Name contains characters before rename operation.
		uint8_t dot_Pos = 0, char_Rep = 0;
		open_File(new_Name);
		if(ch376_status_update == ANSW_USB_INT_SUCCESS || ch376_status_update==ANSW_ERR_OPEN_DIR)return NO;		//file already exists
		open_File(old_Name);
		if (ch376_status_update != ANSW_USB_INT_SUCCESS && ch376_status_update != ANSW_ERR_OPEN_DIR) return NO;	//Old file does not exist.
	
		dir_Info_Read();
		read_Block(interrupt_Buffer);
		for( ; dot_Pos < 12; ++dot_Pos){
			if(new_Name[dot_Pos] == '.') break;
		}
		for(char_Rep = 0; char_Rep < 12; char_Rep++){
			if(char_Rep < dot_Pos) interrupt_Buffer[char_Rep] = new_Name[char_Rep];
			else if(char_Rep < 8) interrupt_Buffer[char_Rep] = ' ';
			else if(char_Rep > 8){
				if(new_Name[dot_Pos+char_Rep-8] != 0)interrupt_Buffer[char_Rep-1] = new_Name[dot_Pos+char_Rep-8];
				else interrupt_Buffer[char_Rep-1] = ' ';
			}
		}
		dir_Info_Read();
		write_Ofset_Block(interrupt_Buffer,0,11);
		dir_Info_Save();
		if(ch376_status_update==ANSW_USB_INT_SUCCESS){close_File();return YES;}
		else {close_File(); return NO;}
	}
	return NO;
}
	*/
	
int32_t CH376::read_File_Byte(char* buffer,uint32_t read_OffSet, uint16_t length){	// Read file in bytes at Offset value in length given. 
	uint8_t v;													// simply place buffer in which data is to be read into, indicate the offset,
	uint16_t actual_Count = 0;									// specity the number of bytes to read starting from offset using length.
	if(read_OffSet) byte_Locate(read_OffSet);
	send_CH376_Cmd(CMD_BYTE_READ);
	exchange_CH376_Data((uint8_t)length);
	exchange_CH376_Data((uint8_t)(length>>8));
	ch376s_CS(DESELECT);
	for( ;ch376_status_update==USB_INT_DISK_READ; actual_Count+=v,buffer+=v){
		v = read_Block(buffer);
		send_CH376_Cmd(CMD_BYTE_RD_GO);
		ch376s_CS(DESELECT);
	}
	return ch376_status_update==USB_INT_SUCCESS ?  actual_Count:NO;	//Return actual byte read to file if operation was successful all through.
}

int32_t CH376::write_File_Byte(const char* buffer, uint32_t write_Ofset, uint16_t length){// Similar as reading bytes above.
	uint8_t v;																			// But this time, write to a file in bytes.
	uint16_t actual_Count = 0;
	if(length==0) length = strlen(buffer);
	if(write_Ofset) byte_Locate(write_Ofset);
	send_CH376_Cmd(CMD_BYTE_WRITE);
	exchange_CH376_Data((uint8_t)length);
	exchange_CH376_Data((uint8_t)(length>>8));
	ch376s_CS(DESELECT);
	for(;ch376_status_update==USB_INT_DISK_WRITE; actual_Count+=v,buffer+=v){
		v = write_Block(buffer);
		send_CH376_Cmd(CMD_BYTE_WR_GO);
		ch376s_CS(DESELECT);
		}
	set_Time(MODIFY);
	update_File_Time();
	return ch376_status_update==USB_INT_SUCCESS ?  actual_Count:NO; //Return actual byte written to file if operation was successful all through.
}

int32_t CH376::append_File_Byte(const char* buffer, uint16_t length){	// Append data in bytes to the end of the currently opened file.
	length = write_File_Byte(buffer,0xFFFFFFFF,length);
	return ch376_status_update==USB_INT_SUCCESS ?  length:NO;
}

//************************************************************************************************

uint8_t CH376::file_Dir_Open(const char* path_Name){ //Open "file or directory" specifying the path to file e.g. "/HOUR12.TXT" for a file in
		uint8_t k = 0, i = 1, p = strlen(path_Name);	//root directory. Use "/YEAR2019/OCTOBER/DAY16/HOUR2.TXT" to open the file indicated
		char temp_Buffer[256];							// by the series of cascaded folders.
		strcpy(temp_Buffer,path_Name);					// Always use forward slash '/' for all path specifier.
		while (i<=p){									// See open_File() function comments for more information.
		for( ; temp_Buffer[i] != '/' && temp_Buffer[i] != '\\' && temp_Buffer[i] != '\0'; ++i);
		temp_Buffer[i] = '\0';							
		open_File(&temp_Buffer[k]);
		k = ++i;
		if (ch376_status_update != USB_INT_SUCCESS && ch376_status_update != ERR_OPEN_DIR) return NO;
	}
	update_File_Time();
	if (k){strcpy(recent_Path_Record,path_Name); return YES;}
	else return NO;
}	

uint8_t	CH376::file_Dir_Create(const char* path_Name){		// Create "file or directory" by specifying the path e.g. "/RICE.TXT" for a file
	uint8_t k = 0, i = 1 , p = strlen(path_Name);			// in root directory. Use "/LIFE/HEALTH/FOOD/RICE.TXT" to open the file
	strcpy(interrupt_Buffer,path_Name);						// indicated by the series of cascaded folders.
	while (i<=p){											// Always use forward slash "/"  to indicate root directory or cascaded folders.
	for( ; interrupt_Buffer[i] != '/' && interrupt_Buffer[i] != '\\' && interrupt_Buffer[i] != '\0' && interrupt_Buffer[i] != '.'; ++i);
		if(interrupt_Buffer[i] == '.'){create_File(&interrupt_Buffer[k]); i += 5;} 
		else {interrupt_Buffer[i] = '\0'; create_Dir(&interrupt_Buffer[k]);}
		k = ++i;
	if (ch376_status_update != USB_INT_SUCCESS) return NO;
	}
	if (k){strcpy(recent_Path_Record,path_Name); return YES;} //Returns 1 if operation is successful else returns 0 if unsuccessful
	else return NO;
}

uint8_t CH376::file_Dir_Delete(const char* path_Name){ //Delete "file or directory" indicated by path_Name e.g. "/HOUSE.TXT" for file in root directory.
	file_Dir_Open(path_Name);							//Use "/PROVINCE/DISCREET/STREET/HOUSE.TXT" for file in cascade folder
	send_CH376_Cmd(CMD_FILE_ERASE);						// path. Always use forward slash '/' for all path specifier.
	ch376s_CS(DESELECT);
	return ch376_status_update==USB_INT_SUCCESS ?  YES:NO;
}

uint8_t CH376::file_Dir_Rename(const char* old_Path, const char* new_Name){//Rename "file or directory" indicated by new_Name. Old path  
	if(strlen(new_Name)){													//points to the old name of file or directory to be replaced. 
	uint8_t dot_Pos = 0, char_Rep = 0;										//Example: old_Path is "/EARTH/CONTINENT/REGION/COUNTRY.TXT" , new_Name is "NATION.TXT".
	char temp_buffer[256];													// The COUNTRY.TXT file will be renamed NATION.TXT.
	strcpy(temp_buffer,old_Path);											// Notice that new_Name does not have a forward "/" slash attached.
	char* lastSlash = strrchr(temp_buffer,'/');
	lastSlash[1] = '\0';
	strcat(temp_buffer,new_Name);
	file_Dir_Open(temp_buffer);
	if(ch376_status_update == USB_INT_SUCCESS || ch376_status_update==ERR_OPEN_DIR){	//new_Name file or folder already exists	 return NO;}	
	file_Dir_Open(old_Path);
	if(ch376_status_update != USB_INT_SUCCESS && ch376_status_update != ERR_OPEN_DIR){return NO;}	//Old_Name file does not exist.
		dir_Info_Read();
		read_Block(interrupt_Buffer);
		for( ; dot_Pos < 12; ++dot_Pos){
			if(new_Name[dot_Pos] == '.') break;
		}
		if(dot_Pos>=11){ 
			while(char_Rep<12){
				for(uint8_t u = strlen(new_Name); char_Rep < u; char_Rep++){
					interrupt_Buffer[char_Rep] = new_Name[char_Rep];
				}
				interrupt_Buffer[char_Rep++] = ' ';
			}
		}else{
		for( ; char_Rep < 12; char_Rep++){
			if(char_Rep < dot_Pos) interrupt_Buffer[char_Rep] = new_Name[char_Rep];
			else if(char_Rep < 8) interrupt_Buffer[char_Rep] = ' ';
			else if(char_Rep > 8){
				if(new_Name[dot_Pos+char_Rep-8] != 0)interrupt_Buffer[char_Rep-1] = new_Name[dot_Pos+char_Rep-8];
				else interrupt_Buffer[char_Rep-1] = ' ';
				}
			}
		}
		dir_Info_Read();
		write_Ofset_Block(interrupt_Buffer,0,11);
		dir_Info_Save();
		set_Time(MODIFY);
		if(ch376_status_update==USB_INT_SUCCESS){strcpy(recent_Path_Record,temp_buffer); return YES;}
		else return NO;
	}
	return NO;
}




void CH376::init_Ext_Int(uint8_t status){//MCU External Interrupt is enabled to receive CH376 interrupt requests.
	
	INTR_PORT |= (1<<INTR_NO);							// Enable the pull-up resistor
	if(status)EXT_INT_MSK_REG |= (1<<INTR_NO);			// Turn on the interrupt
	else EXT_INT_MSK_REG &= ~(1<<INTR_NO);				// Turn off the interrupt
	sei();
}
