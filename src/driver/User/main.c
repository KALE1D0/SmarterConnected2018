/******************** (C) COPYRIGHT 2012 WildFire Team **************************
 * �ļ���  ��main.c
**********************************************************************************/
#include "stm32f10x.h"
#include "led.h"
#include "key.h"
#include "usart.h"
#include "motor.h"
//#include "SysTick.h"
//#include "timer.h"
//#include "UltrasonicWave.h"
u8 u8BluetoothValue;
void delay(vu32 nCount)
{
  for(; nCount != 0; nCount--);
}

int main(void)
{	
	 //u8 KeyNum = 0;
//	u8 u8BluetoothValue;
	//SystemInit();                   //=====ϵͳ��ʼ��
//	Timerx_Init(5000,7199);				   //��ʱ��TIM1
//	UltrasonicWave_Configuration(); 	   //��������ʼ������ IO�ڼ��ж�����		
	/* LED �˿ڳ�ʼ�� */
	//LED_GPIO_Config();
	//GPIO_KEY_Config();
	USART1_Config();
	USART3_Config();
	NVIC_Configuration();
	TIM2_PWM_Init();
	MOTOR_GPIO_Config();
  TIM_SetCompare3(TIM2,50);
	TIM_SetCompare4(TIM2,50);
	
	//GPIO_SetBits(GPIOB, GPIO_Pin_13);
	GPIO_SetBits(GPIOB, GPIO_Pin_13 | GPIO_Pin_15);GPIO_SetBits(GPIOB, GPIO_Pin_12 | GPIO_Pin_14); 
	//GPIO_SetBits(GPIOB, GPIO_Pin_11 | GPIO_Pin_12| GPIO_Pin_14| GPIO_Pin_15);
	//LED1( ON );
	while (1)
	{
			
	}
}
	


