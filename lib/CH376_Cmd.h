#ifndef _CH376_UTIL_H
#define _CH376_UTIL_H

#define MODE_HOST_0 0x05
#define MODE_HOST_1 0x06
#define MODE_HOST_2 0x07
#define MODE_HOST_3 0X03

////////////CH376 Commands/////////
#define	CH376_DAT_BLOCK_LEN	0x40			/* USBµ¥¸öÊý¾Ý°ü, Êý¾Ý¿éµÄ×î´ó³¤¶È, Ä¬ÈÏ»º³åÇøµÄ³¤¶È */

#define	CMD01_GET_IC_VER	0x01			/* »ñÈ¡Ð¾Æ¬¼°¹Ì¼þ°æ±¾ */

#define	CMD21_SET_BAUDRATE	0x02			/* ´®¿Ú·½Ê½: ÉèÖÃ´®¿ÚÍ¨Ñ¶²¨ÌØÂÊ(ÉÏµç»òÕß¸´Î»ºóµÄÄ¬ÈÏ²¨ÌØÂÊÎª9600bps,ÓÉD4/D5/D6Òý½ÅÑ¡Ôñ) */

#define	CMD00_ENTER_SLEEP	0x03			/* ½øÈëË¯Ãß×´Ì¬ */

#define	CMD00_RESET_ALL		0x05			/* Ö´ÐÐÓ²¼þ¸´Î» */

#define	CMD11_CHECK_EXIST	0x06			/* ²âÊÔÍ¨Ñ¶½Ó¿ÚºÍ¹¤×÷×´Ì¬ */

#define	CMD20_CHK_SUSPEND	0x0B			/* Éè±¸·½Ê½: ÉèÖÃ¼ì²éUSB×ÜÏß¹ÒÆð×´Ì¬µÄ·½Ê½ */

#define	CMD20_SET_SDO_INT	0x0B			/* SPI½Ó¿Ú·½Ê½: ÉèÖÃSPIµÄSDOÒý½ÅµÄÖÐ¶Ï·½Ê½ */

#define	CMD14_GET_FILE_SIZE	0x0C			/* Ö÷»úÎÄ¼þÄ£Ê½: »ñÈ¡µ±Ç°ÎÄ¼þ³¤¶È */

#define	CMD50_SET_FILE_SIZE	0x0D			/* Ö÷»úÎÄ¼þÄ£Ê½: ÉèÖÃµ±Ç°ÎÄ¼þ³¤¶È */

#define	CMD11_SET_USB_MODE	0x15			/* ÉèÖÃUSB¹¤×÷Ä£Ê½ */

#define	CMD01_GET_STATUS	0x22			/* »ñÈ¡ÖÐ¶Ï×´Ì¬²¢È¡ÏûÖÐ¶ÏÇëÇó */

#define	CMD00_UNLOCK_USB	0x23			/* Éè±¸·½Ê½: ÊÍ·Åµ±Ç°USB»º³åÇø */

#define	CMD01_RD_USB_DATA0	0x27			/* ´Óµ±Ç°USBÖÐ¶ÏµÄ¶Ëµã»º³åÇø»òÕßÖ÷»ú¶ËµãµÄ½ÓÊÕ»º³åÇø¶ÁÈ¡Êý¾Ý¿é */

#define	CMD01_RD_USB_DATA	0x28			/* Éè±¸·½Ê½: ´Óµ±Ç°USBÖÐ¶ÏµÄ¶Ëµã»º³åÇø¶ÁÈ¡Êý¾Ý¿é, ²¢ÊÍ·Å»º³åÇø, Ïàµ±ÓÚ CMD01_RD_USB_DATA0 + CMD00_UNLOCK_USB */

#define	CMD10_WR_USB_DATA7	0x2B			/* Éè±¸·½Ê½: ÏòUSB¶Ëµã2µÄ·¢ËÍ»º³åÇøÐ´ÈëÊý¾Ý¿é */

#define	CMD10_WR_HOST_DATA	0x2C			/* ÏòUSBÖ÷»ú¶ËµãµÄ·¢ËÍ»º³åÇøÐ´ÈëÊý¾Ý¿é */

#define	CMD01_WR_REQ_DATA	0x2D			/* ÏòÄÚ²¿Ö¸¶¨»º³åÇøÐ´ÈëÇëÇóµÄÊý¾Ý¿é */

