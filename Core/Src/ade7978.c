/**
  ******************************************************************************
  * @file    ade7978.c
  ******************************************************************************
  * @attention
	*
  * 1. Any unauthorized contest and commercial applications or plagiarism
  *	may be subject to legal liability.
	*	2. This program can be applied to open source programs and does not require 
	* a license.
	* 3. Any application must credit the original author.
	* 4. Any reproduction, distribution, modification must follow 
	* the original agreement.
	*
  *                 All Rights Reserved by Fei Song, 2021
  *
  ******************************************************************************
  */

// ##   ##  #####  ##   ##     ##             ##   ##  ##### ####### 
// ##   ## ##   ## ##   ##     ##             ##   ## ##   ## ##   # 
// ##   ## ##   ## ##   ##    #####   ####    ##   ## ##      ## #   
// ####### ##   ## ## # ##     ##    ##  ##   ##   ##  #####  ####   
// ##   ## ##   ## #######     ##    ##  ##   ##   ##      ## ## #   
// ##   ## ##   ## ### ###     ## ## ##  ##   ##   ## ##   ## ##   # 
// ##   ##  #####  ##   ##      ###   ####     #####   ##### ####### 
/**
	*@Preknowledge
	* 1.The chipset including ADE7978 and ADE7933/7932 use three communication protocols 
	* to transmit and receive data, which are SPI, I2C and HSDC. However, the I2C cannot
	* work together with SPI but HSDC. The SPI protocol is easy to make it. So the code
	* is about I2C, which can be used by both hardware and software, and HSDC.
	*@Notice
	* 1. The software I2C may have some problems.
	* 2. The Data received may not be trusted but the logic analyser shows the data received by
	* STM32 is right.
	*@Method
	* 1. To choose the communication protocols, please predefine the HSDC_Mode and I2C_Mode
	* in file "ade7978.h" like "#define I2C_Mode Using_HW_I2C" and "#define HSDC_Mode HSDC_Used".
	* 2. If you want to use HSDC, you need to change the SPI mode to "Slave Receive Only",
	* set the SS/HSA to be "Low-Level active", modify the "Data Size", which should be 32bit,
  *	and change "Master Inter Data Idleness" and "Master Ss Idleness" to be "07 Cycles". Last
	* but not least, never forget to enable "SPIx global interrupt".
	* 3. Change the SPI and IIC handler in functions "ade7978_mem_read()" and "ade7978_mem_write".
	* 4. To use HSDC to get data, you need to add "SPI Receive Callback" to restart SPI and process
  * the data received, like 
	*	"	void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi)
	*	{
	*		if(hspi->Instance==hspi3.Instance){
	*			HAL_SPI_Receive_IT(&hspi3,(uint8_t*)&hsdc_value,16);
	*		}
	*	} ".
	* Also, remember to export hsdc_value to main.c like 
	* "extern uint32_t hsdc_value[16];".
	*@Attention
	* If you want to using IIC to receive data, please use the function
	* "ade7978_read_validation". And the transmission opration is in the same way.
  */                                                                   





#include "ade7978.h"


#if HSDC_Mode==HSDC_Used
uint32_t hsdc_value[16];
#endif

