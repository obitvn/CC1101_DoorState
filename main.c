/**
  ******************************************************************************
  * @file    Project/STM8L15x_StdPeriph_Template/main.c
  * @author  MCD Application Team
  * @version V1.6.1
  * @date    30-September-2014
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm8l15x.h"
#include "cc1101.h"


/** @addtogroup STM8L15x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/


uint8_t SendBuffer[15] = "123456789012";

#define TX              0       // ????
#define RX              1       // ????
#define IDLE          	2       // ????
#define ACK_LENGTH      60   	// ??????? 
#define ACK_CNT					ACK_LENGTH/6
#define SEND_LENGTH     60      // ?????????
#define RECV_TIMEOUT		2000    // ????2s
/* Private defines -----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

#define ADD_UNIQUEID 0x4925
uint32_t id_24bit;
uint8_t PacketRF[13];


void Delay_us(uint32_t us);
void ReadUniqueID(uint8_t *id);

void ReadUniqueID(uint8_t *id)
{
  uint16_t val;
  for(int i=0; i<12; i++)
  {
    val = ADD_UNIQUEID + i ;
    id[i] = *(PointerAttr uint8_t *) (uint16_t)val;
  }
}

uint32_t EndingID(void);

uint32_t EndingID()
{
  uint8_t id_device[12];
  uint32_t id, a, b, c;
  ReadUniqueID(id_device);
  a = id_device[11];
  b = id_device[10];
  c = id_device[9];
  id = a<<16|b<<8|c;
  return id;
  
}

void Delay_us(uint32_t us)
{
  for(uint32_t i=us;i > 0; --i) 
  {
    nop();
    nop();
    nop();
    nop();
    nop();
    nop();
    nop();
    nop();
    nop();
    nop();
    nop();
  }
}

void RF_Initial(uint8_t addr, uint16_t sync, uint8_t mode);


void RF_Initial(uint8_t addr, uint16_t sync, uint8_t mode)
{
	CC1101Init(addr, sync);                       			// ???CC1101???
	if(mode == RX)				{CC1101SetTRMode(RX_MODE);}		// ????
	else if(mode == TX)		{CC1101SetTRMode(TX_MODE);}   // ????
	else
	{
		CC1101SetIdle();																	// ????,???sleep??
		CC1101WORInit();																	// ??????????
		CC1101SetWORMode();
	}
}


void GetIdAndConvertData(uint8_t state);

void GetIdAndConvertData(uint8_t state)
{
  uint32_t add, mask,draft;
  uint8_t array13[13], slide=0;
  id_24bit=EndingID();
  if(state==1) // opendoor
  {
    add = 1L<<24 | id_24bit ;
  }
  else
  {
    add = 1L<<25 | id_24bit ;
  }
  mask = 0x03; // 1100 0000 0000 0000
  for(int i=0; i<13; i++)
  {
    draft = add & mask;
    array13[i] = draft>> slide;
    slide = (i+1)*2;
    mask = mask << 2;
  }
  for (int i=0; i<13; i++)
  {
    switch (array13[i])
    {
    case 0x00:  //0b00000000:
      PacketRF[i] = 0x77;
      break;
    case 0x01:  //0b00000001:
      PacketRF[i] = 0x71;
      break;
    case 0x02:  //0b00000010: 
      PacketRF[i] = 0x17;
      break;
    case 0x03:  //0b00000011:
      PacketRF[i] = 0x11;
      break;
    }
  }
  nop();     
}

void ReGPIO(void);

void ReGPIO()
{
    GPIO_Init(CC1101_SPI_SCK_GPIO_PORT, CC1101_SPI_SCK_PIN, GPIO_Mode_In_FL_No_IT);
    GPIO_Init(CC1101_SPI_MOSI_GPIO_PORT, CC1101_SPI_MOSI_PIN,GPIO_Mode_In_FL_No_IT);
    GPIO_Init(CC1101_SPI_CSN_GPIO_PORT, CC1101_SPI_CSN_PIN, GPIO_Mode_In_FL_No_IT);
    GPIO_Init(CC1101_SPI_MISO_GPIO_PORT, CC1101_SPI_MISO_PIN, GPIO_Mode_In_FL_No_IT); 
    GPIO_Init(CC1101_IRQ_GPIO_PORT, CC1101_IRQ_PIN, GPIO_Mode_In_FL_No_IT); 
    GPIO_Init(CC1101_GDO2_GPIO_PORT, CC1101_GDO2_PIN, GPIO_Mode_In_FL_No_IT); 
    GPIO_Init(GPIOC, GPIO_Pin_4, GPIO_Mode_In_FL_No_IT);
    GPIO_Init(GPIOC, GPIO_Pin_0, GPIO_Mode_In_FL_No_IT);
    GPIO_Init(GPIOC, GPIO_Pin_1, GPIO_Mode_In_FL_No_IT);
}



/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
void main(void)
{
    /* Select HSE as system clock source */
  CLK_SYSCLKSourceSwitchCmd(ENABLE);
  CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_HSI);
  
  /*High speed external clock prescaler: 1*/
  CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);

  while (CLK_GetSYSCLKSource() != CLK_SYSCLKSource_HSI)
  {}

  /* Enable SPI clock */
  CLK_PeripheralClockConfig(CLK_Peripheral_SPI1, ENABLE);
  /* Enable DMA clock */
 // CLK_PeripheralClockConfig(CLK_Peripheral_DMA1, ENABLE);
  GPIO_Init(GPIOC, GPIO_Pin_5, GPIO_Mode_In_FL_IT);
  /* Infinite loop */
  EXTI_SetPinSensitivity(EXTI_Pin_5,EXTI_Trigger_Rising_Falling); 
  enableInterrupts();
  EXTI_ClearITPendingBit(EXTI_IT_Pin5);
  
  while (1)
  {

      if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_5) == 0)
      {
        GPIO_Init(GPIOC, GPIO_Pin_4, GPIO_Mode_Out_PP_High_Slow);
        Delay_us(20000);
        GetIdAndConvertData(1);
        RF_Initial(0, 0, RX);
        Delay_us(10000);
        for(int i=0; i<5; i++)
        {
        CC1101SendPacket(PacketRF, 13, ADDRESS_CHECK); 
        Delay_us(9000);
        }
        GPIO_ResetBits(GPIOC, GPIO_Pin_4);
        SPI_DeInit(SPI1);
        ReGPIO();
        EXTI_SetPinSensitivity(EXTI_Pin_5,EXTI_Trigger_Rising_Falling); 
        enableInterrupts();
        EXTI_ClearITPendingBit(EXTI_IT_Pin5);
      }
      else 
      {
        GPIO_Init(GPIOC, GPIO_Pin_4, GPIO_Mode_Out_PP_High_Slow);
        Delay_us(20000);
        GetIdAndConvertData(0);
        RF_Initial(0, 0, RX);
        Delay_us(10000);
        for(int i=0; i<5; i++)
        {
        CC1101SendPacket(PacketRF, 13, ADDRESS_CHECK); 
        Delay_us(9000);
        }
        GPIO_ResetBits(GPIOC, GPIO_Pin_4);
        SPI_DeInit(SPI1);
        ReGPIO();
        EXTI_SetPinSensitivity(EXTI_Pin_5,EXTI_Trigger_Rising_Falling); 
        enableInterrupts();
        EXTI_ClearITPendingBit(EXTI_IT_Pin5);
      }
      EXTI_ClearITPendingBit(EXTI_IT_Pin5);
      halt();

  }
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
