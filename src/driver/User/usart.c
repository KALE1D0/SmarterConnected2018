/******************** (C) COPYRIGHT 2012 WildFire Team ***************************
 * ÎÄ¼şÃû  £ºusart1.c
 * ÃèÊö    £º½«printfº¯ÊıÖØ¶¨Ïòµ½USART1¡£ÕâÑù¾Í¿ÉÒÔÓÃprintfº¯Êı½«µ¥Æ¬»úµÄÊı¾İ
 *           ´òÓ¡µ½PCÉÏµÄ³¬¼¶ÖÕ¶Ë»ò´®¿Úµ÷ÊÔÖúÊÖ¡£         
 * ÊµÑéÆ½Ì¨£º»Û¾»¿ª·¢°å
 * Ó²¼şÁ¬½Ó£º------------------------
 *          | PA9  - USART1(Tx)      |
 *          | PA10 - USART1(Rx)      |
 *           ------------------------
**********************************************************************************/
#include "usart.h"
#include <stdarg.h>
#include "misc.h"
//´®¿Ú½ÓÊÕDMA»º´æ
uint8_t Uart_Rx[UART_RX_LEN] = {0};
/*
 * º¯ÊıÃû£ºUSART1_Config
 * ÃèÊö  £ºUSART1 GPIO ÅäÖÃ,¹¤×÷Ä£Ê½ÅäÖÃ¡£115200 8-N-1
 * ÊäÈë  £ºÎŞ
 * Êä³ö  : ÎŞ
 * µ÷ÓÃ  £ºÍâ²¿µ÷ÓÃ
 */
void USART1_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	//ÉùÃ÷Ò»¸ö½á¹¹Ìå±äÁ¿£¬ÓÃÀ´³õÊ¼»¯GPIO

	USART_InitTypeDef  USART_InitStructure;	  //´®¿Ú½á¹¹Ìå¶¨Òå

	NVIC_InitTypeDef NVIC_InitStructure;//ÖĞ¶Ï½á¹¹Ìå¶¨Òå
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	 //´ò¿ªÊ±ÖÓ
	
	/*  ÅäÖÃGPIOµÄÄ£Ê½ºÍIO¿Ú */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;//TX			   //´®¿ÚÊä³öPA9
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;	    //¸´ÓÃÍÆÍìÊä³ö
	GPIO_Init(GPIOA,&GPIO_InitStructure);  /* ³õÊ¼»¯´®¿ÚÊäÈëIO */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;//RX			 //´®¿ÚÊäÈëPA10
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;		  //Ä£ÄâÊäÈë
	GPIO_Init(GPIOA,&GPIO_InitStructure); /* ³õÊ¼»¯GPIO */


	USART_InitStructure.USART_BaudRate=9600;   //²¨ÌØÂÊÉèÖÃÎª9600	//²¨ÌØÂÊ
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;		//Êı¾İ³¤8Î»
	USART_InitStructure.USART_StopBits=USART_StopBits_1;			//1Î»Í£Ö¹Î»
	USART_InitStructure.USART_Parity=USART_Parity_No;				//ÎŞĞ§Ñé
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None; //Ê§ÄÜÓ²¼şÁ÷
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;	 //¿ªÆô·¢ËÍºÍ½ÓÊÜÄ£Ê½
	USART_Init(USART1,&USART_InitStructure);	/* ³õÊ¼»¯USART1 */
	USART_Cmd(USART1, ENABLE);		   /* Ê¹ÄÜUSART1 */
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//Ê¹ÄÜ»òÕßÊ§ÄÜÖ¸¶¨µÄUSARTÖĞ¶Ï ½ÓÊÕÖĞ¶Ï
	USART_ClearFlag(USART1,USART_FLAG_TC);//Çå³ıUSARTxµÄ´ı´¦Àí±êÖ¾Î»


	/* ÉèÖÃNVIC²ÎÊı */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);    
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn; 	   //´ò¿ªUSART1µÄÈ«¾ÖÖĞ¶Ï
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 	 //ÇÀÕ¼ÓÅÏÈ¼¶Îª0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; 			//ÏìÓ¦ÓÅÏÈ¼¶Îª0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 			 //Ê¹ÄÜ
	NVIC_Init(&NVIC_InitStructure);
}
void USART3_Config(void)
{

	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;	//¶¨Òå´®¿Ú³õÊ¼»¯½á¹¹Ìå

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3 , ENABLE);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB	, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);    
	//Configure USART3 Rx (PB.11) as input floating ¸
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	  
	//USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_BaudRate = 9600;//²¨ÌØÂÊ9600
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//8Î»Êı¾İ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//1¸öÍ£Ö¹Î»
	USART_InitStructure.USART_Parity = USART_Parity_No ;//ÎŞĞ£ÑéÎ»
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//½ûÓÃRTSCTSÓ²¼şÁ÷¿ØÖÆ
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//Ê¹ÄÜ·¢ËÍ½ÓÊÕ


	USART_Init(USART3, &USART_InitStructure); 
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//Ê¹ÄÜ½ÓÊÕÖĞ¶Ï
	USART_Cmd(USART3, ENABLE);
}
void NVIC_Configuration(void)
{
   NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;	 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}


/*
 * º¯ÊıÃû£ºfputc
 * ÃèÊö  £ºÖØ¶¨Ïòc¿âº¯Êıprintfµ½USART1
 * ÊäÈë  £ºÎŞ
 * Êä³ö  £ºÎŞ
 * µ÷ÓÃ  £ºÓÉprintfµ÷ÓÃ
 */
