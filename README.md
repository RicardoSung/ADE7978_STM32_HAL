# ADE7978_STM32_HAL
                                                
## Attention
1. Any unauthorized contest and commercial applications or plagiarism may be subject to legal liability.
2. This program can be applied to open source programs and does not require a license.
3. Any application must credit the original author.
4. Any reproduction, distribution, modification must follow the original agreement.
<br><center>All Rights Reserved by Fei Song, 2021</center>

## Preknowledge
The chipset including ADE7978 and ADE7933/7932 use three communication protocols to transmit and receive data, which are SPI, I2C and HSDC. However, the I2C cannot work together with SPI but HSDC. The SPI protocol is easy to make it. So the code is about I2C, which can be used by both hardware and software, and HSDC.
## Issues
1. The software I2C may have some problems.
2. The Data received may not be trusted but the logic analyser shows the data received by STM32 is right.
## Method
1. To choose the communication protocols, please predefine the HSDC_Mode and I2C_Mode in file "ade7978.h" like "#define I2C_Mode Using_HW_I2C" and "#define HSDC_Mode HSDC_Used".
2. If you want to use HSDC, you need to change the SPI mode to "Slave Receive Only", set the SS/HSA to be "Low-Level active", modify the "Data Size", which should be 32bit, and change "Master Inter Data Idleness" and "Master Ss Idleness" to be "07 Cycles". Last but not least, never forget to enable "SPIx global interrupt".
3. Change the SPI and IIC handler in functions "ade7978_mem_read()" and "ade7978_mem_write".
4. To use HSDC to get data, you need to add "SPI Receive Callback" to restart SPI and process the data received, like 
"	void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi)
{
  if(hspi->Instance==hspi3.Instance){
  HAL_SPI_Receive_IT(&hspi3,(uint8_t*)&hsdc_value,16);
  }
} ".
Also, remember to export hsdc_value to main.c like "extern uint32_t hsdc_value[16];".
5. If you want to using IIC to receive data, please use the function "ade7978_read_validation". And the transmission opration is in the same way.
