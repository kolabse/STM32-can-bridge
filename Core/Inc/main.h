/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
#define PW_BTN_Pin GPIO_PIN_4
#define PW_BTN_GPIO_Port GPIOA
#define VU_BTN_Pin GPIO_PIN_5
#define VU_BTN_GPIO_Port GPIOA
#define VD_BTN_Pin GPIO_PIN_6
#define VD_BTN_GPIO_Port GPIOA
#define CAN_ERR_LED_Pin GPIO_PIN_0
#define CAN_ERR_LED_GPIO_Port GPIOB
#define DATA_O_LED_Pin GPIO_PIN_1
#define DATA_O_LED_GPIO_Port GPIOB
#define DATA_I_LED_Pin GPIO_PIN_2
#define DATA_I_LED_GPIO_Port GPIOB
#define CAN_EN_Pin GPIO_PIN_14
#define CAN_EN_GPIO_Port GPIOB
#define CAN__STB_Pin GPIO_PIN_15
#define CAN__STB_GPIO_Port GPIOB
#define CAN_ERR_Pin GPIO_PIN_7
#define CAN_ERR_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
