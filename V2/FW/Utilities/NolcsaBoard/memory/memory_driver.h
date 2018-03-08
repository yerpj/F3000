#ifndef MEMORY_DRIVER_H_
#define MEMORY_DRIVER_H_

#include "stm32f2xx_spi.h"
#include "commonDefs.h"

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#define MEM_BUF_SIZE	(100)


#define FLASH_SPI_CS_LOW while (SPI_I2S_GetFlagStatus(FLASH_SPI, SPI_I2S_FLAG_TXE) == RESET);GPIO_ResetBits(FLASH_SPI_CS_GPIO_PORT, FLASH_SPI_CS_PIN)
#define FLASH_SPI_CS_HIGH GPIO_SetBits(FLASH_SPI_CS_GPIO_PORT, FLASH_SPI_CS_PIN)

//Instruction set
#define SERIAL_FLASH_CMD_WRITE_ENABLE	0x06
#define SERIAL_FLASH_CMD_WRITE_DISABLE	0x04
#define SERIAL_FLASH_CMD_READ_ID		0x9F
#define SERIAL_FLASH_CMD_READ_STATREG	0x05
//#define SERIAL_FLASH_CMD_WRITE_STATREG	0x01
#define SERIAL_FLASH_CMD_READ_BYTES		0x03
#define SERIAL_FLASH_CMD_WRITE_BYTES	0x02
#define SERIAL_FLASH_CMD_SECTOR_ERASE	0xD8
#define SERIAL_FLASH_CMD_BULK_ERASE		0xC7
#define SERIAL_FLASH_CMD_DEEP_POWERDOWN	0xB9


void Flash_SPI_buffer_transfer(uint8_t *buffer, uint32_t length);
uint8_t Flash_SPI_byte_transfer(uint8_t txbyte);
void Memory_init(void);
void Memory_ON(void);
void Memory_OFF(void);
void Memory_write_enable(void);
void Memory_write_disable(void);
uint8_t Memory_is_here(void);
void Memory_read_ID(uint8_t *buf);
uint8_t Memory_read_status(void);
void Memory_read(uint8_t *buf, uint32_t length, uint32_t address);
void Memory_read_sector(uint8_t *buf, uint32_t sector);
void Memory_write(uint8_t *buf, uint32_t length, uint32_t address);
void Memory_write_sector(uint8_t *buf, uint32_t sector);
void Memory_sector_erase(uint8_t sector);
void Memory_bulk_erase(void);
void Memory_ToDeepPowerDown(void);
void Memory_update(uint8_t *buffer);



#endif /*MEMORY_DRIVER_H_*/
