#include "key.h"
//#include "stm32f10x.h"
/*
 * ��������key_GPIO_Config
 * ����  ������LED�õ���I/O��
 * ����  ����
 * ���  ����
*/

void GPIO_KEY_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Configure KEY1 Button */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14|GPIO_Pin_13;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

}


u8 ReadKeyDown(void)
{
  /* 1 key is pressed */
  if(!GPIO_ReadInputDataBit(GPIOA , GPIO_Pin_14)&&!GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_13))
  {
    return 1; 
  }	
 
  /* No key is pressed */
  else 
  {
    return 0;
  }
}
