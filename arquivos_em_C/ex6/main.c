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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
static void MX_GPIO_Init(void);
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
	int8_t disp7seg[16][7] = // Números de 0 a 9 para LCD de 7 Segmentos
	{
	  //{A,B,C,D,E,F,G}
		{1,1,1,1,1,1,0},    //0
		{0,1,1,0,0,0,0},    //1
		{1,1,0,1,1,0,1},    //2
		{1,1,1,1,0,0,1},    //3
		{0,1,1,0,0,1,1},    //4
		{1,0,1,1,0,1,1},    //5
		{1,0,1,1,1,1,1},    //6
		{1,1,1,0,0,0,0},    //7
		{1,1,1,1,1,1,1},    //8
		{1,1,1,1,0,1,1},    //9
		{1,1,1,0,1,1,1},    //A
		{0,0,1,1,1,1,1},    //B
		{1,0,0,1,1,1,0},    //C
		{0,1,1,1,1,0,1},    //D
		{1,0,0,1,1,1,1},    //E
		{1,0,0,0,1,1,1},    //F
	  //{A,B,C,D,E,F,G}
	};
	int8_t num = 0;
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

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {/* estava acontecendo um bug no display,  quando nenhum botao era pressionado nao aparecia o seu estado atual no display,
	essa parte serve para resolver isso. Antes sempre aparecia o numero 8.
	configurando display. */
	  if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0)==1 && HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1)==1){ // verifica se nenhum botão esta pressionado
		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, !disp7seg[num][0]);                          //seg_A
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, !disp7seg[num][1]);                        //seg_B
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, !disp7seg[num][2]);                        //seg_C
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, !disp7seg[num][3]);                        //seg_D
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9,  !disp7seg[num][4]);                        //seg_E
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8,  !disp7seg[num][5]);                        //seg_F
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5,  !disp7seg[num][6]);                        //seg_G
			HAL_Delay(200);
	  }

	  if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0)==0){                                           // verifica se SW1 esta pressionado.
		num++;                                                                               // faz encremento.
		if (num > 15){                                                                       // verifica se estourou e aciona o buzzer.
			while (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0)==0){
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, 1);                                    // liga o buzzer.

			}
		num = 15;                                                                            // apos o estouro o valor se corrige.
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, 0);                                            // desliga o buzzer.
		}
		// configurando display
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, !disp7seg[num][0]);  							 // seg_A
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, !disp7seg[num][1]);  							 // seg_B
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, !disp7seg[num][2]);  							 // seg_C
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, !disp7seg[num][3]);  							 // seg_D
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9,  !disp7seg[num][4]);  							 // seg_E
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8,  !disp7seg[num][5]);  							 // seg_F
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5,  !disp7seg[num][6]);  							 // seg_G
		HAL_Delay(200);
	  }
	  if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1)==0){                                           // leitura do botao SW2.
		num--;                                                                               // faz encremento.
		if (num < 0){                                                                        // verifica se estourou e aciona o buzzer.
			while (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1)==0){
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, 1);                                    // liga o buzzer.

			}
		num = 0;                                                                             // apos o estouro o valor se corrige.
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, 0);                                            // desliga o buzzer.
		}
		// configurando display
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, !disp7seg[num][0]);  							 // seg_A
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, !disp7seg[num][1]);  							 // seg_B
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, !disp7seg[num][2]);  							 // seg_C
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, !disp7seg[num][3]);  							 // seg_D
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9,  !disp7seg[num][4]);  							 // seg_E
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8,  !disp7seg[num][5]);  							 // seg_F
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5,  !disp7seg[num][6]);  							 // seg_G
		HAL_Delay(200);
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

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15
                          |GPIO_PIN_5|GPIO_PIN_8|GPIO_PIN_9, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET);

  /*Configure GPIO pins : PB0 PB1 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PB12 PB13 PB14 PB15
                           PB5 PB8 PB9 */
  GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15
                          |GPIO_PIN_5|GPIO_PIN_8|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PA10 */
  GPIO_InitStruct.Pin = GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

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
