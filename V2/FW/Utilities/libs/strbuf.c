#include "strbuf.h"

void buffer_init(uint8_t *buf,uint8_t val,uint32_t len)
{
  uint32_t i;
  for(i=0;i<len;i++)
    buf[i]=val;
}

void buffer_copy(uint8_t *dst,uint8_t *src,uint8_t len)
{
  uint8_t i;
  for(i=0;i<len;i++)
    dst[i]=src[i];
}

// A simple AtoI() function
int32_t AtoI(uint8_t *str)
{
    int32_t res = 0,i; // Initialize result

    // Iterate through all characters of input string and update result
    for (i = 0; str[i] != '\0'; ++i)
    {
      if(i==0)
      {
        if(str[0]=='-')
          res=-1;
      }
      res = res*10 + (str[i] - '0');
    }
    // return result.
    return res;
}

uint8_t isASCII(uint8_t *buf,uint32_t len)
{
  uint8_t i=0;
  for(i=0;i<len;i++)
  {
    if(buf[i]>127)
       return 0;
  }
  return 1;
}

void HexaASCIItoByteArray(uint8_t *ByteArray, uint8_t *HexaCodedASCII,uint8_t size)
{
	uint8_t i;
	for(i=0;i<(size<<1);i+=2)
	{
		if(HexaCodedASCII[i]>'/' && HexaCodedASCII[i]<':')
		{
			ByteArray[(i>>1)]=(HexaCodedASCII[i]-'0')<<4;	//old index was "size-1-(i>>1)"
		}
		else if(HexaCodedASCII[i+1]>'@' && HexaCodedASCII[i+1]<'G')
		{
			ByteArray[(i>>1)]=(HexaCodedASCII[i]-0x37)<<4;
		}
		else if(HexaCodedASCII[i+1]>0x60 && HexaCodedASCII[i+1]<'g')
		{
			ByteArray[(i>>1)]=(HexaCodedASCII[i]-0x57)<<4;
		}

		if(HexaCodedASCII[i+1]>'/' && HexaCodedASCII[i+1]<':')
		{
			ByteArray[(i>>1)]+=HexaCodedASCII[i+1]-'0';
		}
		else if(HexaCodedASCII[i+1]>'@' && HexaCodedASCII[i+1]<'G')
		{
			ByteArray[(i>>1)]+=HexaCodedASCII[i+1]-0x37;
		}
		else if(HexaCodedASCII[i+1]>0x60 && HexaCodedASCII[i+1]<'g')
		{
			ByteArray[(i>>1)]+=HexaCodedASCII[i+1]-0x57;
		}
	}
}

void ByteArraytoHexaASCII(uint8_t *HexaCodedASCII, uint8_t *ByteArray, uint8_t size)
{
  static char Digits[] = "0123456789ABCDEF";
  uint8_t i;
  for(i=0;i<size;i++)
  {
          HexaCodedASCII[i<<1]=Digits[ByteArray[i]>>4]; 		
          HexaCodedASCII[(i<<1)+1]=Digits[ByteArray[i]&0x0F];	
  }
  HexaCodedASCII[(i<<1)]='\0';
}

