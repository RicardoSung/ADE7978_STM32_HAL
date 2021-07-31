/**
  ******************************************************************************
  * @file    ade7978.h
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
  *              All Rights Reserved by Fei Song, 2021
  *
  ******************************************************************************
  */


#ifndef __ADE_H__
#define __ADE_H__

#include "main.h"

#include "gpio.h"

#define I2C_Mode Using_HW_I2C
//#define I2C_Mode Using_SW_I2C
#define Using_SW_I2C 0
#define Using_HW_I2C 1


#define HSDC_Mode HSDC_Used
//#define HSDC_Mode HSDC_Unused
#define HSDC_Used 1
#define HSDC_Unused 1

#if I2C_Mode==Using_HW_I2C
#include "i2c.h"
#else
	#include "myiic.h"
#endif

#if HSDC_Mode==HSDC_Used
#include "spi.h"
#endif







//   ###                         ##    ##                        
//  ## ##                        ##                              
//  ##     ##  ##  #####   #### ##### ###   ####  #####   #####  
// ####    ##  ##  ##  ## ##  ## ##    ##  ##  ## ##  ## ##      
//  ##     ##  ##  ##  ## ##     ##    ##  ##  ## ##  ##  #####  
//  ##     ##  ##  ##  ## ##  ## ## ## ##  ##  ## ##  ##      ## 
// ####     ###### ##  ##  ####   ### ####  ####  ##  ## ######  
void ade7978_mem_write(uint16_t MemAddress,uint8_t *pData, uint16_t Size);
void ade7978_mem_read(uint16_t MemAddress,uint8_t *pData, uint16_t Size);
uint8_t ade7978_write_validation(uint16_t MemAddress,uint8_t *pData, uint16_t Size);
uint8_t ade7978_read_validation(uint16_t MemAddress,uint8_t *pData, uint16_t Size);
uint8_t ade7978_init(void);
void ade7978_dsp_ram_init(void);
void ade7978_DSP_start(void);
void ade7978_energy_reg_read(void);
void ade7978_cfmode_clear(void);
void data_mirror(uint8_t *pData, uint8_t Size);
void ade7978_HSDC_init_start(void);

//                ###                        
//                 ##                        
// ##  ##          ##  ##  ##  ####   #####  
// ##  ##   ####   ##  ##  ## ##  ## ##      
// ##  ##  #    #  ##  ##  ## ######  #####  
//  ####   #   ##  ##  ##  ## ##          ## 
//   ##     ### # ####  ###### ##### ######  
                                           

#define 	AIGAIN_value	(uint32_t )0x00000000
#define 	AVGAIN_value	(uint32_t )0x00000000
#define 	AV2GAIN_value	(uint32_t )0x00000000
#define 	BIGAIN_value	(uint32_t )0x00000000
#define 	BVGAIN_value	(uint32_t )0x00000000
#define 	BV2GAIN_value	(uint32_t )0x00000000
#define 	CIGAIN_value	(uint32_t )0x00000000
#define 	CVGAIN_value	(uint32_t )0x00000000
#define 	CV2GAIN_value	(uint32_t )0x00000000
#define 	NIGAIN_value	(uint32_t )0x00000000
#define 	NVGAIN_value	(uint32_t )0x00000000
#define 	NV2GAIN_value	(uint32_t )0x00000000
#define 	AIRMSOS_value	(uint32_t )0x00000000
#define 	AVRMSOS_value	(uint32_t )0x00000000
#define 	AV2RMSOS_value (uint32_t )0x00000000
#define 	BIRMSOS_value	(uint32_t )0x00000000
#define 	BVRMSOS_value	(uint32_t )0x00000000
#define 	BV2RMSOS_value (uint32_t )0x00000000
#define 	CIRMSOS_value	(uint32_t )0x00000000
#define 	CVRMSOS_value	(uint32_t )0x00000000
#define 	CV2RMSOS_value (uint32_t )0x00000000
#define 	NIRMSOS_value	(uint32_t )0x00000000
#define 	NVRMSOS_value 	(uint32_t )0x00000000
#define 	NV2RMSOS_value 	(uint32_t )0x00000000
#define 	ISUMLVL_value	(uint32_t )0x00000000
#define 	APGAIN_value 	(uint32_t )0x00000000
#define 	BPGAIN_value 	(uint32_t )0x00000000
#define 	CPGAIN_value	(uint32_t )0x00000000
#define 	AWATTOS_value 	(uint32_t )0x00000000
#define 	BWATTOS_value 	(uint32_t )0x00000000
#define 	CWATTOS_value 	(uint32_t )0x00000000
#define 	AVAROS_value 	(uint32_t )0x00000000
#define 	BVAROS_value 	(uint32_t )0x00000000
#define 	CVAROS_value 	(uint32_t )0x00000000
#define 	VLEVEL_value	(uint32_t )0x00000000
#define 	AFWATTOS_value 	(uint32_t )0x00000000
#define 	BFWATTOS_value 	(uint32_t )0x00000000
#define 	CFWATTOS_value 	(uint32_t )0x00000000
#define 	AFVAROS_value 	(uint32_t )0x00000000
#define 	BFVAROS_value 	(uint32_t )0x00000000
#define 	CFVAROS_value	(uint32_t )0x00000000
#define 	AFIRMSOS_value 	(uint32_t )0x00000000
#define 	BFIRMSOS_value 	(uint32_t )0x00000000
#define 	CFIRMSOS_value 	(uint32_t )0x00000000
#define 	AFVRMSOS_value 	(uint32_t )0x00000000
#define 	BFVRMSOS_value 	(uint32_t )0x00000000
#define 	CFVRMSOS_value 	(uint32_t )0x00000000
#define 	TEMPCO_value 	(uint32_t )0x00000000
#define 	ATEMP0_value	(uint32_t )0x00000000
#define 	BTEMP0_value 	(uint32_t )0x00000000
#define 	CTEMP0_value 	(uint32_t )0x00000000
#define 	NTEMP0_value	(uint32_t )0x00000000
#define 	ATGAIN_value 	(uint32_t )0x00000000
#define 	BTGAIN_value 	(uint32_t )0x00000000
#define 	CTGAIN_value 	(uint32_t )0x00000000
#define 	NTGAIN_value	(uint32_t )0x00000000






