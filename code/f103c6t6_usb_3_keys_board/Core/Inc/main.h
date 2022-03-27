/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdlib.h"
#define u8 uint8_t
#define u16 uint16_t
#define u32 uint32_t
#define delay_ms HAL_Delay
#define delay_us(x)
#define delayms HAL_Delay
  // extern lwrb_t usart_lwrb;
  // extern uint8_t USART_TX_BUF_PS[];
#define rt_thread_mdelay HAL_Delay    
#define rt_kprintf

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_B_Pin GPIO_PIN_1
#define LED_B_GPIO_Port GPIOA
#define LED_R_Pin GPIO_PIN_2
#define LED_R_GPIO_Port GPIOA
#define LED_G_Pin GPIO_PIN_3
#define LED_G_GPIO_Port GPIOA
#define LED0_Pin GPIO_PIN_4
#define LED0_GPIO_Port GPIOA
#define KEY0_Pin GPIO_PIN_5
#define KEY0_GPIO_Port GPIOA
#define LED1_Pin GPIO_PIN_6
#define LED1_GPIO_Port GPIOA
#define KEY1_Pin GPIO_PIN_7
#define KEY1_GPIO_Port GPIOA
#define LED6_Pin GPIO_PIN_10
#define LED6_GPIO_Port GPIOB
#define LED7_Pin GPIO_PIN_11
#define LED7_GPIO_Port GPIOB
#define S0_Pin GPIO_PIN_12
#define S0_GPIO_Port GPIOB
#define S1_Pin GPIO_PIN_13
#define S1_GPIO_Port GPIOB
#define LED2_Pin GPIO_PIN_14
#define LED2_GPIO_Port GPIOB
#define KEY2_Pin GPIO_PIN_15
#define KEY2_GPIO_Port GPIOB
#define KEY3_Pin GPIO_PIN_4
#define KEY3_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