//  ####          ##  ##    ##         ###    #######                        ##    ##                        
//   ##               ##                ##     ##   #                        ##                              
//   ##   #####  ### ##### ###          ##     ## #    ##  ##  #####   #### ##### ###   ####  #####   #####  
//   ##   ##  ##  ##  ##    ##   ####   ##     ####    ##  ##  ##  ## ##  ## ##    ##  ##  ## ##  ## ##      
//   ##   ##  ##  ##  ##    ##  #    #  ##     ## #    ##  ##  ##  ## ##     ##    ##  ##  ## ##  ##  #####  
//   ##   ##  ##  ##  ## ## ##  #   ##  ##     ##      ##  ##  ##  ## ##  ## ## ## ##  ##  ## ##  ##      ## 
//  ####  ##  ## ####  ### ####  ### # ####   ####      ###### ##  ##  ####   ### ####  ####  ##  ## ######  
uint8_t ade7978_init(void)
{
  //Thread sleeps until RSTDONE interrupt triggered.
  while(HAL_GPIO_ReadPin(ADE_IRQ1_GPIO_Port,ADE_IRQ1_Pin)!=GPIO_PIN_RESET)
		HAL_Delay(1);
  //Pull-up SS/HSA pin to ensure that the communication mode between ADE7978 and 
  //STM32 is I2C and HSDC.
  HAL_GPIO_WritePin(SS_HSA_GPIO_Port,SS_HSA_Pin,GPIO_PIN_SET);
	//Write CONFIG2 Register bit I2C_LOCK to lock the communication mode which is I2C and HSDC. 
	 uint32_t STATUS_1_value;
	if(ade7978_read_validation(STATUS1,(uint8_t *)&STATUS_1_value,4)){
		if((STATUS_1_value>>15 & 1)==1){
			STATUS_1_value=0xFFFFFFFF;
		}else {
			return 0;
		}
		ade7978_write_validation(STATUS1,(uint8_t *)&STATUS_1_value,4);
		while(HAL_GPIO_ReadPin(ADE_IRQ1_GPIO_Port,ADE_IRQ1_Pin)!=GPIO_PIN_RESET)
			HAL_Delay(1);
	}
	//lock the communication mode
	uint8_t CONFIG_2=0x01;
	ade7978_write_validation(CONFIG2,&CONFIG_2,1);
	//HSDC initialize and start
	#if HSDC_Mode==HSDC_Used
	ade7978_HSDC_init_start();
	#endif
	//Initialize the dsp ram registers
	ade7978_dsp_ram_init( );
	//Start Dsp
	ade7978_DSP_start( );
	//Read the energy registers xWATTHR, xVARHR, xFWATTHR, xFVARHR, and xVAHR 
	//to erase their contents and start energy accumulation from a known state
	ade7978_energy_reg_read( );
	ade7978_cfmode_clear( );
	HAL_SPI_Receive_IT(&hspi3,(uint8_t*)&hsdc_value,16);
	return 1;
}
//HSDC initialize and start
#if HSDC_Mode==HSDC_Used
void ade7978_HSDC_init_start(void)
{
	//initialize the rules of hsdc
	//transmit data by 32bits with 7 cycles ack
	uint8_t HSDC_CFG_value=0x05;
	while(ade7978_write_validation(HSDC_CFG,&HSDC_CFG_value, 1)!=1);
		//start hsdc
	uint16_t CONFIG_value;
	while(ade7978_read_validation(CONFIG,(uint8_t *)&CONFIG_value, 2)!=1);
	CONFIG_value|=(1<<6);
	while(ade7978_write_validation(CONFIG,(uint8_t *)&CONFIG_value, 2)!=1);
//	HAL_SPI_Receive_IT(&hspi3,(uint8_t*)&hsdc_value,sizeof(hsdc_value));
}
#endif