#define	CMD20_WR_OFS_DATA	0x2E			/* ÏòÄÚ²¿»º³åÇøÖ¸¶¨Æ«ÒÆµØÖ·Ð´ÈëÊý¾Ý¿é */

#define	CMD10_SET_FILE_NAME	0x2F			/* Ö÷»úÎÄ¼þÄ£Ê½: ÉèÖÃ½«Òª²Ù×÷µÄÎÄ¼þµÄÎÄ¼þÃû */

#define	CMD0H_DISK_CONNECT	0x30			/* Ö÷»úÎÄ¼þÄ£Ê½/²»Ö§³ÖSD¿¨: ¼ì²é´ÅÅÌÊÇ·ñÁ¬½Ó */

#define	CMD0H_DISK_MOUNT	0x31			/* Ö÷»úÎÄ¼þÄ£Ê½: ³õÊ¼»¯´ÅÅÌ²¢²âÊÔ´ÅÅÌÊÇ·ñ¾ÍÐ÷ */

#define	CMD0H_FILE_OPEN		0x32			/* Ö÷»úÎÄ¼þÄ£Ê½: ´ò¿ªÎÄ¼þ»òÕßÄ¿Â¼(ÎÄ¼þ¼Ð),»òÕßÃ¶¾ÙÎÄ¼þºÍÄ¿Â¼(ÎÄ¼þ¼Ð) */

#define	CMD0H_FILE_ENUM_GO	0x33			/* Ö÷»úÎÄ¼þÄ£Ê½: ¼ÌÐøÃ¶¾ÙÎÄ¼þºÍÄ¿Â¼(ÎÄ¼þ¼Ð) */

#define	CMD0H_FILE_CREATE	0x34			/* Ö÷»úÎÄ¼þÄ£Ê½: ÐÂ½¨ÎÄ¼þ,Èç¹ûÎÄ¼þÒÑ¾­´æÔÚÄÇÃ´ÏÈÉ¾³ý */

#define	CMD0H_FILE_ERASE	0x35			/* Ö÷»úÎÄ¼þÄ£Ê½: É¾³ýÎÄ¼þ,Èç¹ûÒÑ¾­´ò¿ªÔòÖ±½ÓÉ¾³ý,·ñÔò¶ÔÓÚÎÄ¼þ»áÏÈ´ò¿ªÔÙÉ¾³ý,×ÓÄ¿Â¼±ØÐëÏÈ´ò¿ª */

#define	CMD1H_FILE_CLOSE	0x36			/* Ö÷»úÎÄ¼þÄ£Ê½: ¹Ø±Õµ±Ç°ÒÑ¾­´ò¿ªµÄÎÄ¼þ»òÕßÄ¿Â¼(ÎÄ¼þ¼Ð) */

#define	CMD1H_DIR_INFO_READ	0x37			/* Ö÷»úÎÄ¼þÄ£Ê½: ¶ÁÈ¡ÎÄ¼þµÄÄ¿Â¼ÐÅÏ¢ */

#define	CMD0H_DIR_INFO_SAVE	0x38			/* Ö÷»úÎÄ¼þÄ£Ê½: ±£´æÎÄ¼þµÄÄ¿Â¼ÐÅÏ¢ */

#define	CMD4H_BYTE_LOCATE	0x39			/* Ö÷»úÎÄ¼þÄ£Ê½: ÒÔ×Ö½ÚÎªµ¥Î»ÒÆ¶¯µ±Ç°ÎÄ¼þÖ¸Õë */

#define	CMD2H_BYTE_READ		0x3A			/* Ö÷»úÎÄ¼þÄ£Ê½: ÒÔ×Ö½ÚÎªµ¥Î»´Óµ±Ç°Î»ÖÃ¶ÁÈ¡Êý¾Ý¿é */

#define	CMD0H_BYTE_RD_GO	0x3B			/* Ö÷»úÎÄ¼þÄ£Ê½: ¼ÌÐø×Ö½Ú¶Á */

#define	CMD2H_BYTE_WRITE	0x3C			/* Ö÷»úÎÄ¼þÄ£Ê½: ÒÔ×Ö½ÚÎªµ¥Î»Ïòµ±Ç°Î»ÖÃÐ´ÈëÊý¾Ý¿é */

#define	CMD0H_BYTE_WR_GO	0x3D			/* Ö÷»úÎÄ¼þÄ£Ê½: ¼ÌÐø×Ö½ÚÐ´ */

