#include "lcd_init.h"
#include "delay.h"

bool LCD_USE_HARDWARE_SPI = false;

void LCD_GPIO_Init(void) {
    if (LCD_USE_HARDWARE_SPI) {
        GPIO_PinRemapConfig(GPIO_Remap_SPI1, ENABLE);

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); // 使能AB端口时钟

        GPIO_InitTypeDef GPIO_InitStructure;
        GPIO_InitStructure.GPIO_Pin =
            GPIO_Pin_4 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  // 推挽输出
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 速度50MHz
        GPIO_Init(GPIOB, &GPIO_InitStructure);            // 初始化GPIOB
        GPIO_SetBits(GPIOB, GPIO_Pin_4 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8);

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_5;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; // 复用推挽输出
        GPIO_Init(GPIOB, &GPIO_InitStructure);          // 初始化GPIOB

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
        SPI_InitTypeDef SPI_InitStructure = {
            .SPI_Direction = SPI_Direction_1Line_Tx,
            .SPI_Mode = SPI_Mode_Master,
            .SPI_DataSize = SPI_DataSize_8b,
            .SPI_CPOL = SPI_CPOL_High,
            .SPI_CPHA = SPI_CPHA_2Edge,
            .SPI_NSS = SPI_NSS_Soft,
            .SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4,
            .SPI_FirstBit = SPI_FirstBit_MSB,
            .SPI_CRCPolynomial = 7,
        };
        SPI_Init(SPI1, &SPI_InitStructure);
        SPI_Cmd(SPI1, ENABLE);
    } else {
        GPIO_InitTypeDef GPIO_InitStructure;
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); // 使能AB端口时钟
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 |
                                      GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  // 推挽输出
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 速度50MHz
        GPIO_Init(GPIOB, &GPIO_InitStructure);            // 初始化GPIOB
        GPIO_SetBits(GPIOB, GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 |
                                GPIO_Pin_7 | GPIO_Pin_8);
    }
}

/******************************************************************************
      函数说明：LCD串行数据写入函数
      入口数据：dat  要写入的串行数据
      返回值：  无
******************************************************************************/
void LCD_Writ_Bus(uint8_t dat) {
    LCD_CS_Clr();
    if (LCD_USE_HARDWARE_SPI) {
        while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET) {}
        SPI_I2S_SendData(SPI1, dat);
        delay_us(1);
    } else {
        for (uint8_t i = 0; i < 8; i++) {
            LCD_SCLK_Clr();
            if (dat & 0x80) {
                LCD_MOSI_Set();
            } else {
                LCD_MOSI_Clr();
            }
            LCD_SCLK_Set();
            dat <<= 1;
        }
    }
    LCD_CS_Set();
}

/******************************************************************************
      函数说明：LCD写入数据
      入口数据：dat 写入的数据
      返回值：  无
******************************************************************************/
void LCD_WR_DATA8(uint8_t dat) {
    LCD_Writ_Bus(dat);
}

/******************************************************************************
      函数说明：LCD写入数据
      入口数据：dat 写入的数据
      返回值：  无
******************************************************************************/
void LCD_WR_DATA(uint16_t dat) {
    LCD_Writ_Bus(dat >> 8);
    LCD_Writ_Bus(dat);
}

/******************************************************************************
      函数说明：LCD写入命令
      入口数据：dat 写入的命令
      返回值：  无
******************************************************************************/
void LCD_WR_REG(uint8_t dat) {
    LCD_DC_Clr(); // 写命令
    LCD_Writ_Bus(dat);
    LCD_DC_Set(); // 写数据
}

/******************************************************************************
      函数说明：设置起始和结束地址
      入口数据：x1,x2 设置列的起始和结束地址
                y1,y2 设置行的起始和结束地址
      返回值：  无
******************************************************************************/
void LCD_Address_Set(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) {
    if (USE_HORIZONTAL == 0) {
        LCD_WR_REG(0x2a); // 列地址设置
        LCD_WR_DATA(x1 + 24);
        LCD_WR_DATA(x2 + 24);
        LCD_WR_REG(0x2b); // 行地址设置
        LCD_WR_DATA(y1);
        LCD_WR_DATA(y2);
        LCD_WR_REG(0x2c); // 储存器写
    } else if (USE_HORIZONTAL == 1) {
        LCD_WR_REG(0x2a); // 列地址设置
        LCD_WR_DATA(x1 + 24);
        LCD_WR_DATA(x2 + 24);
        LCD_WR_REG(0x2b); // 行地址设置
        LCD_WR_DATA(y1);
        LCD_WR_DATA(y2);
        LCD_WR_REG(0x2c); // 储存器写
    } else if (USE_HORIZONTAL == 2) {
        LCD_WR_REG(0x2a); // 列地址设置
        LCD_WR_DATA(x1);
        LCD_WR_DATA(x2);
        LCD_WR_REG(0x2b); // 行地址设置
        LCD_WR_DATA(y1 + 24);
        LCD_WR_DATA(y2 + 24);
        LCD_WR_REG(0x2c); // 储存器写
    } else {
        LCD_WR_REG(0x2a); // 列地址设置
        LCD_WR_DATA(x1);
        LCD_WR_DATA(x2);
        LCD_WR_REG(0x2b); // 行地址设置
        LCD_WR_DATA(y1 + 24);
        LCD_WR_DATA(y2 + 24);
        LCD_WR_REG(0x2c); // 储存器写
    }
}

