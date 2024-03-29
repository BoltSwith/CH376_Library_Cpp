# C-library-for-CH376-USB-Host-microSD-MMC-and-Card-Reader-controller-chip.
This CH376 C++ Library is an implementation of basic functions used to manage the file system (FAT12, FAT16 and FAT32) of USB flash drives, MMC and microSD cards, Hard Disk drives and Card Readers.
## Chip and Modules
First is photo of the chip and next is the most common module in the market which is quite cheap to acquire.
![Alt text](Ch376_and_Modules/CH376S_IC.jpg?raw=true "CH376")
![Alt text](Ch376_and_Modules/Module_1.jpg?raw=true "Common Module")

## Features and Notes:
1. This library is written in C++. The program will very likely not compile on a C compiler because the library contains C++ specific statements and declarations. 
2. The CH376 chip has two variants, viz. CH376s and CH376t. This library was tested on the CH376s variant. Little or no adjustment are needed to adapt the library to the CH376t variant.
3. The library was developed on the Atmel Studio 7 IDE and the target MCU was the AVR's Atmega2560. With little or no adjustment, the library should compile on the WinAVR IDE and the likes.
The library maybe used to develop projects based on the C++ language such as the PIC or ARM based projects. This is done by simply replacing the AVR specific #include files and Macro definitions with user's platform-specific files and Macros.
4. The CH376 IC is designed to function as a USB Device Controller (controlling devices like printers and bluetooths) and USB Host controller (Mass Storage Media controller). However, this library only supports the USB Host Controller function. For other uses, see the datasheet of the chip.
5. The library is designed to use least amount of RAM without compromising on speed. Minimum RAM and ROM (MCU Flash Memory) requirements are 2kb and 5kb respectively. CH376 SCK (Hardware SPI) was clocked at 4MHz and 125kHz during testing without any recorded flaws. Data rate (SCK frequency) above 4MHz have not been tested at the time of this writing.

## Versions
v1.0.2 Oct 10, 2019.
- fixed the file_Dir_Rename() routine to rename files with single or double character extension.
- update some functions/routines to generate proper error code when a command fails in the routine.


v1.0.1 Oct 9, 2019.
- Supports SPI mode only (Hardware SPI).
- Minimum of 5 communication lines between MCU and CH376 are required. These are MOSI, MISO, SCK, CS (Chip_Select), EXT_INT (MCU External Interrupt). An additiional line is recommended for reliablity, viz. the BZ (Busy) line. See source code and datasheet for more instructions on the use of this line.
- Ground the WR# and RD# pins before and after power-up of CH376 to enable SPI mode. See CH376 datasheet for Power Supply circuitry of CH376. 
- Supports only short name files. File and directory name should not exceed 8 characters. File extension should not exceed 3 characters.
  File or directory name and file extension characters should all be UPPERCASE. 