#define	CMD0H_DISK_CAPACITY	0x3E			/* Ö÷»úÎÄ¼þÄ£Ê½: ²éÑ¯´ÅÅÌÎïÀíÈÝÁ¿ */

#define	CMD0H_DISK_QUERY	0x3F			/* Ö÷»úÎÄ¼þÄ£Ê½: ²éÑ¯´ÅÅÌ¿Õ¼äÐÅÏ¢ */

#define	CMD0H_DIR_CREATE	0x40			/* Ö÷»úÎÄ¼þÄ£Ê½: ÐÂ½¨Ä¿Â¼(ÎÄ¼þ¼Ð)²¢´ò¿ª,Èç¹ûÄ¿Â¼ÒÑ¾­´æÔÚÄÇÃ´Ö±½Ó´ò¿ª */

#define	CMD4H_SEC_LOCATE	0x4A			/* Ö÷»úÎÄ¼þÄ£Ê½: ÒÔÉÈÇøÎªµ¥Î»ÒÆ¶¯µ±Ç°ÎÄ¼þÖ¸Õë */

#define	CMD1H_SEC_READ		0x4B			/* Ö÷»úÎÄ¼þÄ£Ê½/²»Ö§³ÖSD¿¨: ÒÔÉÈÇøÎªµ¥Î»´Óµ±Ç°Î»ÖÃ¶ÁÈ¡Êý¾Ý¿é */

#define	CMD1H_SEC_WRITE		0x4C			/* Ö÷»úÎÄ¼þÄ£Ê½/²»Ö§³ÖSD¿¨: ÒÔÉÈÇøÎªµ¥Î»ÔÚµ±Ç°Î»ÖÃÐ´ÈëÊý¾Ý¿é */

#define	CMD0H_DISK_BOC_CMD	0x50			/* Ö÷»ú·½Ê½/²»Ö§³ÖSD¿¨: ¶ÔUSB´æ´¢Æ÷Ö´ÐÐBulkOnly´«ÊäÐ­ÒéµÄÃüÁî */

#define	CMD5H_DISK_READ		0x54			/* Ö÷»ú·½Ê½/²»Ö§³ÖSD¿¨: ´ÓUSB´æ´¢Æ÷¶ÁÎïÀíÉÈÇø */

#define	CMD0H_DISK_RD_GO	0x55			/* Ö÷»ú·½Ê½/²»Ö§³ÖSD¿¨: ¼ÌÐøÖ´ÐÐUSB´æ´¢Æ÷µÄÎïÀíÉÈÇø¶Á²Ù×÷ */

#define	CMD5H_DISK_WRITE	0x56			/* Ö÷»ú·½Ê½/²»Ö§³ÖSD¿¨: ÏòUSB´æ´¢Æ÷Ð´ÎïÀíÉÈÇø */

#define	CMD0H_DISK_WR_GO	0x57			/* Ö÷»ú·½Ê½/²»Ö§³ÖSD¿¨: ¼ÌÐøÖ´ÐÐUSB´æ´¢Æ÷µÄÎïÀíÉÈÇøÐ´²Ù×÷ */

#define	CMD10_SET_USB_SPEED	0x04			/* ÉèÖÃUSB×ÜÏßËÙ¶È, ÔÚÃ¿´ÎCMD11_SET_USB_MODEÉèÖÃUSB¹¤×÷Ä£Ê½Ê±»á×Ô¶¯»Ö¸´µ½12MbpsÈ«ËÙ */

#define	CMD11_GET_DEV_RATE	0x0A			/* Ö÷»ú·½Ê½: »ñÈ¡µ±Ç°Á¬½ÓµÄUSBÉè±¸µÄÊý¾ÝËÙÂÊÀàÐÍ */

#define	CMD11_GET_TOGGLE	0x0A			/* »ñÈ¡OUTÊÂÎñµÄÍ¬²½×´Ì¬ */

#define	CMD11_READ_VAR8		0x0A			/* ¶ÁÈ¡Ö¸¶¨µÄ8Î»ÎÄ¼þÏµÍ³±äÁ¿ */

#define	CMD20_SET_RETRY		0x0B			/* Ö÷»ú·½Ê½: ÉèÖÃUSBÊÂÎñ²Ù×÷µÄÖØÊÔ´ÎÊý */

#define	CMD20_WRITE_VAR8	0x0B			/* ÉèÖÃÖ¸¶¨µÄ8Î»ÎÄ¼þÏµÍ³±äÁ¿ */