void LCD_Init(void) {
    // 预先初始化
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);

    LCD_GPIO_Init(); // 初始化GPIO

    LCD_RES_Clr(); // 复位
    delay_ms(100);
    LCD_RES_Set();
    delay_ms(100);

    LCD_BLK_Set(); // 打开背光
    delay_ms(100);

    LCD_WR_REG(0x11); // Sleep exit
    delay_ms(120);    // Delay 120ms

    // Frame Rate Control (In normal mode/ Full colors)
    LCD_WR_REG(0xB1);
    LCD_WR_DATA8(0x05);
    LCD_WR_DATA8(0x3C);
    LCD_WR_DATA8(0x3C);

    // Frame Rate Control (In Idle mode/ 8-colors)
    LCD_WR_REG(0xB2);
    LCD_WR_DATA8(0x05);
    LCD_WR_DATA8(0x3C);
    LCD_WR_DATA8(0x3C);

    // Frame Rate Control (In Partial mode/ full colors)
    LCD_WR_REG(0xB3);
    LCD_WR_DATA8(0x05);
    LCD_WR_DATA8(0x3C);
    LCD_WR_DATA8(0x3C);
    LCD_WR_DATA8(0x05);
    LCD_WR_DATA8(0x3C);
    LCD_WR_DATA8(0x3C);

    // Display Inversion Control
    LCD_WR_REG(0xB4); // Dot inversion
    LCD_WR_DATA8(0x03);

    // Power Control 1
    LCD_WR_REG(0xC0);
    LCD_WR_DATA8(0x0E);
    LCD_WR_DATA8(0x0E);
    LCD_WR_DATA8(0x04);

    // Power Control 2
    LCD_WR_REG(0xC1);
    LCD_WR_DATA8(0xC5);

    // Power Control 3 (In Normal mode)
    LCD_WR_REG(0xC2);
    LCD_WR_DATA8(0x0d);
    LCD_WR_DATA8(0x00);

    // Power Control 4 (In Idle mode)
    LCD_WR_REG(0xC3);
    LCD_WR_DATA8(0x8D);
    LCD_WR_DATA8(0x2A);

    // Power Control 5 (In Partial mode)
    LCD_WR_REG(0xC4);
    LCD_WR_DATA8(0x8D);
    LCD_WR_DATA8(0xEE);

    // VCOM Control 1
    LCD_WR_REG(0xC5);   // VCOM
    LCD_WR_DATA8(0x06); // 1D  .06

    // Memory Data Access Control
    LCD_WR_REG(0x36); // MX, MY, RGB mode
    if (USE_HORIZONTAL == 0)
        LCD_WR_DATA8(0x08);
    else if (USE_HORIZONTAL == 1)
        LCD_WR_DATA8(0xC8);
    else if (USE_HORIZONTAL == 2)
        LCD_WR_DATA8(0x78);
    else
        LCD_WR_DATA8(0xA8);

    // Interface Pixel Format
    LCD_WR_REG(0x3A);
    LCD_WR_DATA8(0x55);

    // Gamma (‘+’polarity) Correction Characteristics Setting
    LCD_WR_REG(0xE0);
    LCD_WR_DATA8(0x0b);
    LCD_WR_DATA8(0x17);
    LCD_WR_DATA8(0x0a);
    LCD_WR_DATA8(0x0d);
    LCD_WR_DATA8(0x1a);
    LCD_WR_DATA8(0x19);
    LCD_WR_DATA8(0x16);
    LCD_WR_DATA8(0x1d);
    LCD_WR_DATA8(0x21);
    LCD_WR_DATA8(0x26);
    LCD_WR_DATA8(0x37);
    LCD_WR_DATA8(0x3c);
    LCD_WR_DATA8(0x00);
    LCD_WR_DATA8(0x09);
    LCD_WR_DATA8(0x05);
    LCD_WR_DATA8(0x10);

    // Gamma ‘-’polarity Correction Characteristics Setting
    LCD_WR_REG(0xE1);
    LCD_WR_DATA8(0x0c);
    LCD_WR_DATA8(0x19);
    LCD_WR_DATA8(0x09);
    LCD_WR_DATA8(0x0d);
    LCD_WR_DATA8(0x1b);
    LCD_WR_DATA8(0x19);
    LCD_WR_DATA8(0x15);
    LCD_WR_DATA8(0x1d);
    LCD_WR_DATA8(0x21);
    LCD_WR_DATA8(0x26);
    LCD_WR_DATA8(0x39);
    LCD_WR_DATA8(0x3E);
    LCD_WR_DATA8(0x00);
    LCD_WR_DATA8(0x09);
    LCD_WR_DATA8(0x05);
    LCD_WR_DATA8(0x10);

    delay_ms(120);
    LCD_WR_REG(0x29); // Display on
}

void LCD_UseHardwareSPI(void) {
    LCD_USE_HARDWARE_SPI = true;
}
