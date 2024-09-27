#ifndef __LCD_INIT_H
#define __LCD_INIT_H

#include "sys.h"

#define USE_HORIZONTAL 2  //���ú�������������ʾ 0��1Ϊ���� 2��3Ϊ����


#if USE_HORIZONTAL==0||USE_HORIZONTAL==1
#define LCD_W 80
#define LCD_H 160

#else
#define LCD_W 160
#define LCD_H 80
#endif



//-----------------LCD�˿ڶ���---------------- 

#define LCD_SCLK_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_3)//SCL=SCLK
#define LCD_SCLK_Set() GPIO_SetBits(GPIOB,GPIO_Pin_3)

#define LCD_MOSI_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_5)//SDA=MOSI
#define LCD_MOSI_Set() GPIO_SetBits(GPIOB,GPIO_Pin_5)

#define LCD_RES_Clr()  GPIO_ResetBits(GPIOB,GPIO_Pin_6)//RES
#define LCD_RES_Set()  GPIO_SetBits(GPIOB,GPIO_Pin_6)

#define LCD_DC_Clr()   GPIO_ResetBits(GPIOB,GPIO_Pin_4)//DC
#define LCD_DC_Set()   GPIO_SetBits(GPIOB,GPIO_Pin_4)
 		     
#define LCD_CS_Clr()   GPIO_ResetBits(GPIOB,GPIO_Pin_7)//CS
#define LCD_CS_Set()   GPIO_SetBits(GPIOB,GPIO_Pin_7)

#define LCD_BLK_Clr()  GPIO_ResetBits(GPIOB,GPIO_Pin_8)//BLK
#define LCD_BLK_Set()  GPIO_SetBits(GPIOB,GPIO_Pin_8)





void LCD_GPIO_Init(void);//��ʼ��GPIO
void LCD_Writ_Bus(u8 dat);//ģ��SPIʱ��
void LCD_WR_DATA8(u8 dat);//д��һ���ֽ�
void LCD_WR_DATA(u16 dat);//д�������ֽ�
void LCD_WR_REG(u8 dat);//д��һ��ָ��
void LCD_Address_Set(u16 x1,u16 y1,u16 x2,u16 y2);//�������꺯��
void LCD_Init(void);//LCD��ʼ��
#endif
