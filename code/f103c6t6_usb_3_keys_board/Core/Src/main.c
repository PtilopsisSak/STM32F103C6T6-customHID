/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "usb_device.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "mouse.h"
#include "keyboard.h"
#include "touch_screen.h"
#include "custom_control.h"

#include "psk_hid.h"

#include "psk_multi_button.h"
#include "psk_ps.h"
#include "psk_led.h"
#include "psk_switch.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void shutdown(void)
{
  keyboard_press_sp_key(LEFT_GUI, 2);
  keyboard_press_char('x', 2);
  keyboard_delay(100);
  keyboard_press_sp_key(LEFT_GUI, 2);
  keyboard_press_char('x', 2);
  keyboard_delay(50);
  keyboard_press_str("uuuuuuuuuuuuuuuuuuu\n", 0);
}
void USB_Reset(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);
  /*Configure GPIO pin : PA12 */
  GPIO_InitStruct.Pin = GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);
  HAL_Delay(65);
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET);
}
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim == (&htim1)) // 2.5msÒ»´Î
  {
    static uint8_t i;

    if (i)
    {
      send_keyboard_data();
      send_custom_control_data();
    }
    else
    {
      send_touch_data();
      send_mouse_data();

      led_smooth_change_handle();
    }
    i = !i;
  }
  else if (htim == (&htim3))
  {
    led_soft_pwm_handle();
  }
}
#define ENC_START_VAL 1024

void encode_get(void)
{
  static int8_t en_get;
  en_get = -(__HAL_TIM_GET_COUNTER(&htim2) - ENC_START_VAL);
  if (en_get)
  {
    if (en_get % 2 == 0)
    {
      __HAL_TIM_SetCounter(&htim2, ENC_START_VAL);
    }
    if (en_get > 0)
    {
      custom_press_key(VOL_UP, 1);
    }
    else if (en_get < 0)
    {
      custom_press_key(VOL_DOWN, 1);
    }
  }
}

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
  /* USER CODE BEGIN 1 */
  int i;
  uint32_t tickstart = HAL_GetTick();
  uint32_t wait = 1;

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
  USB_Reset();
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_USB_DEVICE_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */

  mouse_init();
  keyboard_init();
  touch_init();
  custom_init();
  HAL_TIM_Base_Start_IT(&htim1);

  led_set_mode(0, SMOOTH_DIM);
  led_set_mode(2, SMOOTH_DIM);
  led_set_mode(1, SMOOTH_DIM);
  led_set_mode(3, SMOOTH_DIM);

  led_set_mode(5, SMOOTH_ALL);
  led_set_mode(6, SMOOTH_ALL);
  led_set_mode(7, SMOOTH_ALL);

  HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_ALL);
  __HAL_TIM_SetCounter(&htim2, ENC_START_VAL);

  my_button_init();
  HAL_Delay(100);

  HAL_TIM_Base_Start_IT(&htim3);

  scan_switch();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  static uint16_t tick[5];
  static uint16_t tick_max[5] = {5, 5, 100, 500, 1000};
  // static int8_t led
  while (1)
  {
    // HAL_Delay(1);
    tickstart = HAL_GetTick();

    for (i = 0; i < 5; i++)
    {
      if (tick[i] == 0)
      {
        tick[i] = tick_max[i];
        switch (i)
        {
        case 0:
          key_scan();
          button_ticks();
          if (key_scan_code == 0 && (switch_data == 3))
          {
            shutdown();
          }
          break;
        case 1:
          encode_get();
          break;
        case 2:
          scan_switch();
          break;
        case 3:
          if (switch_data == 0)
          {
            led_set_mode(3, SMOOTH_DIM);
            led_set_mode(4, SMOOTH_LIGHT);
            led_set_light(3, 100);
            led_set_light(4, 0);
          }
          else if (switch_data == 1)
          {
            led_set_mode(3, SMOOTH_DIM);
            led_set_mode(4, STEEP);
            led_set_light(3, 100);
            led_set_light(4, 0);
          }
          else if (switch_data == 2)
          {
            led_set_mode(3, STEEP);
            led_set_mode(4, SMOOTH_LIGHT);
            led_set_light(3, 0);
            led_set_light(4, 0);
          }
          break;
        case 4:
          // static uint8_t r, g, b;
          // r = (r + 3) % 200;
          // g = (g + 4) % 200;
          // b = (b + 2) % 200;
          led_set_rgb(rand() & 100, rand() % 100, rand() % 100);
          ps("Hello PC Ptisak %d", tickstart);
          // keyboard_press_key_code(Keypad_Num_Lock_and_Clear11_90____101_104, 30);
          // led_set_rgb(r, g, b);
          break;
        }
      }
      tick[i]--;
    }

    while ((HAL_GetTick() - tickstart) < wait)
    {
    }

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
   * in the RCC_OscInitTypeDef structure.
   */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
   */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL_DIV1_5;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
