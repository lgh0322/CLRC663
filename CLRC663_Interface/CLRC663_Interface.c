#include "CLRC663_Interface.h"
#include "delay.h"

int32_t rxdata[15];//���ջ����� 
int32_t txdata[15];//���ͻ�����
void CLRC663_Uart_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure; 
	NVIC_InitTypeDef NVIC_InitStructure;
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA,ENABLE);
  RCC_APB1PeriphClockCmd( RCC_APB1Periph_USART2,ENABLE);
  //USART2_TX -> PA2 , USART2_RX ->	PA3			
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	         
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  GPIO_Init(GPIOA, &GPIO_InitStructure);		   

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;	        
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(USART2, &USART_InitStructure); 
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
  USART_ClearFlag(USART2,USART_FLAG_TC);
  USART_Cmd(USART2, ENABLE);
  //Usart2 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
}
//663��ʼ��
/*
void CLRC663_Uart_Init(void)
{
	//GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);
	
	//USART1_TX   PA.9
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
 
	//USART1_RX	  PA.10
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);  

   //Usart1 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//

	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���USART1
  //USART ��ʼ������ 
	USART_InitStructure.USART_BaudRate = 115200;//����Ϊ4800;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(USART1, &USART_InitStructure);
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�����ж�
  USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ��� 
}*/
//��������֡����CLRC663�Ĵ�����
void uart_rx_frame_663(uint8_t num) //��������֡����CLRC663�Ĵ����� 
{  
 	  uint8_t   i; 
	  USART_SendData(USART1, txdata[0]);
    while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);//�ȴ��������
	  USART_ClearFlag(USART1, USART_FLAG_TXE);//���������ɱ�־ 
	  for(i=0;i<num;i++)                //����ȡ�ֽ�������ѭ����ȡ���� 
    {                                      
			 while(USART_GetFlagStatus(USART1,USART_FLAG_RXNE) == RESET);//�ȴ�������� 
			 rxdata[i]=USART_ReceiveData(USART1);//�����յ������ݴ�ŵ� rxdata���飬���� 
			 USART_ClearFlag(USART1, USART_FLAG_RXNE);//���������ɱ�־ 
    }
}
//��������֡��дCLRC663�Ĵ�����
void uart_tx_frame_663(uint8_t num)//��������֡��дCLRC663�Ĵ����� 
{    
	  u8  i=1; 
    USART_SendData(USART1, txdata[0]);//����д�Ĵ������0x80+ADDR�� 
		while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);//�ȴ��������  
		USART_ClearFlag(USART1, USART_FLAG_TXE);//���������ɱ�־
    for(i=1;i<num;i++)   //���ݲ��� num�������ֽ�������ѭ��д���� 
    {                    
			  USART_SendData(USART1, txdata[i]);//�������� 
        while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);//�ȴ��������        
        USART_ClearFlag(USART1, USART_FLAG_TXE);//���������ɱ�־  
    }                                                                 
		//USART_SendData(USART1,txdata[num]);//����CHECKSUM            
    //while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);//�ȴ��������
		//USART_ClearFlag(USART1, USART_FLAG_TXE);//���������ɱ�־  
}


