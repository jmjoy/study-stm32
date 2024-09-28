#ifndef __W25Q64_H
#define __W25Q64_H

#include "SPI.h"

// W25Q64指令定义
#define W25Q64_CMD_WRITE_ENABLE    0x06
#define W25Q64_CMD_WRITE_DISABLE   0x04
#define W25Q64_CMD_PAGE_PROGRAM    0x02
#define W25Q64_CMD_SECTOR_ERASE    0x20
#define W25Q64_CMD_READ_STATUS_REG 0x05
#define W25Q64_CMD_READ_DATA       0x03

typedef struct {
    uint8_t vendor_id;
    uint16_t device_id;
} JEDEC;

void W25Q64_Init(void);
void W25Q64_ReadJEDEC(JEDEC *jedec);
void W25Q64_Read(uint32_t addr, uint8_t *data, uint16_t len);
void W25Q64_EarseSector(uint32_t addr);
void W25Q64_PageProgram(uint32_t addr, uint8_t *data, uint16_t len);

#endif
