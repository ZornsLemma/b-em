#ifndef __INC_6502TUBE_H
#define __INC_6502TUBE_H

#include "cpu_debug.h"

void tube_6502_init_cpu(void);
void tube_6502_reset(void);
void tube_6502_exec(void);
void tube_6502_close(void);
void tube_6502_mapoutrom(void);
uint8_t tube_6502_readmem(uint32_t addr);
void tube_6502_writemem(uint32_t addr, uint8_t byte);

extern cpu_debug_t tube6502_cpu_debug;

#endif
