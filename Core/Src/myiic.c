#include "myiic.h"

#if I2C_Mode==Using_SW_I2C


void IIC_Start(void)
{
	SDA_OUT(); 
	IIC_SDA(1);	  	  
	IIC_SCL(1);
	delay_us(4);
 	IIC_SDA(0);
	delay_us(4);
	IIC_SCL(0);
}	  

void IIC_Stop(void)
{
	SDA_OUT();
	IIC_SCL(0);
	IIC_SDA(0);
 	delay_us(4);
	IIC_SCL(1); 
	IIC_SDA(1);
	delay_us(4);							   	
}

uint8_t IIC_Wait_Ack(void)
{
	uint8_t ucErrTime=0;
	SDA_IN(); 
	IIC_SDA(1);delay_us(1);	   
	IIC_SCL(1);delay_us(1);	 
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL(0);  
	return 0;  
} 

void IIC_Ack(void)
{
	IIC_SCL(0);
	SDA_OUT();
	IIC_SDA(0);
	delay_us(2);
	IIC_SCL(1);
	delay_us(2);
	IIC_SCL(0);
}
	    
void IIC_NAck(void)
{
	IIC_SCL(0);
	SDA_OUT();
	IIC_SDA(1);
	delay_us(2);
	IIC_SCL(1);
	delay_us(2);
	IIC_SCL(0);
}					 				     
			  
void IIC_Send_Byte(uint8_t txd)
{                        
	uint8_t t;   
	SDA_OUT(); 	    
	IIC_SCL(0);
	for(t=0;t<8;t++)
	{              
		IIC_SDA((txd&0x80)>>7);
		txd<<=1; 	  
		delay_us(2);
		IIC_SCL(1);
		delay_us(2); 
		IIC_SCL(0);	
		delay_us(1);
	}	 
} 	    

uint8_t IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();
  for(i=0;i<8;i++ )
	{
		IIC_SCL(0); 
		delay_us(2);
		IIC_SCL(1);
		receive<<=1;
    if(READ_SDA)receive++;   
		delay_us(1); 
  }					 
    if (!ack) IIC_NAck();
    else IIC_Ack();
    return receive;
}


void IIC_Mem_Write(uint8_t device_addr, uint8_t *memory_addr,
	uint8_t *pData, uint8_t Size)
{
	IIC_Send_Byte(device_addr);
	IIC_Ack();
	memory_addr=memory_addr+2;
	for(uint8_t i=0;i<2;i++)
  {
		memory_addr--;
		IIC_Send_Byte(*memory_addr);
		IIC_Ack();	
  }
	pData=pData + Size;
	for(uint8_t i=0;i<Size;i++)
  {
		pData--;
		IIC_Send_Byte(*pData);
			
  }
}


void IIC_Mem_Read(uint8_t device_addr, uint8_t *memory_addr,
	uint8_t *pData, uint8_t Size)
{
	IIC_Send_Byte(device_addr);
	IIC_Ack();
	memory_addr=memory_addr+2;
	for(uint8_t i=0;i<2;i++)
  {
		memory_addr--;
		IIC_Send_Byte(*memory_addr);
		IIC_Ack();
  }
	IIC_Send_Byte((device_addr+0x01));IIC_Ack();
	pData = pData + Size;
	for(uint8_t i=0;i<Size;i++)
  {
		pData--;
		*pData = IIC_Read_Byte(1);
  }
}

void delay_us(uint32_t us)
{		
	uint32_t ticks;
	uint32_t told,tnow,tcnt=0;
	uint32_t reload=SysTick->LOAD;
	ticks = us * fclk_Mhz; 	
	told=SysTick->VAL;
	while(1)
	{
		tnow=SysTick->VAL;	
		if(tnow!=told)
		{	    
			if(tnow<told)tcnt+=told-tnow;
			else tcnt+=reload-tnow+told;	    
			told=tnow;
			if(tcnt>=ticks)break;	
		}  
	};
}

#endif