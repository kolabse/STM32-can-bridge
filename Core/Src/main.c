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
#include "cmsis_os.h"
#include "usb_device.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "RTC/RTC_utils.h"
#include "CAN/CAN_utils.h"
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
CAN_HandleTypeDef hcan1;
CAN_HandleTypeDef hcan2;

RTC_HandleTypeDef hrtc;

/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for sendTask50ms */
osThreadId_t sendTask50msHandle;
const osThreadAttr_t sendTask50ms_attributes = {
  .name = "sendTask50ms",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityBelowNormal,
};
/* Definitions for sendTask100ms */
osThreadId_t sendTask100msHandle;
const osThreadAttr_t sendTask100ms_attributes = {
  .name = "sendTask100ms",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityBelowNormal,
};
/* Definitions for sendTask200ms */
osThreadId_t sendTask200msHandle;
const osThreadAttr_t sendTask200ms_attributes = {
  .name = "sendTask200ms",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityBelowNormal,
};
/* Definitions for sendTask500ms */
osThreadId_t sendTask500msHandle;
const osThreadAttr_t sendTask500ms_attributes = {
  .name = "sendTask500ms",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityBelowNormal,
};
/* Definitions for sendTask1000ms */
osThreadId_t sendTask1000msHandle;
const osThreadAttr_t sendTask1000ms_attributes = {
  .name = "sendTask1000ms",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityBelowNormal,
};
/* Definitions for sendTask5000ms */
osThreadId_t sendTask5000msHandle;
const osThreadAttr_t sendTask5000ms_attributes = {
  .name = "sendTask5000ms",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityBelowNormal,
};
/* USER CODE BEGIN PV */
uint32_t TxMailbox = 0;
CanMessage CanArray[0x5FF];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_CAN1_Init(void);
static void MX_CAN2_Init(void);
static void MX_RTC_Init(void);
void StartDefaultTask(void *argument);
void sendTask50msHandler(void *argument);
void sendTask100msHandler(void *argument);
void sendTask200msHandler(void *argument);
void sendTask500msHandler(void *argument);
void sendTask1000msHandler(void *argument);
void sendTask5000msHandler(void *argument);

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
  MX_CAN1_Init();
  MX_CAN2_Init();
  MX_RTC_Init();
  /* USER CODE BEGIN 2 */

  uint8_t msgData036[8] = {0x0E, 0x00, 0x03, 0x0F, 0X91, 0x00, 0x01, 0xAC};
  CanMessage msg036 = createCanMessage(36, 8, msgData036);

  canMessageSend(&hcan1, &msg036, &TxMailbox);

  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of sendTask50ms */
  sendTask50msHandle = osThreadNew(sendTask50msHandler, NULL, &sendTask50ms_attributes);

  /* creation of sendTask100ms */
  sendTask100msHandle = osThreadNew(sendTask100msHandler, NULL, &sendTask100ms_attributes);

  /* creation of sendTask200ms */
  sendTask200msHandle = osThreadNew(sendTask200msHandler, NULL, &sendTask200ms_attributes);

  /* creation of sendTask500ms */
  sendTask500msHandle = osThreadNew(sendTask500msHandler, NULL, &sendTask500ms_attributes);

  /* creation of sendTask1000ms */
  sendTask1000msHandle = osThreadNew(sendTask1000msHandler, NULL, &sendTask1000ms_attributes);

  /* creation of sendTask5000ms */
  sendTask5000msHandle = osThreadNew(sendTask5000msHandler, NULL, &sendTask5000ms_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 192;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  RCC_OscInitStruct.PLL.PLLR = 2;
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

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief CAN1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_CAN1_Init(void)
{

  /* USER CODE BEGIN CAN1_Init 0 */

  /* USER CODE END CAN1_Init 0 */

  /* USER CODE BEGIN CAN1_Init 1 */

  /* USER CODE END CAN1_Init 1 */
  hcan1.Instance = CAN1;
  hcan1.Init.Prescaler = 24;
  hcan1.Init.Mode = CAN_MODE_NORMAL;
  hcan1.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan1.Init.TimeSeg1 = CAN_BS1_13TQ;
  hcan1.Init.TimeSeg2 = CAN_BS2_2TQ;
  hcan1.Init.TimeTriggeredMode = DISABLE;
  hcan1.Init.AutoBusOff = ENABLE;
  hcan1.Init.AutoWakeUp = DISABLE;
  hcan1.Init.AutoRetransmission = DISABLE;
  hcan1.Init.ReceiveFifoLocked = DISABLE;
  hcan1.Init.TransmitFifoPriority = ENABLE;
  if (HAL_CAN_Init(&hcan1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN1_Init 2 */

  /* USER CODE END CAN1_Init 2 */

}

/**
  * @brief CAN2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_CAN2_Init(void)
{

  /* USER CODE BEGIN CAN2_Init 0 */

  /* USER CODE END CAN2_Init 0 */

  /* USER CODE BEGIN CAN2_Init 1 */

  /* USER CODE END CAN2_Init 1 */
  hcan2.Instance = CAN2;
  hcan2.Init.Prescaler = 24;
  hcan2.Init.Mode = CAN_MODE_NORMAL;
  hcan2.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan2.Init.TimeSeg1 = CAN_BS1_13TQ;
  hcan2.Init.TimeSeg2 = CAN_BS2_2TQ;
  hcan2.Init.TimeTriggeredMode = DISABLE;
  hcan2.Init.AutoBusOff = ENABLE;
  hcan2.Init.AutoWakeUp = DISABLE;
  hcan2.Init.AutoRetransmission = DISABLE;
  hcan2.Init.ReceiveFifoLocked = DISABLE;
  hcan2.Init.TransmitFifoPriority = ENABLE;
  if (HAL_CAN_Init(&hcan2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN2_Init 2 */

  /* USER CODE END CAN2_Init 2 */

}

/**
  * @brief RTC Initialization Function
  * @param None
  * @retval None
  */
static void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef sDate = {0};

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */

  /** Initialize RTC Only
  */
  hrtc.Instance = RTC;
  hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
  hrtc.Init.AsynchPrediv = 127;
  hrtc.Init.SynchPrediv = 255;
  hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
  hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }

  /* USER CODE BEGIN Check_RTC_BKUP */
  if(HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR9) == '*')
  {
	  //Time is OK.
	  return;
  }
  /* USER CODE END Check_RTC_BKUP */

  /** Initialize RTC and set the Time and Date
  */
  sTime.Hours = 0x0;
  sTime.Minutes = 0x0;
  sTime.Seconds = 0x0;
  sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sTime.StoreOperation = RTC_STOREOPERATION_RESET;
  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }
  sDate.WeekDay = RTC_WEEKDAY_MONDAY;
  sDate.Month = RTC_MONTH_JANUARY;
  sDate.Date = 0x1;
  sDate.Year = 0x0;

  if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RTC_Init 2 */

  /* USER CODE END RTC_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, CAN_ERR_LED_Pin|DATA_O_LED_Pin|DATA_I_LED_Pin|CAN_EN_Pin
                          |CAN__STB_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : PW_BTN_Pin VU_BTN_Pin VD_BTN_Pin */
  GPIO_InitStruct.Pin = PW_BTN_Pin|VU_BTN_Pin|VD_BTN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : CAN_ERR_LED_Pin DATA_O_LED_Pin DATA_I_LED_Pin CAN_EN_Pin
                           CAN__STB_Pin */
  GPIO_InitStruct.Pin = CAN_ERR_LED_Pin|DATA_O_LED_Pin|DATA_I_LED_Pin|CAN_EN_Pin
                          |CAN__STB_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : CAN_ERR_Pin */
  GPIO_InitStruct.Pin = CAN_ERR_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(CAN_ERR_GPIO_Port, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* init code for USB_DEVICE */
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN 5 */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END 5 */
}

/* USER CODE BEGIN Header_sendTask50msHandler */
/**
* @brief Function implementing the sendTask50ms thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_sendTask50msHandler */
void sendTask50msHandler(void *argument)
{
  /* USER CODE BEGIN sendTask50msHandler */
	TickType_t xLastWakeTime;
	const TickType_t xFrequency = 50 / portTICK_PERIOD_MS;

	xLastWakeTime = xTaskGetTickCount();
  /* Infinite loop */
  for(;;)
  {
	  vTaskDelayUntil(&xLastWakeTime, xFrequency);
  }
  /* USER CODE END sendTask50msHandler */
}

/* USER CODE BEGIN Header_sendTask100msHandler */
/**
* @brief Function implementing the sendTask100ms thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_sendTask100msHandler */
void sendTask100msHandler(void *argument)
{
  /* USER CODE BEGIN sendTask100msHandler */
	TickType_t xLastWakeTime;
	const TickType_t xFrequency = 100 / portTICK_PERIOD_MS;

	xLastWakeTime = xTaskGetTickCount();
  /* Infinite loop */
  for(;;)
  {
	  vTaskDelayUntil(&xLastWakeTime, xFrequency);
  }
  /* USER CODE END sendTask100msHandler */
}

/* USER CODE BEGIN Header_sendTask200msHandler */
/**
* @brief Function implementing the sendTask200ms thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_sendTask200msHandler */
void sendTask200msHandler(void *argument)
{
  /* USER CODE BEGIN sendTask200msHandler */
	TickType_t xLastWakeTime;
	const TickType_t xFrequency = 200 / portTICK_PERIOD_MS;

	xLastWakeTime = xTaskGetTickCount();
  /* Infinite loop */
  for(;;)
  {
	  vTaskDelayUntil(&xLastWakeTime, xFrequency);
  }
  /* USER CODE END sendTask200msHandler */
}

/* USER CODE BEGIN Header_sendTask500msHandler */
/**
* @brief Function implementing the sendTask500ms thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_sendTask500msHandler */
void sendTask500msHandler(void *argument)
{
  /* USER CODE BEGIN sendTask500msHandler */
	TickType_t xLastWakeTime;
	const TickType_t xFrequency = 500 / portTICK_PERIOD_MS;

	xLastWakeTime = xTaskGetTickCount();
  /* Infinite loop */
  for(;;)
  {
	  vTaskDelayUntil(&xLastWakeTime, xFrequency);
  }
  /* USER CODE END sendTask500msHandler */
}

/* USER CODE BEGIN Header_sendTask1000msHandler */
/**
* @brief Function implementing the sendTask1000ms thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_sendTask1000msHandler */
void sendTask1000msHandler(void *argument)
{
  /* USER CODE BEGIN sendTask1000msHandler */
	TickType_t xLastWakeTime;
	const TickType_t xFrequency = 1000 / portTICK_PERIOD_MS;

	xLastWakeTime = xTaskGetTickCount();
  /* Infinite loop */
  for(;;)
  {
	  vTaskDelayUntil(&xLastWakeTime, xFrequency);
  }
  /* USER CODE END sendTask1000msHandler */
}

/* USER CODE BEGIN Header_sendTask5000msHandler */
/**
* @brief Function implementing the sendTask5000ms thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_sendTask5000msHandler */
void sendTask5000msHandler(void *argument)
{
  /* USER CODE BEGIN sendTask5000msHandler */
	TickType_t xLastWakeTime;
	const TickType_t xFrequency = 5000 / portTICK_PERIOD_MS;

	xLastWakeTime = xTaskGetTickCount();
  /* Infinite loop */
  for(;;)
  {
	  vTaskDelayUntil(&xLastWakeTime, xFrequency);
  }
  /* USER CODE END sendTask5000msHandler */
}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM1 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM1) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

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
