#ifndef _MYIIC_H
#define _MYIIC_H

#include "main.h"
#include "gpio.h"
#include "ade7978.h"
#if I2C_Mode==Using_SW_I2C
#define fclk_Mhz  400

#define SDA_IN()  {GPIOH->MODER&=~(3<<(8*2));GPIOH->MODER|=0<<8*2;}
#define SDA_OUT() {GPIOH->MODER&=~(3<<(8*2));GPIOH->MODER|=1<<8*2;}


//#define SDA_IN()  {GPIOH->MODER&=~(3<<(5*2));GPIOH->MODER|=0<<5*2;}
//#define SDA_OUT() {GPIOH->MODER&=~(3<<(5*2));GPIOH->MODER|=1<<5*2;}


#define IIC_SCL(n)  (n?HAL_GPIO_WritePin(I2C_SCL_GPIO_Port,I2C_SCL_Pin,GPIO_PIN_SET):HAL_GPIO_WritePin(I2C_SCL_GPIO_Port,I2C_SCL_Pin,GPIO_PIN_RESET))
#define IIC_SDA(n)  (n?HAL_GPIO_WritePin(I2C_SDA_GPIO_Port,I2C_SDA_Pin,GPIO_PIN_SET):HAL_GPIO_WritePin(I2C_SDA_GPIO_Port,I2C_SDA_Pin,GPIO_PIN_RESET))
#define READ_SDA    HAL_GPIO_ReadPin(I2C_SDA_GPIO_Port,I2C_SDA_Pin)


void IIC_Init(void); 				 
void IIC_Start(void);
void IIC_Stop(void);
void IIC_Send_Byte(uint8_t txd);
uint8_t IIC_Read_Byte(unsigned char ack);
uint8_t IIC_Wait_Ack(void);
void IIC_Ack(void);
void IIC_NAck(void);
void delay_us(uint32_t us);
void IIC_Write_One_Byte(uint8_t daddr,uint8_t addr,uint8_t data);
uint8_t IIC_Read_One_Byte(uint8_t daddr,uint8_t addr);	 

void IIC_Mem_Read(uint8_t device_addr, uint8_t *emory_addr,
	uint8_t *pData, uint8_t Size);

void IIC_Mem_Write(uint8_t device_addr, uint8_t *emory_addr,
	uint8_t *pData, uint8_t Size);
#endif

#endif

