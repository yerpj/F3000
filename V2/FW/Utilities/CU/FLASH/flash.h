#ifndef __FLASH_H__
#define __FLASH_H__
#include "stm32f2xx.h"

#define FLASH_CS_ASSERTED       0x01
#define FLASH_CS_RELEASED       0x00

/*  SPI Flash supported commands */  

#define SERIAL_FLASH_CMD_WRITE_ENABLE	        0x06
#define SERIAL_FLASH_CMD_WRITE_DISABLE	        0x04
#define SERIAL_FLASH_CMD_READ_ID		0x9F
#define SERIAL_FLASH_CMD_READ_STATREG	        0x05
//#define SERIAL_FLASH_CMD_WRITE_STATREG	0x01
#define SERIAL_FLASH_CMD_READ_BYTES		0x03
#define SERIAL_FLASH_CMD_WRITE_BYTES	        0x02
#define SERIAL_FLASH_CMD_SECTOR_ERASE	        0x20
#define SERIAL_FLASH_CMD_BULK_ERASE		0xC7
#define SERIAL_FLASH_CMD_DEEP_POWERDOWN	        0xB9
  
/* MX25L1606E SPI Flash memory organization */
#define FLASH_NUM_SECTORS                       511     //number of sectors
#define FLASH_SECTOR_SIZE                       4095    //bytes in one sector

/* Exported functions ------------------------------------------------------- */
uint8_t flash_init(void);
void flash_read_ID(uint8_t *buf);
uint8_t flash_read_Status(void);
uint8_t flash_read_Data(uint8_t *buf,uint32_t length, uint32_t addr);
void flash_Write_Enable(void);
uint8_t flash_Write_Page(uint8_t *buf,uint32_t length, uint32_t sector);
uint8_t flash_Sector_Erase(uint32_t sector);

#endif /* __FLASH_H__ */
