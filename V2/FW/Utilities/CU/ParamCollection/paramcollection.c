#include "paramcollection.h"
#include "string.h"
#include "flash.h"
uint8_t PC_ParamNameTable[PC_NUMPARAM][PC_PARAM_NAME_LENGTH];

uint8_t PC_Init(void)
{
  uint32_t i;
  uint8_t tmp='Z';
  for(i=0;i<PC_NUMPARAM;i++)
  {
    PC_ParamNameTable[i][0]=0;
  }
  /*flash_Write_Enable();
  flash_Sector_Erase(0);
  flash_Write_Enable();
  flash_Write_Page(&tmp,1,0);
  flash_read_Data(&tmp,1,0);
  if(tmp!='Z')
    return 1;*/
  PC_AddParam("LED_I");
  PC_AddParam("AUTO_GU_BT");//AUTO mode, GEAR UP, BLANKING TIME: time between 2 consecutive GEAR_UP actions
  return 0;
}

uint8_t PC_AddParam(uint8_t *name)
{
  uint32_t i=0,j=0;
  while(i<PC_NUMPARAM)
  {
    if(PC_ParamNameTable[i][0]==0 )
    {
      while(name[j]!='\0')
      {
        PC_ParamNameTable[i][j]=name[j];
        j++;
      }
      return 0;
    }
    else
      i++;
  }
  return 1;
}

uint8_t PC_GetParam(uint8_t *data,uint8_t *name)
{
  uint32_t i=0;
  while(i<PC_NUMPARAM)
  {
    if(strstr(name,&PC_ParamNameTable[i][0])>0)
    {
      flash_read_Data(data,PC_PARAM_LENGTH,0x1000*i);
      return 0;
    }
    else
      i++;
  }
  return 1;
}

uint8_t PC_SetParam(uint8_t *data,uint8_t *name)
{
  uint32_t i=0;
  while(i<PC_NUMPARAM)
  {
    if(strstr(name,&PC_ParamNameTable[i][0])>0)
    {
      flash_Write_Enable();
      flash_Sector_Erase(i);
      flash_Write_Enable();
      flash_Write_Page(data,PC_PARAM_LENGTH,i);
      return 0;
    }
    else
      i++;
  }
  return 1;
}
