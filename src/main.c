/**
  ******************************************************************************
  * @file    CAN/Networking/main.c 
  * @author  MCD Application Team
  * @version V3.6.0
  * @date    24-April-2012
  * @brief   Main program body
  ******************************************************************************
  * @attention
  * KL
  * This is derived form the Atollic peripheral examples for the STM3210E-EVAL board which used the STM32F103ZET6.
  * I've re-targeted it to the STM32F103C8T6 board off ebay.  The idea is to do CAN comms.
  *
  * It will transmit CAN frames at about 2Hz and it's bow also got LED debus and UART debug on it.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "platform_config.h"
#define DFLASH 	Delay();	Delay();	Delay();	Delay(); Delay();  STM_EVAL_LEDOn(LED1);	  Delay();	Delay();	Delay();	Delay();	Delay();	STM_EVAL_LEDOff(LED1);

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define __CAN1_USED__
/* #define __CAN2_USED__*/


#define CANx                       CAN1
#define GPIO_CAN                   GPIO_CAN1
#define GPIO_Remapping_CAN         GPIO_Remapping_CAN1
#define GPIO_CAN                   GPIO_CAN1
#define GPIO_Pin_CAN_RX            GPIO_Pin_CAN1_RX
#define GPIO_Pin_CAN_TX            GPIO_Pin_CAN1_TX

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
CAN_InitTypeDef        CAN_InitStructure;
CAN_FilterInitTypeDef  CAN_FilterInitStructure;
CanTxMsg TxMessage;
uint8_t KeyNumber = 0x0;

/* Private function prototypes -----------------------------------------------*/
void NVIC_Config(void);
void CAN_Config(void);
void LED_Display(uint8_t Ledstatus);
void Init_RxMes(CanRxMsg *RxMessage);
void Delay(void);
void Debug(char *Msg);
void GPIO_Configuration(void);
void RCC_Configuration(void);
USART_InitTypeDef USART_InitStructure;

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured,
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f10x_xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f10x.c file
  */

  /* Configures LED 1..4 */
  STM_EVAL_LEDInit(LED1);
  STM_EVAL_LEDOff(LED1);
  DFLASH

  /* NVIC configuration */
  NVIC_Config();
  RCC_Configuration();
  GPIO_Configuration();

  USART_InitStructure.USART_BaudRate = 19200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(USART1, &USART_InitStructure);
  USART_Cmd(USART1, ENABLE);
  Debug("\nZZZZZZZZZZZZZZzzzzzzzzzzzzzzzzzz!!!!!!!!!!!!!!!!!!!!");

  DFLASH

  /* CAN configuration */
  CAN_Config();
  Delay();
  CAN_ITConfig(CANx, CAN_IT_FMP0, ENABLE);

  /* Infinite loop */
  short int x,led;

  while(1) {
    x++;
    if (x == 0) {
      if (led) {
          STM_EVAL_LEDOn(LED1);
          Delay();
      }
      else {
          STM_EVAL_LEDOff(LED1);
          TxMessage.Data[0]++;
          CAN_Transmit(CANx, &TxMessage);
          Delay();
      }
      led ^= 1;
    }
  }//END While
}//END main

/**
  * @brief  Configures the CAN.
  * @param  None
  * @retval None
  */
void CAN_Config(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  
  /* GPIO clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
#ifdef  __CAN1_USED__
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIO_CAN1, ENABLE);
#else /*__CAN2_USED__*/
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIO_CAN1, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIO_CAN2, ENABLE);
#endif  /* __CAN1_USED__ */
  /* Configure CAN pin: RX */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_CAN_RX;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(GPIO_CAN, &GPIO_InitStructure);
  
  /* Configure CAN pin: TX */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_CAN_TX;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIO_CAN, &GPIO_InitStructure);
  
 GPIO_PinRemapConfig(GPIO_Remapping_CAN , DISABLE);
  
  /* CANx Periph clock enable */
