/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
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
#define LED_Pin GPIO_PIN_13
#define LED_GPIO_Port GPIOC
#define LR_U_FB_Pin GPIO_PIN_0
#define LR_U_FB_GPIO_Port GPIOA
#define LR_D_FB_Pin GPIO_PIN_1
#define LR_D_FB_GPIO_Port GPIOA
#define RR_U_FB_Pin GPIO_PIN_2 //RR_U
#define RR_U_FB_GPIO_Port GPIOA //RR_U
#define RR_D_FB_Pin GPIO_PIN_3 // RR_D
#define RR_D_FB_GPIO_Port GPIOA // RR_D
#define LF_U_FB_Pin GPIO_PIN_4
#define LF_U_FB_GPIO_Port GPIOA
#define LF_D_FB_Pin GPIO_PIN_5
#define LF_D_FB_GPIO_Port GPIOA
#define RF_U_FB_Pin GPIO_PIN_6 //RF_U
#define RF_U_FB_GPIO_Port GPIOA //RF_U
#define RF_D_FB_Pin GPIO_PIN_7 //RF_D
#define RF_D_FB_GPIO_Port GPIOA //RF_U
#define LF_U_Pin GPIO_PIN_0
#define LF_U_GPIO_Port GPIOB
#define LF_D_Pin GPIO_PIN_1
#define LF_D_GPIO_Port GPIOB
#define RF_U_Pin GPIO_PIN_2 //RR
#define RF_U_GPIO_Port GPIOB //RR
#define RF_D_Pin GPIO_PIN_10 //RR
#define RF_D_GPIO_Port GPIOB //RR
#define LR_U_Pin GPIO_PIN_12
#define LR_U_GPIO_Port GPIOB
#define RR_U_Pin GPIO_PIN_13 //RF
#define RR_U_GPIO_Port GPIOB //RF
#define LR_D_Pin GPIO_PIN_14
#define LR_D_GPIO_Port GPIOB
#define RR_D_Pin GPIO_PIN_15 //RF
#define RR_D_GPIO_Port GPIOB //RF
#define LR_UP_Pin GPIO_PIN_11
#define LR_UP_GPIO_Port GPIOA
#define LR_DOWN_Pin GPIO_PIN_12
#define LR_DOWN_GPIO_Port GPIOA
#define LF_UP_Pin GPIO_PIN_15
#define LF_UP_GPIO_Port GPIOA
#define LF_DOWN_Pin GPIO_PIN_3
#define LF_DOWN_GPIO_Port GPIOB
#define RF_UP_Pin GPIO_PIN_4
#define RF_UP_GPIO_Port GPIOB
#define RF_DOWN_Pin GPIO_PIN_5
#define RF_DOWN_GPIO_Port GPIOB
#define RR_UP_Pin GPIO_PIN_6
#define RR_UP_GPIO_Port GPIOB
#define RR_DOWN_Pin GPIO_PIN_7
#define RR_DOWN_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