//Initialize the dsp ram registers
//the values of AIGAIN, BIGAIN, CIGAIN, NIGAIN and etc can be changed in "ade7978.h"
void ade7978_dsp_ram_init(void)
{
	ade7978_write_validation(AIGAIN,(uint8_t *)AIGAIN_value,4);
	ade7978_write_validation(BIGAIN,(uint8_t *)BIGAIN_value,4);
	ade7978_write_validation(CIGAIN,(uint8_t *)CIGAIN_value,4);
	ade7978_write_validation(NIGAIN,(uint8_t *)NIGAIN_value,4);	
	
	ade7978_write_validation(NIGAIN,(uint8_t *)NIGAIN_value,4);
	ade7978_write_validation(NIGAIN,(uint8_t *)NIGAIN_value,4);
}
//Initialize DSP RAM and start the DSP in ADE7978
uint8_t dsp_start_value=0;
void ade7978_DSP_start(void)
{	
	uint16_t dsp_start=0x0001;
	//Start DSP
	dsp_start_value=ade7978_write_validation(RUN,(uint8_t *)&dsp_start,2);
}
//Initialize the Configuration and Power Quality registers
void ade7978_PowerConfig_init(void)
{
	
}
//DSP RAM write protection
void ade7978_dsp_ram_protection(void)
{
	ade7978_write_validation(DSP_RAM_Protection_1,(uint8_t *)0xAD,1);
	ade7978_write_validation(DSP_RAM_Protection_2,(uint8_t *)0x80,1);
}
//Read xWATTHR, xVARHR, xFWATTHR, xFVARHR, and xVAHR
void ade7978_energy_reg_read(void)
{
	uint32_t AWATTHR_value;uint32_t BWATTHR_value;uint32_t CWATTHR_value;
	uint32_t AFWATTHR_value;uint32_t BFWATTHR_value;uint32_t CFWATTHR_value;
	uint32_t AVARHR_value;uint32_t BVARHR_value;uint32_t CVARHR_value;
	uint32_t AFVARHR_value;uint32_t BFVARHR_value;uint32_t CFVARHR_value;
	uint32_t AVAHR_value;uint32_t BVAHR_value;uint32_t CVAHR_value;
	
	ade7978_read_validation(AWATTHR,(uint8_t *)AWATTHR_value,4);
	ade7978_read_validation(BWATTHR,(uint8_t *)BWATTHR_value,4);
	ade7978_read_validation(CWATTHR,(uint8_t *)CWATTHR_value,4);
	
	ade7978_read_validation(AFWATTHR,(uint8_t *)AFWATTHR_value,4);
	ade7978_read_validation(BFWATTHR,(uint8_t *)BFWATTHR_value,4);
	ade7978_read_validation(CFWATTHR,(uint8_t *)CFWATTHR_value,4);
	
	ade7978_read_validation(AVARHR,(uint8_t *)AVARHR_value,4);
	ade7978_read_validation(BVARHR,(uint8_t *)BVARHR_value,4);
	ade7978_read_validation(CVARHR,(uint8_t *)CVARHR_value,4);
	
	ade7978_read_validation(AFVARHR,(uint8_t *)AFVARHR_value,4);
	ade7978_read_validation(BFVARHR,(uint8_t *)BFVARHR_value,4);
	ade7978_read_validation(CFVARHR,(uint8_t *)CFVARHR_value,4);
	
	ade7978_read_validation(AVAHR,(uint8_t *)AVAHR_value,4);
	ade7978_read_validation(BVAHR,(uint8_t *)BVAHR_value,4);
	ade7978_read_validation(CVAHR,(uint8_t *)CVAHR_value,4);
}
//CFMODE clear
void ade7978_cfmode_clear(void)
{
	uint16_t cfmode_value;
	ade7978_read_validation(CFMODE,(uint8_t *)&cfmode_value,2);
	//to change the y bit value of x to 0: x&=~(1<<y)
	//to change the y bit value of x to 1: x|=(1<<y)
	//to change the y bit value of x to the opposite: x^=(1<<y)
	//to get the y bit value of x : (x>>y&1)
	cfmode_value &= ~(0b111<<9);
	ade7978_write_validation(CFMODE,(uint8_t *)&cfmode_value,2);
}