#define	CMD14_READ_VAR32	0x0C			/* ¶ÁÈ¡Ö¸¶¨µÄ32Î»ÎÄ¼þÏµÍ³±äÁ¿ */

#define	CMD50_WRITE_VAR32	0x0D			/* ÉèÖÃÖ¸¶¨µÄ32Î»ÎÄ¼þÏµÍ³±äÁ¿ */

#define	CMD01_DELAY_100US	0x0F			/* ÑÓÊ±100uS(´®¿Ú²»Ö§³Ö) */

#define	CMD40_SET_USB_ID	0x12			/* Éè±¸·½Ê½: ÉèÖÃUSB³§ÉÌVIDºÍ²úÆ·PID */

#define	CMD10_SET_USB_ADDR	0x13			/* ÉèÖÃUSBµØÖ· */

#define	CMD01_TEST_CONNECT	0x16			/* Ö÷»ú·½Ê½/²»Ö§³ÖSD¿¨: ¼ì²éUSBÉè±¸Á¬½Ó×´Ì¬ */

#define	CMD00_ABORT_NAK		0x17			/* Ö÷»ú·½Ê½: ·ÅÆúµ±Ç°NAKµÄÖØÊÔ */

#define	CMD10_SET_ENDP2		0x18			/* Éè±¸·½Ê½(´®¿Ú²»Ö§³Ö): ÉèÖÃUSB¶Ëµã0µÄ½ÓÊÕÆ÷ */

#define	CMD10_SET_ENDP3		0x19			/* Éè±¸·½Ê½(´®¿Ú²»Ö§³Ö): ÉèÖÃUSB¶Ëµã0µÄ·¢ËÍÆ÷ */

#define	CMD10_SET_ENDP4		0x1A			/* Éè±¸·½Ê½(´®¿Ú²»Ö§³Ö): ÉèÖÃUSB¶Ëµã1µÄ½ÓÊÕÆ÷ */

#define	CMD10_SET_ENDP5		0x1B			/* Éè±¸·½Ê½(´®¿Ú²»Ö§³Ö): ÉèÖÃUSB¶Ëµã1µÄ·¢ËÍÆ÷ */

#define	CMD10_SET_ENDP6		0x1C			/* ÉèÖÃUSB¶Ëµã2/Ö÷»ú¶ËµãµÄ½ÓÊÕÆ÷ */

#define	CMD10_SET_ENDP7		0x1D			/* ÉèÖÃUSB¶Ëµã2/Ö÷»ú¶ËµãµÄ·¢ËÍÆ÷ */

#define	CMD00_DIRTY_BUFFER	0x25			/* Ö÷»úÎÄ¼þÄ£Ê½: Çå³ýÄÚ²¿µÄ´ÅÅÌºÍÎÄ¼þ»º³åÇø */

#define	CMD10_WR_USB_DATA3	0x29			/* Éè±¸·½Ê½(´®¿Ú²»Ö§³Ö): ÏòUSB¶Ëµã0µÄ·¢ËÍ»º³åÇøÐ´ÈëÊý¾Ý¿é */

#define	CMD10_WR_USB_DATA5	0x2A			/* Éè±¸·½Ê½(´®¿Ú²»Ö§³Ö): ÏòUSB¶Ëµã1µÄ·¢ËÍ»º³åÇøÐ´ÈëÊý¾Ý¿é */

#define	CMD1H_CLR_STALL		0x41			/* Ö÷»ú·½Ê½: ¿ØÖÆ´«Êä-Çå³ý¶Ëµã´íÎó */

#define	CMD1H_SET_ADDRESS	0x45			/* Ö÷»ú·½Ê½: ¿ØÖÆ´«Êä-ÉèÖÃUSBµØÖ· */

#define	CMD1H_GET_DESCR		0x46			/* Ö÷»ú·½Ê½: ¿ØÖÆ´«Êä-»ñÈ¡ÃèÊö·û */

#define	CMD1H_SET_CONFIG	0x49			/* Ö÷»ú·½Ê½: ¿ØÖÆ´«Êä-ÉèÖÃUSBÅäÖÃ */

#define	CMD0H_AUTO_SETUP	0x4D			/* Ö÷»ú·½Ê½/²»Ö§³ÖSD¿¨: ×Ô¶¯ÅäÖÃUSBÉè±¸ */

