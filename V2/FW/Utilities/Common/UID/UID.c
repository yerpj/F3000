#include "UID.h"

uint8_t UID_length=0;
uint8_t *UID_base_address;
uint8_t UID_default[8]={0x08,0x07,0x19,0x87,0xDE,0xAD,0xBE,0xEF};

/*
The user should define those two DEFINES with correct values
#define UID_ADDRESS_BASE (uint8_t*)(0x1FFF7A10)
#define UID_BYTE_SIZE   (12)
*/
void UID_Init(uint8_t *UID_base, uint8_t UID_size)
{
  UID_length = UID_size;
  UID_base_address=UID_base;
}

void UID_get(uint8_t *UID)
{
  uint8_t i;
  for(i=0;i<UID_length;i++)
  {
    UID[i]=UID_base_address[i]; 
  } 
}

void UID_getUID(uint8_t *UID)
{
uint8_t i;
  if(UID_length>=8)
  {
    for(i=0;i<8;i++)
      UID[i]=UID_base_address[i]; 
  }
  else
  {
    for(i=0;i<UID_length;i++)
      UID[i]=UID_base_address[i]; 
    for(i=UID_length;i<8;i++)
      UID[i]=UID_default[i]; 
  }
}

void UID_getNXSFormat(uint8_t *UID12)
{
  uint8_t i,j=0;
  for(i=0;i<3;i++)
  {
    j=i<<2;
    UID12[11-j]=UID_base_address[j+3];
    UID12[11-(j+1)]=UID_base_address[j+2];
    UID12[11-(j+2)]=UID_base_address[j+1];
    UID12[11-(j+3)]=UID_base_address[j];
  }
}

void EUI64_getNXSFormat(uint8_t *EUI64)
{
  uint8_t i=0;
  uint8_t UID12[12];
  UID_getNXSFormat(UID12);
  for(i=0;i<4;i++)
    EUI64[i]=UID12[i];  //4 first bytes come directly from UID
  for(;i<8;i++)
    EUI64[i]=UID12[11-i+4];  //4 following bytes are UID MSB swapped
}