// ######                  ##           #######                        ##    ##                        
//  ##  ##                               ##   #                        ##                              
//  ##  ##          ##### ###   ####     ## #    ##  ##  #####   #### ##### ###   ####  #####   #####  
//  #####    ####  ##      ##  ##  ##    ####    ##  ##  ##  ## ##  ## ##    ##  ##  ## ##  ## ##      
//  ##  ##  #    #  #####  ##  ##        ## #    ##  ##  ##  ## ##     ##    ##  ##  ## ##  ##  #####  
//  ##  ##  #   ##      ## ##  ##  ##    ##      ##  ##  ##  ## ##  ## ## ## ##  ##  ## ##  ##      ## 
// ######    ### # ###### ####  ####    ####      ###### ##  ##  ####   ### ####  ####  ##  ## ######                                                                                                      
//ade7978 reading validation function including mode check, 
//memory address check and  data check
//uint8_t lastMode;uint16_t lastMemAddr;uint8_t lastData[1];
uint8_t ade7978_read_validation(uint16_t MemAddress,
                                     uint8_t *pData, uint16_t Size)
{
	//Write data by i2c
	ade7978_mem_read(MemAddress,pData,Size);
	data_mirror(pData,Size);
	
	//validate the communication mode
	uint8_t lastMode;
	ade7978_mem_read(LAST_OP,&lastMode,1);
	if(lastMode!=0x35)return 0;
	//validate the memory address
	uint16_t lastMemAddr;
	ade7978_mem_read(LAST_ADD,(uint8_t *)&lastMemAddr,2);
	data_mirror((uint8_t *)&lastMemAddr,2);
	if(lastMemAddr!=MemAddress)return 0;
	//validate the values writen to memory
	uint8_t lastData[4];
	switch(Size){
		case 0x0001: ade7978_mem_read(LAST_RWDATA8,lastData,Size);break;
		case 0x0002:ade7978_mem_read(LAST_RWDATA16,lastData,Size);break;
		case 0x0004:ade7978_mem_read(LAST_RWDATA32,lastData,Size);break;
	}
	data_mirror((uint8_t *)&lastData,Size);
	pData = 0;
	for(uint8_t i=0;i<Size;i++){
		if(lastData[i] != *pData){
			return 0;
		}else{
			pData++;
		}
	}
	return 1;
}
//ade7978 writing validation function including mode check, 
//memory address check and  data check
uint8_t ade7978_write_validation(uint16_t MemAddress,
                                     uint8_t *pData, uint16_t Size)
{
	data_mirror(pData,Size);
	//Write data by i2c
	ade7978_mem_write(MemAddress,pData,Size);
	//validate the communication mode
	uint8_t lastMode;
	ade7978_mem_read(LAST_OP,&lastMode,1);
	if(lastMode!=0xCA)return 0;
	//validate the memory address
	uint16_t lastMemAddr;
	ade7978_mem_read(LAST_ADD,(uint8_t *)&lastMemAddr,2);
	data_mirror((uint8_t *)&lastMemAddr,2);
	if(lastMemAddr!=MemAddress)return 0;
	//validate the values writen to memory
	uint8_t lastData[Size];
	switch(Size){
		case 0x0001:ade7978_mem_read(LAST_RWDATA8,lastData,Size);break;
		case 0x0002:ade7978_mem_read(LAST_RWDATA16,lastData,Size);break;
		case 0x0004:ade7978_mem_read(LAST_RWDATA32,lastData,Size);break;
	}
	data_mirror((uint8_t *)&lastData,Size);
	pData = 0;
	for(uint8_t i=0;i<Size;i++){
		if(lastData[i] != *pData){
			return 0;
		}else{
			pData++;
		}	
	}
	return 1;
}
//ade7978 memory-writing and memory-reading functions which include both HW i2c and SW i2c
//to choose the i2c mode, please pre-define "I2C_Mode==Using_HW_I2C" or "I2C_Mode==Using_SW_I2C" 
//in file "ade1978.c" or "ade1978.h"
//@attention
//the HW i2c is the interrupt mode, however, the SW i2c is the normal mode
void ade7978_mem_write(uint16_t MemAddress,uint8_t *pData, uint16_t Size)
{
	#if(I2C_Mode==Using_HW_I2C)
	HAL_I2C_Mem_Write_IT(&hi2c3,ADE_addr,MemAddress,I2C_MEMADD_SIZE_16BIT,pData,Size);
	#elif(I2C_Mode==Using_SW_I2C)
	IIC_Mem_Write(ADE_addr,(uint8_t *)&MemAddress,pData,Size);
	#endif
	HAL_Delay(1);
}
void ade7978_mem_read(uint16_t MemAddress,uint8_t *pData, uint16_t Size)
{
	#if I2C_Mode==Using_HW_I2C
	HAL_I2C_Mem_Read_IT(&hi2c3,ADE_addr,MemAddress,I2C_MEMADD_SIZE_16BIT,pData,Size);
	#else
	IIC_Mem_Read(ADE_addr,(uint8_t *)&MemAddress,pData,Size);
	#endif
	HAL_Delay(1);
}
//change the sequence of bytes to make the MSB byte be the first byte, meanwhile, the LSB be the last byte
void data_mirror(uint8_t *pData, uint8_t Size)
{
	uint8_t pData_value[Size];
	pData= pData+Size;
	for(uint8_t i=0;i<Size;i++){
		pData--;
		pData_value[i] = *pData;		
	}
	for(uint8_t i=0;i<Size;i++){
		*pData  = pData_value[i];
		pData++;
	}
}


