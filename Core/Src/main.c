/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "CLRC663_Interface.h"
#include <phbalReg.h>
#include <phhalHw.h>
#include <phpalSli15693.h>
#include <phalSli.h>
#include "phalI15693.h"
#include "phalSli.h"
#include <RegCtl_SpiHw.h>
#include "phkeyStore.h"
#include "phalI15693_Sw.h"
#include "stdio.h"
#include "aes.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
typedef uint8_t  u8;

#define  CHECK_SUCCESS(status)   {223;}//if ((status) != PH_ERR_SUCCESS) {printf("fuck\n");}else{printf("wu\n");}}

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

u8  UID_Table[8];

u8  len;
phhalHw_Rc663_DataParams_t      halReader;
phpalSli15693_Sw_DataParams_t   palSli;
phalI15693_Sw_DataParams_t      al15693;
	
	//通用变量
	uint8_t bIndex;
	phStatus_t status;
  uint8_t bHalBufferReader[256];
	
	//PAL层使用变量
	uint8_t  bOption, bFlags, bAfi;
	uint8_t  pMask[PHPAL_SLI15693_UID_LENGTH], bMaskLength;
	uint8_t  bDsfid, pUid[PHPAL_SLI15693_UID_LENGTH];
	uint8_t  bRxLength, bMoreCardsAvaliable;
	uint8_t  bBlockNo;
	uint16_t wNoOfBlocks;
	uint8_t  bUidLength;
	//uint8_t  pData[PHAL_SLI_BLOCK_SIZE * 28];
	uint8_t  pData[PHAL_SLI_BLOCK_SIZE * 1];
	uint16_t wDataLength=12;
	
	phbalReg_Stub_DataParams_t balReader;
	phKeyStore_Rc663_DataParams_t Rc663keyStore;
	
  //AL层使用的变量
	uint8_t pOriginalData[PHAL_SLI_BLOCK_SIZE];
	uint8_t ** ppData = (uint8_t**)&pData;


//u8 Key_Num;

	uint8_t Write_date=38;
	uint8_t Wr_t[12]={37,38,39,35,37,38,39,35,37,38,37,38};
	
	void *pHal;
	
int fputc(int ch,FILE *f)
{
    uint8_t temp[1]={ch};
    HAL_UART_Transmit(&huart1,temp,1,2);
		return 0;
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
uint8_t * fuck;
	unsigned short f5;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI1_Init();
  MX_USART1_UART_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
	  u8 ks[16]={4,5,2,5,0,1,1,9,9,7,0,3,2,2,7,4};
		u8 lgh[16]="onedayigotoscho";
   AesKey pkey;
   aes_initKey(&pkey, ks, 16);
		while(1){
			
			



			 u8 is[16];
			 u8 os[16];

			 memset(is, 0, sizeof(is));
			 memset(os, 0, sizeof(os));

			 aes_encrypt(&pkey, lgh, os);
			
			for(int k=0;k<16;k++){
				printf("%X",os[k]);
			}
			
			printf("\n");

			 aes_decrypt(&pkey, os, is);

				for(int k=0;k<16;k++){
				printf("%c",is[k]);
			}
			
			printf("\n");
			while(1);
			HAL_Delay(1000);
			
			
			
			
			
			
			
			
		}








while(1);

	
	status=phbalReg_Stub_Init(&balReader, sizeof(phbalReg_Stub_DataParams_t));
	 CHECK_SUCCESS(status)
	HAL_Delay(40);
	status = phhalHw_Rc663_Init(
															&halReader,
															sizeof(phhalHw_Rc663_DataParams_t),
															&balReader,
															NULL,
															bHalBufferReader,
															sizeof(bHalBufferReader),
															bHalBufferReader,
															sizeof(bHalBufferReader));

 CHECK_SUCCESS(status)
	halReader.bBalConnectionType = PHHAL_HW_BAL_CONNECTION_SPI;
	pHal = &halReader;
															
	status = phpalSli15693_Sw_Init(&palSli, sizeof(palSli), &halReader);
			 CHECK_SUCCESS(status)
		status = phalI15693_Sw_Init(&al15693, sizeof(al15693), &palSli);
			 CHECK_SUCCESS(status)
		bOption = PHPAL_SLI15693_ACTIVATE_ADDRESSED;
	bFlags =  PHPAL_SLI15693_FLAG_NBSLOTS | PHPAL_SLI15693_FLAG_DATA_RATE;
	bAfi = 0xff; 
	bMaskLength = 0;
	status = phhalHw_FieldOn(&halReader); 
	 CHECK_SUCCESS(status)
 status = phhalHw_ApplyProtocolSettings(&halReader, PHHAL_HW_CARDTYPE_ISO15693);
	 CHECK_SUCCESS(status)
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		bOption = PHPAL_SLI15693_ACTIVATE_ADDRESSED;
			bFlags =  PHPAL_SLI15693_FLAG_NBSLOTS | PHPAL_SLI15693_FLAG_DATA_RATE;
			bAfi = 0xFF; //设置为0xff，支持所有应用
			bMaskLength = 0;
		  //status = phhalHw_FieldReset(&halReader);     //打开场
		  status = phhalHw_FieldOn(&halReader);
		 CHECK_SUCCESS(status)
		 status = phhalHw_ApplyProtocolSettings(&halReader, PHHAL_HW_CARDTYPE_ISO15693);
		 CHECK_SUCCESS(status)
		
		
		  status = phpalSli15693_ActivateCard(&palSli, bOption, bFlags,
                                         bAfi, pMask, bMaskLength,
                                         &bDsfid, pUid, &bMoreCardsAvaliable);
		 CHECK_SUCCESS(status)
			if(PH_ERR_SUCCESS == status)//读卡成功
			{
				HAL_Delay(300);
				//LED1=1; 
				status = phpalSli15693_GetSerialNo(&palSli, pUid, &bRxLength);
				//BEEP_TS_Small();   
				for(len=0;len<8;len++)
				{
					 UID_Table[len]=pUid[len];   //保存UID
//					printf("%d ",pUid[len]);
				}
				printf("\n");
				if(bRxLength == PHPAL_SLI15693_UID_LENGTH)
				{
						memcpy(pMask, pUid, PHPAL_SLI15693_UID_LENGTH);
						bMaskLength = PHPAL_SLI15693_UID_LENGTH * 8;
				} 
				bFlags = 0x32; 
				bAfi = 0x00;
				//bBlockNo = 0;
				wNoOfBlocks = 1;
				bOption = PHAL_I15693_OPTION_DEFAULT;//设置为默认，即选项位清除
				//bBlockNo = 0x7f;   //块号，即读取地址
				bBlockNo = 0x10; 
				Wr_t[0]=30;
				Wr_t[1]=31;
				Wr_t[2]=32;
				Wr_t[3]=33;
				
			
				status	=	phalI15693_WriteSingleBlock(&al15693,bOption, bBlockNo,Wr_t, 4);//往单个块里写入数据
					HAL_Delay(200);
				f5=70;
					bBlockNo =0x10;
				for(int k=0;k<256;k++){
					
						phalI15693_ReadSingleBlock(&al15693,bOption, k,&fuck, &f5);
							HAL_Delay(200);
					if(f5!=0){
						printf("%d\n",k);
						
					}
				}
				
	
				
				
				
						HAL_Delay(200);
//				printf("%d\n",f5);
//				for(int k=0;k<f5;k++){
//					printf("%d hh ",fuck[k]);
//				}
				printf("\n");
				
		
				if(PH_ERR_SUCCESS == status)//读取成功
				{
					HAL_Delay(20);
				}

					
      }
						HAL_Delay(200);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
