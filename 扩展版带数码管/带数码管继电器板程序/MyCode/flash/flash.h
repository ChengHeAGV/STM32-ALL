#ifndef __FLASH_H
#define __FLASH_H

#include "sys.h"

int ReadFlashNBtye(uint32_t ReadAddress, uint16_t *ReadBuf, int32_t ReadNum);
void WriteFlashOneWord(uint32_t WriteAddress,uint16_t WriteData);


#endif
