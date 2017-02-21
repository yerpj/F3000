#include "flash.h"

uint8_t flash_init(void)
{
  uint8_t ID[3];
  CU_MX25L1606E_LowLevel_Init();
  flash_read_ID(ID);
  if( (ID[0]==0) && (ID[1]==0) && (ID[2]==0) )
    return 1;
  return 0;
}

void flash_read_ID(uint8_t *buf)
{
  uint8_t cmd=SERIAL_FLASH_CMD_READ_ID;
  CU_MX25L1606E_CS(FLASH_CS_ASSERTED);
  CU_MX25L1606E_transfer(&cmd,1,0);
  CU_MX25L1606E_transfer(buf,3,0);
  CU_MX25L1606E_CS(FLASH_CS_RELEASED);
}

uint8_t flash_read_Status(void)
{
  uint8_t cmd=SERIAL_FLASH_CMD_READ_STATREG;
  uint8_t status;
  
  CU_MX25L1606E_CS(FLASH_CS_ASSERTED);
  CU_MX25L1606E_transfer(&cmd,1,0);
  CU_MX25L1606E_transfer(&status,1,0);
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
  CU_MX25L1606E_transfer(cmd,4,0);
  CU_MX25L1606E_transfer(buf,length,0);
  CU_MX25L1606E_CS(FLASH_CS_RELEASED);
}

void flash_Write_Enable(void)
{
  uint8_t cmd=SERIAL_FLASH_CMD_WRITE_ENABLE;
  CU_MX25L1606E_CS(FLASH_CS_ASSERTED);
  CU_MX25L1606E_transfer(&cmd,1,0);
  CU_MX25L1606E_CS(FLASH_CS_RELEASED);
}

uint8_t flash_Write_Page(uint8_t *buf,uint32_t length, uint32_t sector)
{
  uint8_t cmd[4];
  uint32_t addr=0x1000*sector;
  uint16_t len=length>256?256:length;
  
  cmd[0]=SERIAL_FLASH_CMD_WRITE_BYTES;
  cmd[1] = (addr>>16) & 0xFF;
  cmd[2] = (addr>>8) & 0xFF;
  cmd[3] = addr & 0xFF;
  
  CU_MX25L1606E_CS(FLASH_CS_ASSERTED);  
  CU_MX25L1606E_transfer(cmd,4,0);
  CU_MX25L1606E_transfer(buf,length,0);
  CU_MX25L1606E_CS(FLASH_CS_RELEASED);
  //flash_read_Status();
  
  do
  {
    vTaskDelay(50);	
  }
  while(flash_read_Status()&0x01);
}

uint8_t flash_Sector_Erase(uint32_t sector)
{
  uint8_t cmd[4];
  uint8_t status;
  if(sector>FLASH_NUM_SECTORS)
    return 1;
  cmd[0]=SERIAL_FLASH_CMD_SECTOR_ERASE;
  cmd[1] = (((0x1000*sector)&0xFF0000)>>16);
  cmd[2] = (((0x1000*sector)&0xFF00)>>8);
  cmd[3] = (0x1000*sector)&0xFF;

  CU_MX25L1606E_CS(FLASH_CS_ASSERTED);  
  CU_MX25L1606E_transfer(cmd,4,1);
  //CS released within "transfer function"
  do
  {
    vTaskDelay(10);	//typ 40ms
  }
  while(flash_read_Status()&0x01);
  return 0;
}