int fputc(int ch, FILE *f)
{
	/* ½«PrintfÄÚÈİ·¢Íù´®¿Ú */
	USART_SendData(USART1, (unsigned char) ch);
//	while (!(USART1->SR & USART_FLAG_TXE));
	while( USART_GetFlagStatus(USART1,USART_FLAG_TC)!= SET);	
	return (ch);
}
/*int fgetc(FILE *f)
{
	
	while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
	return (int)USART_ReceiveData(USART1);
}*/

/*
 * º¯ÊıÃû£ºitoa
 * ÃèÊö  £º½«ÕûĞÎÊı¾İ×ª»»³É×Ö·û´®
 * ÊäÈë  £º-radix =10 ±íÊ¾10½øÖÆ£¬ÆäËû½á¹ûÎª0
 *         -value Òª×ª»»µÄÕûĞÎÊı
 *         -buf ×ª»»ºóµÄ×Ö·û´®
 *         -radix = 10
 * Êä³ö  £ºÎŞ
 * ·µ»Ø  £ºÎŞ
 * µ÷ÓÃ  £º±»USART1_printf()µ÷ÓÃ
 */
static char *itoa(int value, char *string, int radix)
{
	int     i, d;
	int     flag = 0;
	char    *ptr = string;
	
	/* This implementation only works for decimal numbers. */
	if (radix != 10)
	{
	    *ptr = 0;
	    return string;
	}
	
	if (!value)
	{
	    *ptr++ = 0x30;
	    *ptr = 0;
	    return string;
	}
	
	/* if this is a negative value insert the minus sign. */
	if (value < 0)
	{
	    *ptr++ = '-';
	
	    /* Make the value positive. */
	    value *= -1;
	}
	
	for (i = 10000; i > 0; i /= 10)
	{
	    d = value / i;
	
	    if (d || flag)
	    {
	        *ptr++ = (char)(d + 0x30);
	        value -= (d * i);
	        flag = 1;
	    }
	}
	
	/* Null terminate the string. */
	*ptr = 0;
	
	return string;

} /* NCL_Itoa */

/*
 * º¯ÊıÃû£ºUSART1_printf
 * ÃèÊö  £º¸ñÊ½»¯Êä³ö£¬ÀàËÆÓÚC¿âÖĞµÄprintf£¬µ«ÕâÀïÃ»ÓĞÓÃµ½C¿â
 * ÊäÈë  £º-USARTx ´®¿ÚÍ¨µÀ£¬ÕâÀïÖ»ÓÃµ½ÁË´®¿Ú1£¬¼´USART1
 *		     -Data   Òª·¢ËÍµ½´®¿ÚµÄÄÚÈİµÄÖ¸Õë
 *			   -...    ÆäËû²ÎÊı
 * Êä³ö  £ºÎŞ
 * ·µ»Ø  £ºÎŞ 
 * µ÷ÓÃ  £ºÍâ²¿µ÷ÓÃ
 *         µäĞÍÓ¦ÓÃUSART1_printf( USART1, "\r\n this is a demo \r\n" );
 *            		 USART1_printf( USART1, "\r\n %d \r\n", i );
 *            		 USART1_printf( USART1, "\r\n %s \r\n", j );
 */
 

void USART1_printf(USART_TypeDef* USARTx, uint8_t *Data,...)
{
	const char *s;
	int d;   
	char buf[16];
	
	va_list ap;
	va_start(ap, Data);
	
	while ( *Data != 0)     // ÅĞ¶ÏÊÇ·ñµ½´ï×Ö·û´®½áÊø·û
	{				                          
		if ( *Data == 0x5c )  //'\'
	{									  
	switch ( *++Data )
	{
		case 'r':							          //»Ø³µ·û
			USART_SendData(USARTx, 0x0d);
			Data ++;
		break;
		
		case 'n':							          //»»ĞĞ·û
			USART_SendData(USARTx, 0x0a);	
			Data ++;
		break;
		
		default:
			Data ++;
		break;
	}			 
	}
	else if ( *Data == '%')
	{									  //
	switch ( *++Data )
	{				
		case 's':										  //×Ö·û´®
			s = va_arg(ap, const char *);
	for ( ; *s; s++) 
	{
		USART_SendData(USARTx,*s);
		while( USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET );
	}
		Data++;
		break;
	
	case 'd':										//Ê®½øÖÆ
	d = va_arg(ap, int);
	itoa(d, buf, 10);
	for (s = buf; *s; s++) 
	{
		USART_SendData(USARTx,*s);
		while( USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET );
	}
	Data++;
	break;
		 default:
				Data++;
		    break;
	}		 
	} // end of else if 
	else USART_SendData(USARTx, *Data++);
	while( USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET );
	}
}

void USART1_Send_Byte(unsigned char byte)   //´®¿Ú·¢ËÍÒ»¸ö×Ö½Ú
{
        USART_SendData(USART1, byte);        //Í¨¹ı¿âº¯Êı  ·¢ËÍÊı¾İ
        while( USART_GetFlagStatus(USART1,USART_FLAG_TC)!= SET);  
        //µÈ´ı·¢ËÍÍê³É¡£   ¼ì²â USART_FLAG_TC ÊÇ·ñÖÃ1£»    //¼û¿âº¯Êı P359 ½éÉÜ
        
}

//Êä³ö×Ö·û´®
void PrintChar(char *s)
{
	char *p;
	p=s;
	while(*p != '\0')
	{
		USART1_Send_Byte(*p);
		p++;
	}
}
void USART3_Send_Byte(unsigned char byte)
{
	USART_SendData(USART3,byte);
	while(USART_GetFlagStatus(USART3,USART_FLAG_TC));
}
void PrintChar3(char *s)
{
	char *p;
	p=s;
	while(*p!='\0')
	{
		USART3_Send_Byte(*p);
		p++;
	}
	
}

