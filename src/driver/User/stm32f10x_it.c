/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "led.h"
#include "key.h"
#include "usart.h"
//#define GO_FORWARD() GPIO_SetBits(GPIOB, GPIO_Pin_11 | GPIO_Pin_15);GPIO_ResetBits(GPIOB, GPIO_Pin_12 | GPIO_Pin_14);
//#define GO_BACK() 
int count_speed=100;

void delay_us(u32 nTimer)
{
	u32 i=0;
	for(i=0;i<nTimer;i++){
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
	}
}
void delay_ms(u32 nTimer)
{
	u32 i=1000*nTimer;
	delay_us(i);
}
/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

void USART3_IRQHandler(void)
{
	static u8 k;
	USART_ClearFlag(USART3,USART_FLAG_TC);
	if(USART_GetITStatus(USART3,USART_IT_RXNE)!=Bit_RESET)
	{
		k=USART_ReceiveData(USART3);
		USART_SendData(USART3,k);
		while(USART_GetFlagStatus(USART3,USART_FLAG_TXE)==Bit_RESET);
		//PrintChar3("FUCK");
		switch (k)
		{
			case 'f' :GPIO_ResetBits(GPIOB, GPIO_Pin_13 | GPIO_Pin_15);GPIO_SetBits(GPIOB, GPIO_Pin_12 | GPIO_Pin_14);  PrintChar("Forward");delay_ms(200);GPIO_SetBits(GPIOB, GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15);break;	//前进	  
			case 'b' : GPIO_SetBits(GPIOB, GPIO_Pin_13 | GPIO_Pin_15);GPIO_ResetBits(GPIOB, GPIO_Pin_12 | GPIO_Pin_14); PrintChar("Back");delay_ms(200);GPIO_SetBits(GPIOB, GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15);break;	//后退		  
			case 'r' : GPIO_ResetBits(GPIOB, GPIO_Pin_13 | GPIO_Pin_14);GPIO_SetBits(GPIOB, GPIO_Pin_12 | GPIO_Pin_15); PrintChar("Right");delay_ms(200);GPIO_SetBits(GPIOB, GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15);break;  //左转
			case 'l' : GPIO_ResetBits(GPIOB, GPIO_Pin_12 | GPIO_Pin_15);GPIO_SetBits(GPIOB, GPIO_Pin_13 | GPIO_Pin_14);PrintChar("Left");delay_ms(200);GPIO_SetBits(GPIOB, GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15);break;  //左转
			case 's'	: GPIO_SetBits(GPIOB, GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15);PrintChar("Stop");break;  //停止
			case 'u' :	TIM_SetCompare3(TIM2,60);TIM_SetCompare4(TIM2,60);break;
			case 'd' :	TIM_SetCompare3(TIM2,40);TIM_SetCompare4(TIM2,40);break;
			//default : k = 0;break;
		}
	}
	
}

void USART1_IRQHandler(void)	//串口1中断函数
{
	//u8 KeyNum = 0;
	static u8 k;
	//static u8 stop_tgt=5;
	//char msg_drive;
	USART_ClearFlag(USART1,USART_FLAG_TC);
	if(USART_GetITStatus(USART1,USART_IT_RXNE)!=Bit_RESET)//检查指定的USART中断发生与否
	{
		k=USART_ReceiveData(USART1);
	//	k++;	
		USART_SendData(USART1,k);//通过外设USARTx发送单个数据
		while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==Bit_RESET);	
		/*KeyNum = ReadKeyDown();
		if(KeyNum==1)
		{
			k=84;
		}*/
		//int count=100;
		/*if(k!='f')
		{
			count_speed=100;
		}
		else{
			count_speed+=50;
		}*/
		PrintChar("Speed UP");
		/*if(k=='f')
		{
			GPIO_ResetBits(GPIOB, GPIO_Pin_11 | GPIO_Pin_12| GPIO_Pin_14| GPIO_Pin_15);PrintChar("FUck");
		}*/
		switch (k)
		{
			case 'f' :GPIO_ResetBits(GPIOB, GPIO_Pin_13 | GPIO_Pin_15);GPIO_SetBits(GPIOB, GPIO_Pin_12 | GPIO_Pin_14);  PrintChar("Forward");delay_ms(200);GPIO_SetBits(GPIOB, GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15);break;	//前进	  
			case 'b' : GPIO_SetBits(GPIOB, GPIO_Pin_13 | GPIO_Pin_15);GPIO_ResetBits(GPIOB, GPIO_Pin_12 | GPIO_Pin_14); PrintChar("Back");delay_ms(200);GPIO_SetBits(GPIOB, GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15);break;	//后退		  
			case 'r' : GPIO_ResetBits(GPIOB, GPIO_Pin_13 | GPIO_Pin_14);GPIO_SetBits(GPIOB, GPIO_Pin_12 | GPIO_Pin_15); PrintChar("Right");delay_ms(200);GPIO_SetBits(GPIOB, GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15);break;  //左转
			case 'l' : GPIO_ResetBits(GPIOB, GPIO_Pin_12 | GPIO_Pin_15);GPIO_SetBits(GPIOB, GPIO_Pin_13 | GPIO_Pin_14);PrintChar("Left");delay_ms(200);GPIO_SetBits(GPIOB, GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15);break;  //左转
			case 's'	: GPIO_SetBits(GPIOB, GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15);PrintChar("Stop");break;  //停止
			case 'u' :	TIM_SetCompare3(TIM2,60);TIM_SetCompare4(TIM2,60);break;
			case 'd' :	TIM_SetCompare3(TIM2,40);TIM_SetCompare4(TIM2,40);break;
			//default : k = 0;break;
		}
		/*if(count_speed!=100){
		TIM_SetCompare3(TIM2,count_speed);
		TIM_SetCompare4(TIM2,count_speed);
		}*/
	}
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
