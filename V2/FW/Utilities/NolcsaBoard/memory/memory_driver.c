#include "memory_driver.h"

uint8_t mem_is_on=0;
extern unsigned char Host_received_message_lock;


uint8_t Flash_SPI_byte_transfer(uint8_t txbyte)
{
  uint8_t rxbuf;
  FLASH_SPI->DR = txbyte;
  //while (SPI_I2S_GetFlagStatus(FLASH_SPI, SPI_I2S_FLAG_TXE) == RESET);//tant que pas vide
  while (SPI_I2S_GetFlagStatus(FLASH_SPI, SPI_I2S_FLAG_RXNE) == RESET);//tant que vide
  rxbuf = FLASH_SPI->DR;
  //while (GPIO_ReadInputDataBit(FLASH_SPI,CC1101_SPI_SCK_PIN));
  while (SPI_I2S_GetFlagStatus(FLASH_SPI, SPI_I2S_FLAG_BSY));
  while (SPI_I2S_GetFlagStatus(FLASH_SPI, SPI_I2S_FLAG_TXE) == RESET);//tant que pas vide
  return rxbuf;
}

void Flash_SPI_buffer_transfer(uint8_t *buffer, uint32_t length)
{
  uint32_t count;
  for(count=0;count<length;count++)
  {
    FLASH_SPI->DR = buffer[count];
    while (SPI_I2S_GetFlagStatus(FLASH_SPI, SPI_I2S_FLAG_RXNE) == RESET);//tant que vide
    buffer[count] = FLASH_SPI->DR;
    while (SPI_I2S_GetFlagStatus(FLASH_SPI, SPI_I2S_FLAG_BSY));
    while (SPI_I2S_GetFlagStatus(FLASH_SPI, SPI_I2S_FLAG_TXE) == RESET);//tant que pas vide
  }
}

void Memory_init(void)
{
}

void Memory_ON(void)
{
  if(!mem_is_on)
  {
    FLASH_SPI_CS_HIGH;
    vTaskDelay(10);			// to be sure memory is initialized 
    mem_is_on=1;
  }
}

void Memory_OFF(void)
{
  if(mem_is_on)
  {
    FLASH_SPI_CS_HIGH;
    mem_is_on=0;	
  }						
}

void Memory_write_enable(void)
{
  if(mem_is_on)
  {
    FLASH_SPI_CS_LOW;
    Flash_SPI_byte_transfer(SERIAL_FLASH_CMD_WRITE_ENABLE);
    FLASH_SPI_CS_HIGH;
  }
}

void Memory_write_disable(void)
{
  if(mem_is_on)
  {
    FLASH_SPI_CS_LOW;
    Flash_SPI_byte_transfer(SERIAL_FLASH_CMD_WRITE_DISABLE);
    FLASH_SPI_CS_HIGH;
  }
}

uint8_t Memory_is_here(void)
{
  uint8_t buf[20];
  buf[0]=0;//force to zero before asking the memory
  Memory_read_ID(buf);
  if(buf[0])
    return 1;
  else
    return 0;
}

void Memory_read_ID(uint8_t *buf)
{
  if(mem_is_on)
  {
    FLASH_SPI_CS_LOW;
    Flash_SPI_byte_transfer(SERIAL_FLASH_CMD_READ_ID);
    Flash_SPI_buffer_transfer(buf,3);
  }
}
uint8_t Memory_read_status(void)
{
  uint8_t rxbyte;
  if(mem_is_on)
  {
    FLASH_SPI_CS_LOW;
    Flash_SPI_byte_transfer(SERIAL_FLASH_CMD_READ_STATREG);
    rxbyte=Flash_SPI_byte_transfer(0);
    FLASH_SPI_CS_HIGH;
    return rxbyte;
  }
  return NULL;
}

void Memory_read_sector(uint8_t *buf, uint32_t sector)
{
  Memory_read(buf,0xFFFF,0x10000*sector);
}

void Memory_read(uint8_t *buf, uint32_t length, uint32_t address)
{
  uint8_t cmd[4];
  if(mem_is_on)
  {
    FLASH_SPI_CS_LOW;
    cmd[0] = SERIAL_FLASH_CMD_READ_BYTES;
    cmd[1] = (address>>16) & 0xFF;
    cmd[2] = (address>>8) & 0xFF;
    cmd[3] = address & 0xFF;
    Flash_SPI_buffer_transfer(cmd,4);
    Flash_SPI_buffer_transfer(buf,length);
    FLASH_SPI_CS_HIGH;
  }
}

void Memory_write_sector(uint8_t *buf, uint32_t sector)
{
  Memory_write(buf,0xFFFF,0x10000*sector);
}

void Memory_write(uint8_t *buf, uint32_t length, uint32_t address)
{
  uint8_t cmd[4];
  if(mem_is_on)
  {
    FLASH_SPI_CS_LOW;
    cmd[0] = SERIAL_FLASH_CMD_WRITE_BYTES;
    cmd[1] = (address>>16) & 0xFF;
    cmd[2] = (address>>8) & 0xFF;
    cmd[3] = address & 0xFF;
    Flash_SPI_buffer_transfer(cmd,4);
    Flash_SPI_buffer_transfer(buf,length);
    FLASH_SPI_CS_HIGH;
  }
}

void Memory_sector_erase(uint8_t sector)
{
  uint8_t cmd[4];
  //uint8_t WIP;
  if(mem_is_on)
  {
    FLASH_SPI_CS_LOW;
    cmd[0] = SERIAL_FLASH_CMD_SECTOR_ERASE;
    cmd[1] = (((0x10000*sector)&0xFF0000)>>16);
    cmd[2] = (((0x10000*sector)&0xFF00)>>8);
    cmd[3] = (0x10000*sector)&0xFF;
    Flash_SPI_buffer_transfer(cmd,4);
    FLASH_SPI_CS_HIGH;
    do
    {
      vTaskDelay(200);	//typ 0.6s, max 3s in accordance to datasheet.... :-(
    }
    while(Memory_read_status()&0x80);
    vTaskDelay(10);	
  }
}

void Memory_bulk_erase(void)
{
  if(mem_is_on)
  {
    FLASH_SPI_CS_LOW;
    Flash_SPI_byte_transfer(SERIAL_FLASH_CMD_BULK_ERASE);
    FLASH_SPI_CS_HIGH;
    do
    {
      vTaskDelay(1000);	//typ 8s, max 20s in accordance to datasheet.... :-(
    }
    while(Memory_read_status()&0x80);
    vTaskDelay(10);	
  }
}

void Memory_ToDeepPowerDown(void)
{
  if(mem_is_on)
  {
    FLASH_SPI_CS_LOW;
    Flash_SPI_byte_transfer(SERIAL_FLASH_CMD_DEEP_POWERDOWN);
    FLASH_SPI_CS_HIGH;
  }
}