//                         ##          ##                           
//                                     ##                           
// ######   ####   ### ## ###   ##### #####   ####  ######   #####  
//  ##  ## ##  ## ##  ##   ##  ##      ##    ##  ##  ##  ## ##      
//  ##     ###### ##  ##   ##   #####  ##    ######  ##      #####  
//  ##     ##      #####   ##       ## ## ## ##      ##          ## 
// ####     #####     ##  #### ######   ###   ##### ####    ######  
//                #####                                             
//the list of ADE7978 registers
#define ADE_addr 0x70
//Registers located in DSP Data Memory RAM
#define 	AIGAIN	0x4380
#define 	AVGAIN	0x4381
#define 	AV2GAIN	0x4382
#define 	BIGAIN	0x4383
#define 	BVGAIN	0x4384
#define 	BV2GAIN	0x4385
#define 	CIGAIN	0x4386
#define 	CVGAIN	0x4387
#define 	CV2GAIN	0x4388
#define 	NIGAIN	0x4389
#define 	NVGAIN	0x438A
#define 	NV2GAIN	0x438B
#define 	AIRMSOS	0x438C
#define 	AVRMSOS	0x438D
#define 	AV2RMSOS	0x438E
#define 	BIRMSOS	0x438F
#define 	BVRMSOS	0x4390
#define 	BV2RMSOS	0x4391
#define 	CIRMSOS	0x4392
#define 	CVRMSOS	0x4393
#define 	CV2RMSOS	0x4394
#define 	NIRMSOS	0x4395
#define 	NVRMSOS 	0x4396
#define 	NV2RMSOS 	0x4397
#define 	ISUMLVL	0x4398
#define 	APGAIN 	0x4399
#define 	BPGAIN 	0x439A
#define 	CPGAIN	0x439B
#define 	AWATTOS 	0x439C
#define 	BWATTOS 	0x439D
#define 	CWATTOS 	0x439E
#define 	AVAROS 	0x439F
#define 	BVAROS 	0x43A0
#define 	CVAROS 	0x43A1
#define 	VLEVEL	0x43A2
#define 	AFWATTOS 	0x43A3
#define 	BFWATTOS 	0x43A4
#define 	CFWATTOS 	0x43A5
#define 	AFVAROS 	0x43A6
#define 	BFVAROS 	0x43A7
#define 	CFVAROS	0x43A8
#define 	AFIRMSOS 	0x43A9
#define 	BFIRMSOS 	0x43AA
#define 	CFIRMSOS 	0x43AB
#define 	AFVRMSOS 	0x43AC
#define 	BFVRMSOS 	0x43AD
#define 	CFVRMSOS 	0x43AE
#define 	TEMPCO 	0x43AF
#define 	ATEMP0	0x43B0
#define 	BTEMP0 	0x43B1
#define 	CTEMP0 	0x43B2
#define 	NTEMP0	0x43B3
#define 	ATGAIN 	0x43B4
#define 	BTGAIN 	0x43B5
#define 	CTGAIN 	0x43B6
#define 	NTGAIN	0x43B7
#define 	AIRMS 	0x43C0
#define 	AVRMS 	0x43C1
#define 	AV2RMS 	0x43C2
#define 	BIRMS 	0x43C3
#define 	BVRMS 	0x43C4
#define 	BV2RMS 	0x43C5
#define 	CIRMS 	0x43C6
#define 	CVRMS 	0x43C7
#define 	CV2RMS 	0x43C8
#define 	NIRMS 	0x43C9
#define 	ISUM	0x43CA
#define 	ATEMP 	0x43CB
#define 	BTEMP 	0x43CC
#define 	CTEMP 	0x43CD
#define 	NTEMP	0x43CE
//Internal DSP Memory RAM Registers	
#define 	RUN	0xE228
//Billable Registers		
#define 	AWATTHR 	0xE400 
#define 	BWATTHR 	0xE401 
#define 	CWATTHR 	0xE402 
#define 	AFWATTHR 	0xE403 
#define 	BFWATTHR 	0xE404 
#define 	CFWATTHR 	0xE405 
#define 	AVARHR 	0xE406 
#define 	BVARHR 	0xE407 
#define 	CVARHR 	0xE408 
#define 	AFVARHR 	0xE409 
#define 	BFVARHR 	0xE40A 
#define 	CFVARHR 	0xE40B 
#define 	AVAHR 	0xE40C 
#define 	BVAHR 	0xE40D 
#define 	CVAHR	0xE40E
//Configuration and Power Quality Registers		
#define 	IPEAK 	0xE500
#define 	VPEAK	0xE501
#define 	STATUS0 	0xE502
#define 	STATUS1	0xE503
#define 	OILVL	0xE507
#define 	OVLVL	0xE508
#define 	SAGLVL	0xE509
#define 	MASK0	0xE50A
#define 	MASK1	0xE50B
#define 	IAWV	0xE50C
#define 	IBWV	0xE50D
#define 	ICWV	0xE50E
#define 	INWV	0xE50F
#define 	VAWV 	0xE510 
#define 	VBWV 	0xE511
#define 	VCWV	0xE512 
#define 	VA2WV 	0xE513 
#define 	VB2WV 	0xE514 
#define 	VC2WV 	0xE515 
#define 	VNWV	0xE516
#define 	VN2WV 	0xE517 
#define 	AWATT 	0xE518 
#define 	BWATT 	0xE519 
#define 	CWATT 	0xE51A 
#define 	AVAR 	0xE51B 
#define 	BVAR 	0xE51C 
#define 	CVAR 	0xE51D 
#define 	AVA 	0xE51E 
#define 	BVA 	0xE51F 
#define 	CVA	0xE520
#define 	AVTHD 	0xE521 
#define 	AITHD 	0xE522 
#define 	BVTHD 	0xE523 
#define 	BITHD 	0xE524 
#define 	CVTHD 	0xE525 
#define 	CITHD	0xE526
#define 	NVRMS	0xE530
#define 	NV2RMS	0xE531
#define 	CHECKSUM	0xE532
#define 	VNOM	0xE533
#define 	AFIRMS	0xE537
#define 	AFVRMS	0xE538
#define 	BFIRMS	0xE539
#define 	BFVRMS	0xE53A
#define 	CFIRMS	0xE53B
#define 	CFVRMS	0xE53C
#define 	LAST_RWDATA32	0xE5FF
#define 	PHSTATUS 	0xE600
#define 	ANGLE0	0xE601
#define 	ANGLE1 	0xE602
#define 	ANGLE2	0xE603
#define 	PHNOLOAD	0xE608
#define 	LINECYC	0xE60C
#define 	ZXTOUT	0xE60D
#define 	COMPMODE	0xE60E
#define 	CFMODE 	0xE610
#define 	CF1DEN 	0xE611
#define 	CF2DEN 	0xE612
#define 	CF3DEN 	0xE613
#define 	APHCAL 	0xE614
#define 	BPHCAL 	0xE615
#define 	CPHCAL 	0xE616
#define 	PHSIGN 	0xE617
#define 	CONFIG	0xE618
#define 	MMODE	0xE700 
#define 	ACCMODE 	0xE701 
#define 	LCYCMODE	0xE702 
#define 	PEAKCYC 	0xE703 
#define 	SAGCYC 	0xE704 
#define 	CFCYC	0xE705 
#define 	HSDC_CFG	0xE706
#define 	Version	0xE707
#define 	CONFIG3	0xE708
#define 	ATEMPOS	0xE709
#define 	BTEMPOS	0xE70A
#define 	CTEMPOS	0xE70B
#define 	NTEMPOS	0xE70C
#define 	LAST_RWDATA8	0xE7FD
#define 	APF	0xE902
#define 	BPF	0xE903
#define 	CPF	0xE904
#define 	APERIOD	0xE905
#define 	BPERIOD	0xE906
#define 	CPERIOD	0xE907
#define 	APNOLOAD	0xE908
#define 	VARNOLOAD	0xE909
#define 	VANOLOAD	0xE90A
#define 	LAST_ADD	0xE9FE
#define 	LAST_RWDATA16	0xE9FF
#define 	CONFIG2	0xEA00
#define 	LAST_OP	0xEA01
#define 	WTHR	0xEA02
#define 	VARTHR	0xEA03
#define 	VATHR	0xEA04
#define   DSP_RAM_Protection_1 0xE7FE
#define   DSP_RAM_Protection_2 0xE7E3


#endif