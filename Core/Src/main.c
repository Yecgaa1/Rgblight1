/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "deal.h"


#define RXBUFFERSIZE  256     //最大接收字节数
char RxBuffer[RXBUFFERSIZE];   //接收数据
uint8_t aRxBuffer;            //接收中断缓冲
uint8_t Uart1_Rx_Cnt = 0;        //接收缓冲计数


int pwmVal = 0;
int red = 0, blue = 0, green = 0;//目标的量
int nred = 0, nblue = 0, ngreen = 0;//现在的量
int tred = 0, tblue = 0, tgreen = 0;//临时的量
bool flag = false;//true为呼吸
bool i = true;//down
int tmp;
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
int main(void) {
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
    MX_TIM2_Init();
    MX_USART1_UART_Init();
    /* USER CODE BEGIN 2 */

    HAL_UART_Receive_IT(&huart1, (uint8_t *) &aRxBuffer, 1);
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
    //htim2.Instance->CCR1 =700;//red
    //htim2.Instance->CCR2 =750;//green
    //htim2.Instance->CCR3 =999;//blue
    red = 255;
    //htim2.Instance->CCR1 = (3.91 * red);//red
    //htim2.Instance->CCR1 =;//red
    green = 180;

    //htim2.Instance->CCR2 = (3.91 * green) ;//green
    //htim2.Instance->CCR2 = green;//green
    blue = 0;

    //htim2.Instance->CCR3 = (3.91 * blue);//blue
    //htim2.Instance->CCR3 = blue;//blue

    //For test


    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    while (1) {

        HAL_Delay(10);
        if (flag) {
            HAL_Delay(100);
            if (i) {
                if ((nred < 13 && nred > 10) || (ngreen < 13 && nred > 10) || (nblue < 13 && nred > 10)) {
                    while (10 < nred || 10 < ngreen || 10 < nblue) {
                        if (10 < nred)
                            htim2.Instance->CCR1 = (3.91 * --nred);
                        if (10 < ngreen)
                            htim2.Instance->CCR2 = (3.91 * --ngreen);
                        if (10 < nblue)
                            htim2.Instance->CCR3 = (3.91 * --nblue);
                        HAL_Delay(10);
                    }
                    while (nred||ngreen||nblue) {
                        if (nred>0)
                            htim2.Instance->CCR1 = (3.91 * --nred);

                        if (ngreen>0)
                            htim2.Instance->CCR2 = (3.91 * --ngreen);

                        if (nblue >0)
                            htim2.Instance->CCR3 = (3.91 * --nblue);


                        HAL_Delay(10);
                    }
                     i = false;
                    nred = red;
                    ngreen = green;
                    nblue = blue;
                    HAL_Delay(1000);
                } else {
                    tred = nred / 1.2;
                    tgreen = ngreen / 1.2;
                    tblue = nblue / 1.2;
                    while (tblue != nblue || tgreen != ngreen || tred != nred) {
                        if (tred != nred)
                            htim2.Instance->CCR1 = (3.91 * --nred);
                        if (tgreen != ngreen)
                            htim2.Instance->CCR2 = (3.91 * --ngreen);
                        if (tblue != nblue)
                            htim2.Instance->CCR3 = (3.91 * --nblue);
                        HAL_Delay(20);
                    }

                }

            } else {

                if ((nred < 13 && nred > 10) || (ngreen < 13 && nred > 10) || (nblue < 13 && nred > 10)) {
                    while (10 < nred || 10 < ngreen || 10 < nblue) {
                        if (10 < nred)
                            htim2.Instance->CCR1 = (3.91 * (red - (--nred)));
                        if (10 < ngreen)
                            htim2.Instance->CCR2 = (3.91 * (green - (--ngreen)));
                        if (10 < nblue)
                            htim2.Instance->CCR3 = (3.91 * (blue - (--nblue)));
                        HAL_Delay(10);
                    }
                    while (nred||ngreen||nblue) {
                        if (nred>0)
                            htim2.Instance->CCR1 = (3.91 * (red - (--nred)));
                        if (ngreen>0)
                            htim2.Instance->CCR2 = (3.91 * (green - (--ngreen)));
                        if (nblue>0)
                            htim2.Instance->CCR3 = (3.91 * (blue - (--nblue)));
                        HAL_Delay(10);
                    }
                    nred = red;
                    ngreen = green;
                    nblue = blue;
                    i = true;
                    HAL_Delay(1000);
                } else {
                    tred = nred / 1.2;
                    tgreen = ngreen / 1.2;
                    tblue = nblue / 1.2;
                    while (tblue != nblue || tgreen != ngreen || tred != nred) {
                        if (tred != nred)
                            htim2.Instance->CCR1 = (3.91 * (red - (--nred)));
                        if (tgreen != ngreen)
                            htim2.Instance->CCR2 = (3.91 * (green - (--ngreen)));
                        if (tblue != nblue)
                            htim2.Instance->CCR3 = (3.91 * (blue - (--nblue)));
                        HAL_Delay(20);
                    }

                }
            }
        } else {

            if (red != nred) {
                if (red > nred)
                    htim2.Instance->CCR1 = (3.91 * nred++);//red
                else
                    htim2.Instance->CCR1 = (3.91 * nred--);//red
            }
            if (green != ngreen) {
                if (green > ngreen)
                    htim2.Instance->CCR2 = (3.91 * ngreen++);//green
                else
                    htim2.Instance->CCR2 = (3.91 * ngreen--);//green
            }
            if (blue != nblue) {
                if (blue > nblue)
                    htim2.Instance->CCR3 = (3.91 * nblue++);//blue
                else
                    htim2.Instance->CCR3 = (3.91 * nblue--);//blue
            }
            if (red == nred && green == ngreen && blue == nblue) {
                flag = true;
            }
        }
    }
    /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void) {
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
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        Error_Handler();
    }
    /** Initializes the CPU, AHB and APB buses clocks
    */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                  | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
        Error_Handler();
    }
}

