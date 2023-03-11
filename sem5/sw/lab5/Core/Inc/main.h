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
#include "stm32l4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
typedef struct
{
	uint16_t miliseconds_u16;
	uint16_t seconds_u16;
	uint16_t minutes_u16;
	uint16_t hours_u16;
	uint16_t isDotActive : 1;
	uint16_t mode_HH_MM : 1;
}Time_t;

typedef enum {
	X = 10U,
	Y,
	Z
}selectedAxisType;
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
void Dis7Seg_Init(void);
void Dis7seg_display(uint8_t dotSecondPlace);
void Dis7Seg_SetAxisValue(const selectedAxisType * const selectedAxis, uint8_t * dotSecondPlace);
uint8_t DetectFallingEdge(GPIO_TypeDef * port, uint16_t pin);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
/* USER CODE BEGIN Private defines */
#define TRUE 1U
#define FALSE 0U

#define SEG_A_PIN GPIO_PIN_0
#define SEG_B_PIN GPIO_PIN_1
#define SEG_C_PIN GPIO_PIN_2
#define SEG_D_PIN GPIO_PIN_3
#define SEG_E_PIN GPIO_PIN_4
#define SEG_F_PIN GPIO_PIN_5
#define SEG_G_PIN GPIO_PIN_6
#define SEG_DP_PIN GPIO_PIN_9
#define SEG_PORT GPIOG
#define SEG_MASK SEG_A_PIN | SEG_B_PIN | SEG_C_PIN | SEG_D_PIN | SEG_E_PIN | SEG_F_PIN | SEG_G_PIN | SEG_DP_PIN

#define DIG1_PIN GPIO_PIN_2
#define DIG2_PIN GPIO_PIN_3
#define DIG3_PIN GPIO_PIN_4
#define DIG4_PIN GPIO_PIN_5
#define DIG_PORT GPIOB
#define DIG_MASK DIG1_PIN | DIG2_PIN | DIG3_PIN | DIG4_PIN

#define JOY_RIGHT_PIN GPIO_PIN_0
#define JOY_LEFT_PIN GPIO_PIN_1
#define JOY_UP_PIN GPIO_PIN_3
#define JOY_DOWN_PIN GPIO_PIN_2
#define JOY_CENTER_PIN GPIO_PIN_15

#define JOY_RIGHT_PORT GPIOE
#define JOY_LEFT_PORT GPIOE
#define JOY_UP_PORT GPIOE
#define JOY_DOWN_PORT GPIOE
#define JOY_CENTER_PORT GPIOE
#define JOY_PORT GPIOE

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
