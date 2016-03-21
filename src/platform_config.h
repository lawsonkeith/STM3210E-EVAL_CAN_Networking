/**
  ******************************************************************************
  * @file    CAN/Networking/platform_config.h 
  * @author  MCD Application Team
  * @version V3.6.0
  * @date    24-April-2012
  * @brief   Evaluation board specific configuration file.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __PLATFORM_CONFIG_H
#define __PLATFORM_CONFIG_H

/* Includes ------------------------------------------------------------------*/

#ifdef USE_STM32100B_EVAL
 #include "stm32100b_eval.h"
#elif defined USE_STM3210B_EVAL
 #include "stm3210b_eval.h"
#elif defined USE_STM3210E_EVAL
 #include "stm3210e_eval.h" 
#elif defined USE_STM3210C_EVAL
 #include "stm3210c_eval.h"
#elif defined USE_STM32100E_EVAL
 #include "stm32100e_eval.h"
#endif

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Uncomment the line corresponding to the STMicroelectronics evaluation board
   used to run the example */
#if !defined (USE_STM3210B_EVAL) &&  !defined (USE_STM3210E_EVAL) &&  !defined (USE_STM3210C_EVAL)
 //#define USE_STM3210B_EVAL
 #define USE_STM3210E_EVAL
 //#define USE_STM3210C_EVAL
#endif

/* Define the STM32F10x hardware depending on the used evaluation board */
#ifdef USE_STM3210B_EVAL
  #define RCC_APB2Periph_GPIO_CAN1    RCC_APB2Periph_GPIOD
  #define GPIO_Remapping_CAN1         GPIO_Remap2_CAN1
  #define GPIO_CAN1                   GPIOD  
  #define GPIO_Pin_CAN1_RX            GPIO_Pin_0
  #define GPIO_Pin_CAN1_TX            GPIO_Pin_1

#elif defined USE_STM3210E_EVAL
  #define RCC_APB2Periph_GPIO_CAN1    RCC_APB2Periph_GPIOB
  #define GPIO_Remapping_CAN1         GPIO_Remap1_CAN1
  #define GPIO_CAN1                   GPIOB
  #define GPIO_Pin_CAN1_RX            GPIO_Pin_8
  #define GPIO_Pin_CAN1_TX            GPIO_Pin_9

#elif defined USE_STM3210C_EVAL
  #define RCC_APB2Periph_GPIO_CAN1    RCC_APB2Periph_GPIOD
  #define GPIO_Remapping_CAN1         GPIO_Remap2_CAN1
  #define GPIO_CAN1                   GPIOD  
  #define GPIO_Pin_CAN1_RX            GPIO_Pin_0
  #define GPIO_Pin_CAN1_TX            GPIO_Pin_1
  
  #define RCC_APB2Periph_GPIO_CAN2    RCC_APB2Periph_GPIOB
  #define GPIO_Remapping_CAN2         GPIO_Remap_CAN2
  #define GPIO_CAN2                   GPIOB  
  #define GPIO_Pin_CAN2_RX            GPIO_Pin_5
  #define GPIO_Pin_CAN2_TX            GPIO_Pin_6
#endif /* USE_STM3210B_EVAL */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#endif /* __PLATFORM_CONFIG_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