#define	CMD2H_ISSUE_TKN_X	0x4E			/* Ö÷»ú·½Ê½: ·¢³öÍ¬²½ÁîÅÆ, Ö´ÐÐÊÂÎñ, ¸ÃÃüÁî¿É´úÌæ CMD10_SET_ENDP6/CMD10_SET_ENDP7 + CMD1H_ISSUE_TOKEN */

#define	CMD1H_ISSUE_TOKEN	0x4F			/* Ö÷»ú·½Ê½: ·¢³öÁîÅÆ, Ö´ÐÐÊÂÎñ, ½¨ÒéÓÃCMD2H_ISSUE_TKN_XÃüÁî */

#define	CMD0H_DISK_INIT		0x51			/* Ö÷»ú·½Ê½/²»Ö§³ÖSD¿¨: ³õÊ¼»¯USB´æ´¢Æ÷ */
/* Êä³öÖÐ¶Ï */

#define	CMD0H_DISK_RESET	0x52			/* Ö÷»ú·½Ê½/²»Ö§³ÖSD¿¨: ¿ØÖÆ´«Êä-¸´Î»USB´æ´¢Æ÷ */

#define	CMD0H_DISK_SIZE		0x53			/* Ö÷»ú·½Ê½/²»Ö§³ÖSD¿¨: »ñÈ¡USB´æ´¢Æ÷µÄÈÝÁ¿ */

#define	CMD0H_DISK_INQUIRY	0x58			/* Ö÷»ú·½Ê½/²»Ö§³ÖSD¿¨: ²éÑ¯USB´æ´¢Æ÷ÌØÐÔ */

#define	CMD0H_DISK_READY	0x59			/* Ö÷»ú·½Ê½/²»Ö§³ÖSD¿¨: ¼ì²éUSB´æ´¢Æ÷¾ÍÐ÷ */

#define	CMD0H_DISK_R_SENSE	0x5A			/* Ö÷»ú·½Ê½/²»Ö§³ÖSD¿¨: ¼ì²éUSB´æ´¢Æ÷´íÎó */

#define	CMD0H_RD_DISK_SEC	0x5B			/* Ö÷»úÎÄ¼þÄ£Ê½: ´Ó´ÅÅÌ¶ÁÈ¡Ò»¸öÉÈÇøµÄÊý¾Ýµ½ÄÚ²¿»º³åÇø */

#define	CMD0H_WR_DISK_SEC	0x5C			/* Ö÷»úÎÄ¼þÄ£Ê½: ½«ÄÚ²¿»º³åÇøµÄÒ»¸öÉÈÇøµÄÊý¾ÝÐ´Èë´ÅÅÌ */

#define	CMD0H_DISK_MAX_LUN	0x5D			/* Ö÷»ú·½Ê½: ¿ØÖÆ´«Êä-»ñÈ¡USB´æ´¢Æ÷×î´óÂß¼­µ¥ÔªºÅ */

