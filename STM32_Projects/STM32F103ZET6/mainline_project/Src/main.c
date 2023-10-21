/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "gpio.h"
/* Private includes ----------------------------------------------------------*/

/* USER CODE BEGIN Includes */
#ifdef LED_BREATH_TEST
  #include "led.h"
  #include "pwm.h"
#endif /*LED_BREATH_TEST*/

#ifdef UART_TEST
  #include "uart.h"
#endif /*UART_TEST*/

#ifdef IIC_OLED_TEST
  #include "iic.h"
  #include "oled.h"
#endif /*IIC_OLED_TEST*/

#ifdef KEY_TEST
  #include "key.h"
  #include "btim.h"
  #include "led.h"
#endif /*KEY_TEST*/

#ifdef RELAY_TEST
  #include "relay.h"
#endif /*RELAY_TEST*/

#ifdef MOTOR_TEST
#include "motor.h"
#include "uart.h"
#include "encoder.h"
#endif /*MOTOR_TEST*/
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

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */
	
  /* Configure the system clock */
  SystemClock_Config();
  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */

  #ifdef UART_TEST
    uart_debug_init();
  #endif /*UART_TEST*/

  #ifdef IIC_OLED_TEST
    OLED_Init();
  #endif /*IIC_OLED_TEST*/

  #ifdef RELAY_TEST
    Relay_Init();
  #endif /*RELAY_TEST*/

  #ifdef KEY_TEST
    uint32_t duty = 0;
    Breath_LED_Direction breath_dir = Breath_Positive;
    led_init();
    key_init();
    TIM6_init(1 - 1 , SystemCoreClock / 1000 - 1);
  #endif /*KEY_TEST*/

  #ifdef LED_BREATH_TEST
    uint32_t duty = 0;
    Breath_LED_Direction breath_dir = Breath_Positive;
    led_init();
    breath_led_init();
  #endif /*LED_BREATH_TEST*/

  #ifdef MOTOR_TEST
    bcd_motor_init(90);   /*直流无刷电机驱动初始化*/
    bcd_encoder_init();   /*编码器初始化——测速*/
    uart_debug_init(115200);  /*USART1初始化*/
	  printf("Hello World\r\n");
  #endif /*MOTOR_TEST*/

  /* USER CODE END 2 */

  /* Infinite loop */

  /* USER CODE BEGIN WHILE */
     while (1) 
  {
#ifdef UART_TEST

    if (uart_debug_rx_flag == SET)
    {
      uart_debug_rx_flag = RESET;
      printf("character:\r\n");
      HAL_UART_Transmit(&uart_debug_handle, uart_debug_rx_buffer, 1, 1000);
      while (__HAL_UART_GET_FLAG(&uart_debug_handle, UART_FLAG_TC) != SET);
      printf("\r\n");
    }
    
#endif /*UART_TEST*/

#ifdef RELAY_TEST

        // 打开继电器
        Relay_On();
        HAL_Delay(1000); // 延时1秒

        // 关闭继电器
        Relay_Off();
        HAL_Delay(1000); // 延时1秒
        
#endif /*RELAY_TEST*/

#ifdef KEY_TEST
   switch(key_scan())
    {
      case KEY0_PRESSED_SHORT: // 短按KEY0开启LED呼吸灯
      breath_led_brightness(&breath_dir, &duty);
      HAL_Delay(5);
      break;

      case KEY1_PRESSED_SHORT:
      led_init();
      break;

      case KEY_UP_PRESSED_SHORT:
      led_init();
      break;
      
      case KEY0_PRESSED_LONG: // 长按KEY0关闭LED呼吸灯
      led_init();
      break;

      case KEY1_PRESSED_LONG:
      led_init();
      break;
      
      case KEY_UP_PRESSED_LONG:
      led_init();
      break;
    }
#endif /*KEY_TEST*/

#ifdef LED_BREATH_TEST
  breath_led_brightness(&breath_dir, &duty);
  HAL_Delay(5);
#endif /*LED_BREATH_TEST*/

#ifdef MOTOR_TEST
  printf("motor speed is: %f rpm.\r\n", bcd_motor_init_struct.speed);
  HAL_Delay(1000);
#endif /*MOTOR_TEST*/

#ifdef IIC_OLED_TEST
#endif /*IIC_OLED_TEST*/

}
    /* USER CODE END WHILE */
}

  /* USER CODE BEGIN 3 */
  
  /* USER CODE END 3 */

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

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
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
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

#ifdef  USE_FULL_ASSERT
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
