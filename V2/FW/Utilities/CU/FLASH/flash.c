#include "flash.h"

uint8_t flash_init(void)
{
  CU_MX25L1606E_LowLevel_Init();
}

void flash_read_ID(uint8_t *buf)
{
  uint8_t cmd=SERIAL_FLASH_CMD_READ_ID;
  CU_MX25L1606E_CS(FLASH_CS_ASSERTED);
  CU_MX25L1606E_transfer(&cmd,1);
  CU_MX25L1606E_transfer(buf,3);
  CU_MX25L1606E_CS(FLASH_CS_RELEASED);
}

uint8_t flash_read_Status(void)
{
  uint8_t cmd=SERIAL_FLASH_CMD_READ_STATREG;
  uint8_t status;
  
  CU_MX25L1606E_CS(FLASH_CS_ASSERTED);
  CU_MX25L1606E_transfer(&cmd,1);
  CU_MX25L1606E_transfer(&status,1);
  CU_MX25L1606E_CS(FLASH_CS_RELEASED);
  return status;
}

uint8_t flash_read_Data(uint8_t *buf,uint32_t length, uint32_t addr)
{
  uint8_t cmd[4];
  cmd[0]=SERIAL_FLASH_CMD_READ_BYTES;
  cmd[1] = (addr>>16) & 0xFF;
  cmd[2] = (addr>>8) & 0xFF;
  cmd[3] = addr & 0xFF;
  
  CU_MX25L1606E_CS(FLASH_CS_ASSERTED);  
  CU_MX25L1606E_transfer(cmd,4);
  CU_MX25L1606E_transfer(*buf,length);
  CU_MX25L1606E_CS(FLASH_CS_RELEASED);
}

void flash_Write_Enable(void)
{
  uint8_t cmd=SERIAL_FLASH_CMD_WRITE_ENABLE;
  CU_MX25L1606E_CS(FLASH_CS_ASSERTED);
  CU_MX25L1606E_transfer(&cmd,1);
  CU_MX25L1606E_CS(FLASH_CS_RELEASED);
}

uint8_t flash_Write_Sector(uint8_t *buf,uint32_t length, uint32_t sector)
{
  uint8_t cmd[4];
  uint32_t addr=0x10000*sector;
  cmd[0]=SERIAL_FLASH_CMD_WRITE_BYTES;
  cmd[1] = (addr>>16) & 0xFF;
  cmd[2] = (addr>>8) & 0xFF;
  cmd[3] = addr & 0xFF;
  
  CU_MX25L1606E_CS(FLASH_CS_ASSERTED);  
  CU_MX25L1606E_transfer(cmd,4);
  CU_MX25L1606E_transfer(*buf,0xFFFF);
  CU_MX25L1606E_CS(FLASH_CS_RELEASED);
  
  do
  {
    vTaskDelay(50);	
  }
  while(flash_read_Status()&0x01);
}

uint8_t flash_Sector_Erase(uint32_t sector)
{
  uint8_t cmd[4];
  cmd[0]=SERIAL_FLASH_CMD_SECTOR_ERASE;
  cmd[1] = (((0x10000*sector)&0xFF0000)>>16);
  cmd[2] = (((0x10000*sector)&0xFF00)>>8);
  cmd[3] = (0x10000*sector)&0xFF;
  
  if(sector>511)
    sector=511;
  
  CU_MX25L1606E_CS(FLASH_CS_ASSERTED);  
  CU_MX25L1606E_transfer(cmd,4);
  CU_MX25L1606E_CS(FLASH_CS_RELEASED);
  
  do
  {
    vTaskDelay(200);	//typ 0.6s, max 3s in accordance to datasheet.... :-(
  }
  while(flash_read_Status()&0x80);
}