#define	CMD_GET_IC_VER		CMD01_GET_IC_VER
#define	CMD_SET_BAUDRATE	CMD21_SET_BAUDRATE
#define	CMD_ENTER_SLEEP		CMD00_ENTER_SLEEP
#define	CMD_RESET_ALL		CMD00_RESET_ALL
#define	CMD_CHECK_EXIST		CMD11_CHECK_EXIST
#define	CMD_CHK_SUSPEND		CMD20_CHK_SUSPEND
#define	CMD_SET_SDO_INT		CMD20_SET_SDO_INT
#define	CMD_GET_FILE_SIZE	CMD14_GET_FILE_SIZE
#define	CMD_SET_FILE_SIZE	CMD50_SET_FILE_SIZE
#define	CMD_SET_USB_MODE	CMD11_SET_USB_MODE
#define	CMD_GET_STATUS		CMD01_GET_STATUS
#define	CMD_UNLOCK_USB		CMD00_UNLOCK_USB
#define	CMD_RD_USB_DATA0	CMD01_RD_USB_DATA0
#define	CMD_RD_USB_DATA		CMD01_RD_USB_DATA
#define	CMD_WR_USB_DATA7	CMD10_WR_USB_DATA7
#define	CMD_WR_HOST_DATA	CMD10_WR_HOST_DATA
#define	CMD_WR_REQ_DATA		CMD01_WR_REQ_DATA
#define	CMD_WR_OFS_DATA		CMD20_WR_OFS_DATA
#define	CMD_SET_FILE_NAME	CMD10_SET_FILE_NAME
#define	CMD_DISK_CONNECT	CMD0H_DISK_CONNECT
#define	CMD_DISK_MOUNT		CMD0H_DISK_MOUNT
#define	CMD_FILE_OPEN		CMD0H_FILE_OPEN
#define	CMD_FILE_ENUM_GO	CMD0H_FILE_ENUM_GO
#define	CMD_FILE_CREATE		CMD0H_FILE_CREATE
#define	CMD_FILE_ERASE		CMD0H_FILE_ERASE
#define	CMD_FILE_CLOSE		CMD1H_FILE_CLOSE
#define	CMD_DIR_INFO_READ	CMD1H_DIR_INFO_READ
#define	CMD_DIR_INFO_SAVE	CMD0H_DIR_INFO_SAVE
#define	CMD_BYTE_LOCATE		CMD4H_BYTE_LOCATE
#define	CMD_BYTE_READ		CMD2H_BYTE_READ
#define	CMD_BYTE_RD_GO		CMD0H_BYTE_RD_GO
#define	CMD_BYTE_WRITE		CMD2H_BYTE_WRITE
#define	CMD_BYTE_WR_GO		CMD0H_BYTE_WR_GO
#define	CMD_DISK_CAPACITY	CMD0H_DISK_CAPACITY
#define	CMD_DISK_QUERY		CMD0H_DISK_QUERY
#define	CMD_DIR_CREATE		CMD0H_DIR_CREATE
#define	CMD_SEC_LOCATE		CMD4H_SEC_LOCATE
#define	CMD_SEC_READ		CMD1H_SEC_READ
#define	CMD_SEC_WRITE		CMD1H_SEC_WRITE
#define	CMD_DISK_BOC_CMD	CMD0H_DISK_BOC_CMD
#define	CMD_DISK_READ		CMD5H_DISK_READ
#define	CMD_DISK_RD_GO		CMD0H_DISK_RD_GO
#define	CMD_DISK_WRITE		CMD5H_DISK_WRITE
#define	CMD_DISK_WR_GO		CMD0H_DISK_WR_GO
#define	CMD_SET_USB_SPEED	CMD10_SET_USB_SPEED
#define	CMD_GET_DEV_RATE	CMD11_GET_DEV_RATE
#define	CMD_GET_TOGGLE		CMD11_GET_TOGGLE
#define	CMD_READ_VAR8		CMD11_READ_VAR8
#define	CMD_SET_RETRY		CMD20_SET_RETRY
#define	CMD_WRITE_VAR8		CMD20_WRITE_VAR8
#define	CMD_READ_VAR32		CMD14_READ_VAR32
#define	CMD_WRITE_VAR32		CMD50_WRITE_VAR32
#define	CMD_DELAY_100US		CMD01_DELAY_100US
#define	CMD_SET_USB_ID		CMD40_SET_USB_ID
#define	CMD_SET_USB_ADDR	CMD10_SET_USB_ADDR
#define	CMD_TEST_CONNECT	CMD01_TEST_CONNECT
#define	CMD_ABORT_NAK		CMD00_ABORT_NAK
#define	CMD_SET_ENDP2		CMD10_SET_ENDP2
#define	CMD_SET_ENDP3		CMD10_SET_ENDP3
#define	CMD_SET_ENDP4		CMD10_SET_ENDP4
#define	CMD_SET_ENDP5		CMD10_SET_ENDP5
#define	CMD_SET_ENDP6		CMD10_SET_ENDP6
#define	CMD_SET_ENDP7		CMD10_SET_ENDP7
#define	CMD_DIRTY_BUFFER	CMD00_DIRTY_BUFFER
#define	CMD_WR_USB_DATA3	CMD10_WR_USB_DATA3
#define	CMD_WR_USB_DATA5	CMD10_WR_USB_DATA5
#define	CMD_CLR_STALL		CMD1H_CLR_STALL
#define	CMD_SET_ADDRESS		CMD1H_SET_ADDRESS
#define	CMD_GET_DESCR		CMD1H_GET_DESCR
#define	CMD_SET_CONFIG		CMD1H_SET_CONFIG
#define	CMD_AUTO_SETUP		CMD0H_AUTO_SETUP
#define	CMD_ISSUE_TKN_X		CMD2H_ISSUE_TKN_X
#define	CMD_ISSUE_TOKEN		CMD1H_ISSUE_TOKEN
#define	CMD_DISK_INIT		CMD0H_DISK_INIT
#define	CMD_DISK_RESET		CMD0H_DISK_RESET
#define	CMD_DISK_SIZE		CMD0H_DISK_SIZE
#define	CMD_DISK_INQUIRY	CMD0H_DISK_INQUIRY
#define	CMD_DISK_READY		CMD0H_DISK_READY
#define	CMD_DISK_R_SENSE	CMD0H_DISK_R_SENSE
#define	CMD_RD_DISK_SEC		CMD0H_RD_DISK_SEC
#define	CMD_WR_DISK_SEC		CMD0H_WR_DISK_SEC
#define	CMD_DISK_MAX_LUN	CMD0H_DISK_MAX_LUN

