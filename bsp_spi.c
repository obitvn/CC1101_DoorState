/**
  ******************************************************************************
  * @file    bsp_spi.h
  * @author  phoenix
  * @version V1.0.0
  * @date    20-October-2017
  * @brief   This file provides set of firmware functions to manage Leds ,
  *          push-button and spi available on STM32F4-Discovery Kit from STMicroelectronics.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */ 

#include "bsp_spi.h"


 /**
  * @brief  配置嵌套向量中断控制器NVIC
  * @param  无
  * @retval 无
  */
//static void NVIC_Configuration(void)
//{
//  NVIC_InitTypeDef NVIC_InitStructure;
//  
//  /* 配置NVIC为优先级组1 */
//  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
//  
//  /* 配置中断源：GDO2 */
//  NVIC_InitStructure.NVIC_IRQChannel = CC1101_GDO2_EXTI_IRQ;
//  /* 配置抢占优先级:1 */
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
//  /* 配置子优先级:1 */
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
//  /* 配置中断通道 */
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//  NVIC_Init(&NVIC_InitStructure);
//}

/**
  * @brief  GPIO_Initial function
  * @param  None
  * @retval None
  */
void GPIO_Initial(void)
{
  /*
    GPIO_InitTypeDef GPIO_InitStructure;
//		EXTI_InitTypeDef EXTI_InitStructure;
    //开启GPIO外设时钟
    RCC_AHB1PeriphClockCmd(LED_GPIO_CLK, ENABLE);
    RCC_AHB1PeriphClockCmd(CC1101_IRQ_GPIO_CLK, ENABLE);
    RCC_AHB1PeriphClockCmd(CC1101_GDO2_GPIO_CLK, ENABLE);
    
		//使能 SYSCFG 时钟 ,使用GPIO外部中断时必须使能SYSCFG时钟
//		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);  

		//配置NVIC
//		NVIC_Configuration();
	
    //配置LED3的GPIO引脚
    GPIO_InitStructure.GPIO_Pin = LED3_Orange_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LED_GPIO_PORT, &GPIO_InitStructure);
    
    //配置LED4的GPIO引脚
    GPIO_InitStructure.GPIO_Pin = LED4_Green_PIN;
    GPIO_Init(LED_GPIO_PORT, &GPIO_InitStructure);

    //配置LED5的GPIO引脚
    GPIO_InitStructure.GPIO_Pin = LED5_Red_PIN;
    GPIO_Init(LED_GPIO_PORT, &GPIO_InitStructure);
    
    //配置LED6的GPIO引脚
    GPIO_InitStructure.GPIO_Pin = LED6_Blue_PIN;
    GPIO_Init(LED_GPIO_PORT, &GPIO_InitStructure);
    
    //配置IRQ的GPIO引脚
    GPIO_InitStructure.GPIO_Pin = CC1101_IRQ_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(CC1101_IRQ_GPIO_PORT, &GPIO_InitStructure);
    
    //配置GDO2的GPIO引脚
    GPIO_InitStructure.GPIO_Pin = CC1101_GDO2_PIN;
    GPIO_Init(CC1101_GDO2_GPIO_PORT, &GPIO_InitStructure);
    
//		//连接EXTI中断源到GDO2引脚
//		SYSCFG_EXTILineConfig(CC1101_GDO2_EXTI_PORTSOURCE,CC1101_GDO2_EXTI_PINSOURCE);

//		//选择EXTI中断源
//		EXTI_InitStructure.EXTI_Line = CC1101_GDO2_EXTI_LINE;
//		//中断模式
//		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
//		//下降沿触发
//		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  
//		//使能中断/事件线
//		EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//		EXTI_Init(&EXTI_InitStructure);
}
*/
    GPIO_Init(CC1101_SPI_SCK_GPIO_PORT, CC1101_SPI_SCK_PIN, GPIO_Mode_Out_PP_High_Fast);
    GPIO_Init(CC1101_SPI_MOSI_GPIO_PORT, CC1101_SPI_MOSI_PIN, GPIO_Mode_Out_PP_High_Fast);
    GPIO_ExternalPullUpConfig(CC1101_SPI_SCK_GPIO_PORT, CC1101_SPI_SCK_PIN | CC1101_SPI_MOSI_PIN, ENABLE);
    GPIO_Init(CC1101_SPI_CSN_GPIO_PORT, CC1101_SPI_CSN_PIN, GPIO_Mode_Out_PP_High_Fast);
    GPIO_Init(CC1101_SPI_MISO_GPIO_PORT, CC1101_SPI_MISO_PIN, GPIO_Mode_In_FL_No_IT); 
    GPIO_Init(CC1101_IRQ_GPIO_PORT, CC1101_IRQ_PIN, GPIO_Mode_In_FL_No_IT); 
    GPIO_Init(CC1101_GDO2_GPIO_PORT, CC1101_GDO2_PIN, GPIO_Mode_In_FL_No_IT); 
}
/**
  * @brief  SPI_Initial function
  * @param  None
  * @retval None
  */
void SPI_Initial(void)
{
    GPIO_Initial();
    SPI_DeInit(SPI1);
    SPI_Init(SPI1,SPI_FirstBit_MSB,SPI_BaudRatePrescaler_2,SPI_Mode_Master,SPI_CPOL_Low,SPI_CPHA_1Edge,SPI_Direction_2Lines_FullDuplex,SPI_NSS_Soft,(uint8_t)0x07);
    SPI_Cmd(SPI1,ENABLE);
}

/*===========================================================================
* 函数 ：SPI_ExchangeByte() => 通过SPI进行数据交换                          * 
* 输入 ：需要写入SPI的值                                                    * 
* 输出 ：通过SPI读出的值                                                    * 
============================================================================*/
uint8_t SPI_ExchangeByte(uint8_t input)
{
  SPI_SendData(SPI1,input);
    //printf("spi send data:%x\n",input);
	while (SPI_GetFlagStatus(SPI1,SPI_FLAG_BSY)){};   // 等待数据传输完成	
	//while (SPI_GetFlagStatus(SPI_FLAG_RXNE)){}; // 等待数据接收完成
    //printf("spi receive data:%x\n",SPI_ReceiveData(SPIx));
	return (SPI_ReceiveData(SPI1));
}

/******************* END OF FILE ******************/
