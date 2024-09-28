#include "W25Q64.h"

void W25Q64_Init(void) {
    MY_SPI_Init();
}

void W25Q64_ReadJEDEC(JEDEC *jedec) {
    MY_SPI_START();
    MY_SPI_SWAP(0x9F);
    jedec->vendor_id = MY_SPI_SWAP(0xFF);
    jedec->device_id = MY_SPI_SWAP(0xFF);
    jedec->device_id <<= 8;
    jedec->device_id |= MY_SPI_SWAP(0xFF);
    MY_SPI_STOP();
}

void W25Q64_Read(uint32_t addr, uint8_t *data, uint16_t len) {
    MY_SPI_START();
    MY_SPI_SWAP(W25Q64_CMD_READ_DATA);
    MY_SPI_SWAP(addr >> 16);
    MY_SPI_SWAP(addr >> 8);
    MY_SPI_SWAP(addr);
    for (int i = 0; i < len; i += 1) {
        data[i] = MY_SPI_SWAP(0xFF);
    }
    MY_SPI_STOP();
}

static void W25Q64_WriteEnable(void) {
    MY_SPI_START();
    MY_SPI_SWAP(W25Q64_CMD_WRITE_ENABLE);
    MY_SPI_STOP();
}

static void W25Q64_WriteDisable(void) {
    MY_SPI_START();
    MY_SPI_SWAP(W25Q64_CMD_WRITE_DISABLE);
    MY_SPI_STOP();
}

static void W25Q64_WaitForWriteEnd(void) {
    uint8_t status;
    do {
        MY_SPI_START();
        MY_SPI_SWAP(W25Q64_CMD_READ_STATUS_REG);
        status = MY_SPI_SWAP(0xFF);
        MY_SPI_STOP();
    } while (status & 0x01);
}

void W25Q64_EarseSector(uint32_t addr) {
    W25Q64_WriteEnable();
    MY_SPI_START();
    MY_SPI_SWAP(W25Q64_CMD_SECTOR_ERASE);
    MY_SPI_SWAP(addr >> 16);
    MY_SPI_SWAP(addr >> 8);
    MY_SPI_SWAP(addr);
    MY_SPI_STOP();
    W25Q64_WaitForWriteEnd();
}

void W25Q64_PageProgram(uint32_t addr, uint8_t *data, uint16_t len) {
    W25Q64_WriteEnable();
    MY_SPI_START();
    MY_SPI_SWAP(W25Q64_CMD_PAGE_PROGRAM);
    MY_SPI_SWAP(addr >> 16);
    MY_SPI_SWAP(addr >> 8);
    MY_SPI_SWAP(addr);
    for (int i = 0; i < len; i += 1) {
        MY_SPI_SWAP(data[i]);
    }
    MY_SPI_STOP();
    W25Q64_WaitForWriteEnd();
}