#define USB_RET_SUCCESS		0x51		//Operation successful
#define	USB_INT_SUCCESS		0x14			/* USB事务或者传输操作成功 */
#define	USB_INT_CONNECT		0x15			/* 检测到USB设备连接事件, 可能是新连接或者断开后重新连接 */
#define	USB_INT_DISCONNECT	0x16			/* 检测到USB设备断开事件 */
#define	USB_INT_BUF_OVER	0x17			/* USB传输的数据有误或者数据太多缓冲区溢出 */
#define	USB_INT_USB_READY	0x18			/* USB设备已经被初始化(已经分配USB地址) */
#define	USB_INT_DISK_READ	0x1D			/* USB存储器请求数据读出 */
#define	USB_INT_DISK_WRITE	0x1E			/* USB存储器请求数据写入 */
#define	USB_INT_DISK_ERR	0x1F			/* USB存储器操作失败 */

/* 以下状态代码用于主机文件模式下的文件系统错误码 */
#define ERR_RET_ABORT		0x5F			
#define	ERR_DISK_DISCON		0x82			/* 磁盘尚未连接,可能磁盘已经断开 */
#define	ERR_LARGE_SECTOR	0x84			/* 磁盘的扇区太大,只支持每扇区512字节 */
#define	ERR_TYPE_ERROR		0x92			/* 磁盘分区类型不支持,只支持FAT12/FAT16/BigDOS/FAT32,需要由磁盘管理工具重新分区 */
#define	ERR_BPB_ERROR		0xA1			/* 磁盘尚未格式化,或者参数错误,需要由WINDOWS采用默认参数重新格式化 */
#define	ERR_DISK_FULL		0xB1			/* 磁盘文件太满,剩余空间太少或者已经没有,需要磁盘整理 */
#define	ERR_FDT_OVER		0xB2			/* 目录(文件夹)内文件太多,没有空闲的目录项,FAT12/FAT16根目录下的文件数应该少于512个,需要磁盘整理 */
#define	ERR_FILE_CLOSE		0xB4			/* 文件已经关闭,如果需要使用,应该重新打开文件 */
#define	ERR_OPEN_DIR		0x41			/* 指定路径的目录(文件夹)被打开 */
#define	ERR_MISS_FILE		0x42			/* 指定路径的文件没有找到,可能是文件名称错误 */
#define	ERR_FOUND_NAME		0x43			/* 搜索到相匹配的文件名,或者是要求打开目录(文件夹)而实际结果却打开了文件 */
/* 以下文件系统错误码用于文件系统子程序 */
#define	ERR_MISS_DIR		0xB3			/* 指定路径的某个子目录(文件夹)没有找到,可能是目录名称错误 */
#define	ERR_LONG_BUF_OVER	0x48			/* 长文件缓冲区溢出 */
#define	ERR_LONG_NAME_ERR	0x49			/* 短文件名没有对应的长文件名或者长文件名错误 */
#define	ERR_NAME_EXIST		0x4A			/* 同名的短文件已经存在,建议重新生成另外一个短文件名 */

//***************OTHER PARTICULAR COMMANDS*************************
#define	VAR_FILE_SIZE		0x68
#define	VAR_DISK_STATUS		0x2B			/* Disk and file status in host file mode */

/*
#define	CMD_READ_VAR8		0x0A
#define	CMD_WRITE_VAR8		0x0B
#define CMD_READ_VAR32		0x0C
#define CMD_WRITE_VAR32		0x0D

#define	VAR_START_CLUSTER	0x60
#define	CMD_DISK_R_SENSE	0x5A
#define	VAR_FILE_DIR_INDEX	0x3B			/ * The index number of the current file directory information in the sector * /*/

#endif