#ifndef _IO_H_
#define _IO_H_

#include <stdint.h>

void put32(uint32_t addr, uint32_t value);
uint32_t get32(uint32_t addr);

#endif //#ifndef _IO_H_