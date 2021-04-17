/*******************************************************************************
*         Copyright (c), NXP Semiconductors Gratkorn / Austria
*
*                     (C)NXP Semiconductors
*       All rights are reserved. Reproduction in whole or in part is
*      prohibited without the written consent of the copyright owner.
*  NXP reserves the right to make changes without notice at any time.
* NXP makes no warranty, expressed, implied or statutory, including but
* not limited to any implied warranty of merchantability or fitness for any
*particular purpose, or that the use will not infringe any third party patent,
* copyright or trademark. NXP must not be liable for any loss or damage
*                          arising from its use.
********************************************************************************
*
* Filename:          RegCtl_SpiHw.c
* Processor family:  LPC11xx
*
* Description:       This file holds the functions for the SPI communication.
*                    In case of the Silica TUSA board, the SPI communication
*                    gets emulated, because it uses GPIO pins that are not
*                    designated for use of SPI communication.
*******************************************************************************/
#include <ph_Status.h>
#include <RegCtl_SpiHw.h>
#include "spi.h"


#if CONFIG_ENABLE_DRIVER_SSP==1
/* statistics of all the interrupts */
volatile uint32_t interruptRxStat0 = 0;
volatile uint32_t interruptOverRunStat0 = 0;
volatile uint32_t interruptRxTimeoutStat0 = 0;

volatile uint32_t interruptRxStat1 = 0;
volatile uint32_t interruptOverRunStat1 = 0;
volatile uint32_t interruptRxTimeoutStat1 = 0;
#endif




void Reset_RC663_device(void);
void _SSP0_SetReg(uint8_t *buf);
void _SSP0_GetReg(uint8_t *buf);
phStatus_t RegCtl_SpiHwGetReg(uint8_t address, uint8_t *reg_data);
phStatus_t RegCtl_SpiHwSetReg(uint8_t address, uint8_t reg_data);
phStatus_t RegCtl_SpiHwModReg(uint8_t address, uint8_t mask, uint8_t set);
phStatus_t RegCtl_SpiHwSetMultiData(uint8_t *buf, uint32_t Len);
phStatus_t RegCtl_SpiHwGetMultiData(uint8_t *txbuf, uint8_t *rxbuf, uint32_t Len);





uint8_t SPI1_ReadWriteByte(uint8_t x){
	unsigned char y;
	HAL_SPI_TransmitReceive(&hspi1,&x,&y,1,100);  
	return y;
}


void _SSP0_SetReg(uint8_t *buf)
{
	uint8_t address,value,i;
	address = *buf++;	//地址
	value = *buf;		//数据
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_RESET);
	SPI1_ReadWriteByte(address);
	SPI1_ReadWriteByte(value);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_SET);
}

void _SSP0_GetReg(uint8_t *buf)
{
		 uint8_t i, ucAddr;
		 uint8_t ucResult=0;
		 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_RESET);
		 ucAddr = *buf++;	//地址
		 SPI1_ReadWriteByte(ucAddr);
	  *buf = SPI1_ReadWriteByte(0);
	   HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_SET);

}
/*********************************************************************/
/*
 * @brief 		Get a databyte from a register
 * @param[in]	address		Address of the register
 * @param[in]	*reg_data	Pointer to the databyte to be read
 *
 * @return 		- PH_ERR_BFL_SUCCESS
 *
 **********************************************************************/
phStatus_t RegCtl_SpiHwGetReg(uint8_t address, uint8_t *reg_data)
{
	uint8_t buff[2];

	// load address in tx_buff 
	buff[0] = address;

	// Assert the SSEL pin 
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_RESET);

	// receive 2 bytes: dummy byte + valid byte
	_SSP0_GetReg(buff);

	// Deassert the SSEL pin 
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_SET);

	// 2nd valid databyte
	reg_data[1] = buff[1];

	// return success
	return PH_ERR_SUCCESS;
}

/*********************************************************************//**
 * @brief 		Set a databyte to a register
 * @param[in]	address		Address of the register
 * @param[in]	*reg_data	Databyte to be written
 *
 * @return 		- PH_ERR_BFL_SUCCESS
 *
 **********************************************************************/
phStatus_t RegCtl_SpiHwSetReg(uint8_t address, uint8_t reg_data)
{
	uint8_t buff[2];

	// load address and data in buffer
	buff[0] = address;
	buff[1] = reg_data;

	// Assert the SSEL pin
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_RESET);

	// send SPI frame
	_SSP0_SetReg(buff);

	// Deassert the SSEL pin
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_SET);

	// return success
	return PH_ERR_SUCCESS;
}
/*
phStatus_t RegCtl_SpiHwSetReg(uint8_t address, uint8_t reg_data)
{
  uint8_t buff[2];
  buff[0] = address;
	buff[1] = reg_data;
	SPI_CS_GPIO_L();
	//_SSP0_SetReg(buff);
	SPIx_ReadWriteByte(buff[0]);
	SPI_CS_GPIO_H();
	return PH_ERR_SUCCESS;
}*/



