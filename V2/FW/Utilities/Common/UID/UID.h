#ifndef _UID_H_
#define _UID_H_
#include "main.h"

void UID_Init(uint8_t *UID_base, uint8_t UID_size);
void UID_get(uint8_t *UID);
void UID_getUID(uint8_t *UID);
void UID_getNXSFormat(uint8_t *UID12);
void EUI64_getNXSFormat(uint8_t *EUI64);

#endif /* _UID_H_ */