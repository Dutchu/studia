/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32l4xx_it.c
  * @brief   Interrupt Service Routines.
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
#include "stm32l4xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#define JOY_PORT GPIOE

#define JOY_RIGHT GPIO_PIN_0
#define JOY_LEFT GPIO_PIN_1
#define JOY_UP GPIO_PIN_3
#define JOY_DOWN GPIO_PIN_2
#define JOY_PUSH GPIO_PIN_15

#define IF_JOY_LEFT ((~(GPIOE->IDR) & JOY_LEFT) ? 1 : 0)
#define IF_JOY_RIGHT ((~(GPIOE->IDR) & JOY_RIGHT) ? 1 : 0)
#define IF_JOY_UP ((~(GPIOE->IDR) & JOY_UP) ? 1 : 0)
#define IF_JOY_DOWN ((~(GPIOE->IDR) & JOY_DOWN) ? 1 : 0)
#define IF_JOY_PUSH ((~(GPIOE->IDR) & JOY_PUSH) ? 1 : 0)

#define LED0 GPIOD, GPIO_PIN_12
#define LED1 GPIOD, GPIO_PIN_13
#define LED2 GPIOB, GPIO_PIN_8

#define FREQ 50U // 50 Hz
#define DELAY 20U // 20 ms
#define NUMBER_OF_LEDS 3U

#define PWM_FREQ 50U
#define LED_INTENSITY_LEVELS 5U
#define PWM_W_MIN PWM_FREQ / LED_INTENSITY_LEVELS
#define PWM_W_MAX PWM_W_MIN * (LED_INTENSITY_LEVELS - 1)

#define JOY_FREQ 1U

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

uint8_t tic_counter = 0U;
uint8_t leds_intens[NUMBER_OF_LEDS] = {PWM_W_MIN, PWM_W_MIN, PWM_W_MIN};
uint8_t colors_on[NUMBER_OF_LEDS] = {1,1,1};
uint8_t current_led = 0U;
uint8_t check_joy = 0U;
uint8_t if_toggle_joy = 1U;
uint8_t show_color = 1U;
uint8_t led_on = 1U;
uint8_t pwm_w[NUMBER_OF_LEDS] = {1U, 1U, 1U};
uint8_t pwm_counter = 0U;
uint8_t pwm_signals_flag[NUMBER_OF_LEDS] = {1U, 1U, 1U};

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/

/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
  while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Prefetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  if (tic_counter % PWM_FREQ == 0 && tic_counter != 0) {
	  led_on = 1;
  } else {
	  led_on = 0;
  }

  if (tic_counter % JOY_FREQ == 0 && tic_counter != 0) {
	  check_joy = 1;
  } else {
	  check_joy = 0;
  }


  if (IF_JOY_UP && check_joy && if_toggle_joy) {

	  if (leds_intens[current_led] < PWM_W_MAX) {
		  leds_intens[current_led] += PWM_W_MIN;
		  colors_on[current_led] = 1;
	  }

	  if_toggle_joy = 0;

  }
  if (IF_JOY_DOWN && check_joy && if_toggle_joy) {
	  if (leds_intens[current_led] > PWM_W_MIN) {
		  leds_intens[current_led] -= PWM_W_MIN;
	  } else {
//		  colors_on[current_led] = 0;
	  }

	  if_toggle_joy = 0;
  }
  if (IF_JOY_LEFT && check_joy && if_toggle_joy) {
	  if (current_led == 0) {
		  current_led = 2;
	  } else {
		  current_led -= 1;
	  }

	  if_toggle_joy = 0;
  }
  if (IF_JOY_RIGHT && check_joy && if_toggle_joy) {
	  if (current_led == 2) {
		  current_led = 0;
	  } else {
		  current_led += 1;
	  }

	  if_toggle_joy = 0;
  }

  //if joy was toggled
  if(if_toggle_joy == 0) {
	  //if NOTHING is toggled on joy
	  if ( ! (IF_JOY_RIGHT || IF_JOY_LEFT || IF_JOY_UP || IF_JOY_DOWN)) {
		  //you can toggle again
		  if_toggle_joy = 1;
	  }
  }

  //find out if pwm signal should persist in this tick for every led
  for (int i = 0; i < NUMBER_OF_LEDS; i++) {

	  //width of pwm signal in ticks for every led
	  // leds_intensity have level of intensity (number of PWM_W_MIN) and PWM_W_MIN is number of ticks for every level (number by which gap between led signals was divided

	  //check if led signal end in this tick
	  if(leds_intens[i] == pwm_counter) {
		  //switch pwm signal flag to false
		  pwm_signals_flag[i] = 0;
	  } else {
		  //keep lights on
		  pwm_signals_flag[i] = 1;
	  }
  }


  //check if leds are to be lit up
  if (tic_counter % PWM_FREQ == 0 && led_on && colors_on[0U] == 1) {
	  HAL_GPIO_WritePin(LED0, GPIO_PIN_SET);
  }
  if (tic_counter % PWM_FREQ == 0 && led_on && colors_on[1U] == 1) {
	  HAL_GPIO_WritePin(LED1, GPIO_PIN_SET);
  }
  if (tic_counter % PWM_FREQ == 0 && led_on && colors_on[2U] == 1) {
	  HAL_GPIO_WritePin(LED2, GPIO_PIN_SET);
  }

  //check if lights are to be switched off
  if (pwm_signals_flag[1] == 0) {
	  HAL_GPIO_WritePin(LED1, GPIO_PIN_RESET);
  }
  if (pwm_signals_flag[0] == 0) {
	  HAL_GPIO_WritePin(LED0, GPIO_PIN_RESET);
  }
  if (pwm_signals_flag[2] == 0) {
	  HAL_GPIO_WritePin(LED2, GPIO_PIN_RESET);
  }

//  //light up LED color 1
//  if (tic_counter % leds_intens[1U] == 0 && led_on && colors_on[1U] == 1U) {
//	  HAL_GPIO_WritePin(LED1, GPIO_PIN_SET);
//  } else {
//	  HAL_GPIO_WritePin(LED1, GPIO_PIN_RESET);
//  }
//
//  //light up LED color 2
//  if (tic_counter % leds_intens[2U] == 0 && led_on && colors_on[2U] == 1U) {
//	  HAL_GPIO_WritePin(LED2, GPIO_PIN_SET);
//  } else {
//	  HAL_GPIO_WritePin(LED2, GPIO_PIN_RESET);
//  }

  if (tic_counter == 1000U) {
	  tic_counter = 0U;
  } else {
	  tic_counter += 1;
  }

  if (PWM_FREQ == pwm_counter) {
	  pwm_counter = 1;
  } else {
	  pwm_counter += 1;
  }

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32L4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32l4xx.s).                    */
/******************************************************************************/

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