/* USER CODE BEGIN 4 */
/* USER CODE BEGIN 4 */

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    /* Prevent unused argument(s) compilation warning */
    UNUSED(huart);
    /* NOTE: This function Should not be modified, when the callback is needed,
             the HAL_UART_TxCpltCallback could be implemented in the user file
     */

    if (Uart1_Rx_Cnt >= 255)  //溢出判断
    {
        Uart1_Rx_Cnt = 0;
        memset(RxBuffer, 0x00, sizeof(RxBuffer));
        HAL_UART_Transmit(&huart1, (uint8_t *) "数据溢出", 10, 0xFFFF);

    } else {
        RxBuffer[Uart1_Rx_Cnt++] = aRxBuffer;   //接收数据转存

        if (RxBuffer[Uart1_Rx_Cnt - 1] == '#') //判断结束位
        {
            HAL_UART_Transmit(&huart1, (uint8_t *) &RxBuffer, Uart1_Rx_Cnt, 0xFFFF); //将收到的信息发送出去
            while (HAL_UART_GetState(&huart1) == HAL_UART_STATE_BUSY_TX);//检测UART发送结束
            char dest1[2] = {""};
            strncpy(dest1, RxBuffer, 2);
            char dest2[2] = {""};
            strncpy(dest2, RxBuffer + 2, 2);
            char dest3[2] = {""};
            strncpy(dest3, RxBuffer + 4, 2);
            if (!i) {
                nred = red - nred;
                ngreen = green - ngreen;
                nblue = blue - nblue;
            }
            sscanf(dest1, "%x", &red);
            //htim2.Instance->CCR1 = (3.1 * i);//red

            sscanf(dest2, "%x", &green);
            //htim2.Instance->CCR2 = (3.52 * i) ;//green

            sscanf(dest3, "%x", &blue);
            flag = false;
            //htim2.Instance->CCR3 = (3.91 * i);//blue
            //HAL_UART_Transmit(&huart1, (uint8_t *)&RxBuffer, sizeof(RxBuffer),0xFFFF); //将收到的信息发送出去
            //while(HAL_UART_GetState(&huart1) == HAL_UART_STATE_BUSY_TX);//检测UART发送结束
            Uart1_Rx_Cnt = 0;
            memset(RxBuffer, 0x00, sizeof(RxBuffer)); //清空数组
        }
    }

    HAL_UART_Receive_IT(&huart1, (uint8_t *) &aRxBuffer, 1);   //再开启接收中断
}








/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void) {
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */

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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