#ifdef  __CAN1_USED__
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
#else /*__CAN2_USED__*/
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN2, ENABLE);
#endif  /* __CAN1_USED__ */
  
  
  /* CAN register init */
  CAN_DeInit(CANx);
  CAN_StructInit(&CAN_InitStructure);

  /* CAN cell init */
  CAN_InitStructure.CAN_TTCM = DISABLE;
  CAN_InitStructure.CAN_ABOM = DISABLE;
  CAN_InitStructure.CAN_AWUM = DISABLE;
  CAN_InitStructure.CAN_NART = DISABLE;
  CAN_InitStructure.CAN_RFLM = DISABLE;
  CAN_InitStructure.CAN_TXFP = DISABLE;
  CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;
  
  /* CAN Baudrate = 1MBps*/
  CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;
  CAN_InitStructure.CAN_BS1 = CAN_BS1_3tq;
  CAN_InitStructure.CAN_BS2 = CAN_BS2_5tq;
  CAN_InitStructure.CAN_Prescaler = 4;
  CAN_Init(CANx, &CAN_InitStructure);

  /* CAN filter init */
#ifdef  __CAN1_USED__
  CAN_FilterInitStructure.CAN_FilterNumber = 0;
#else /*__CAN2_USED__*/
  CAN_FilterInitStructure.CAN_FilterNumber = 14;
#endif  /* __CAN1_USED__ */
  CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
  CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
  CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;
  CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
  CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;
  CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
  CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 0;
  CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
  CAN_FilterInit(&CAN_FilterInitStructure);
  
  /* Transmit */
  TxMessage.StdId = 0x321;
  TxMessage.ExtId = 0x01;
  TxMessage.RTR = CAN_RTR_DATA;
  TxMessage.IDE = CAN_ID_STD;
  TxMessage.DLC = 1;
}

/**
  * @brief  Configures the NVIC for CAN.
  * @param  None
  * @retval None
  */
void NVIC_Config(void)
{
  NVIC_InitTypeDef  NVIC_InitStructure;

  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
  
#ifndef STM32F10X_CL
#ifdef  __CAN1_USED__
  NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
#else  /*__CAN2_USED__*/
  /* CAN2 is not implemented in the device */
   #error "CAN2 is implemented only in Connectivity line devices"
#endif /*__CAN1_USED__*/
#else
#ifdef  __CAN1_USED__ 
  NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX0_IRQn;
#else  /*__CAN2_USED__*/
  NVIC_InitStructure.NVIC_IRQChannel = CAN2_RX0_IRQn;
#endif /*__CAN1_USED__*/

#endif /* STM32F10X_CL*/
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

/**
  * @brief  Initializes a Rx Message.
  * @param  CanRxMsg *RxMessage
  * @retval None
  */
void Init_RxMes(CanRxMsg *RxMessage)
{
  uint8_t i = 0;

  RxMessage->StdId = 0x00;
  RxMessage->ExtId = 0x00;
  RxMessage->IDE = CAN_ID_STD;
  RxMessage->DLC = 0;
  RxMessage->FMI = 0;
  for (i = 0;i < 8;i++)
  {
    RxMessage->Data[i] = 0x00;
  }
}

/**
  * @brief  Turn ON/OFF the dedicate led
  * @param  Ledstatus: Led number from 0 to 3.
  * @retval None
  */
void LED_Display(uint8_t Ledstatus)
{

}

/**
  * @brief  Configures the different GPIO ports.
  * @param  None
  * @retval None
  */
void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Configure USARTy Rx as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);


  /* Configure USARTy Tx as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

}


void RCC_Configuration(void)
{
  /* Enable GPIO clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA  |  RCC_APB2Periph_AFIO, ENABLE);

  /* Enable USARTy Clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

}

void Debug(char *Msg)
{
  int i;

  for (i = 0; i < 255; i++) {
    while (!(USART1->SR & USART_SR_TXE)) // empty?
    {
    }
    USART_SendData(USART1, Msg[i]); // tx
    if (Msg[i] == 0) // EOL
      break;
  }
}//END Debug

/**
  * @brief  Delay
  * @param  None
  * @retval None
  */
void Delay(void)
{
  uint32_t nTime = 0x0000;

  for (nTime = 0; nTime < 0x2FFFFF; nTime++) {
  }
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
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


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
