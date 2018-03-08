#ifndef _STRBUF_H_
#define _STRBUF_H_

#include "commonDefs.h"

void buffer_init(uint8_t *buf,uint8_t val,uint32_t len);
void buffer_copy(uint8_t *dst,uint8_t *src,uint8_t len);
int32_t AtoI(uint8_t *str);
void HexaASCIItoByteArray(uint8_t *ByteArray, uint8_t *HexaCodedASCII,uint8_t size);
void ByteArraytoHexaASCII(uint8_t *HexaCodedASCII, uint8_t *ByteArray, uint8_t size);
uint8_t isASCII(uint8_t *buf,uint32_t len);

#endif /* _STRBUF_H_ */
