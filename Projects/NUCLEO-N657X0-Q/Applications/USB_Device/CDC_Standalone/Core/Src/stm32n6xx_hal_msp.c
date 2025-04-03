/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file         stm32n6xx_hal_msp.c
  * @brief        This file provides code for the MSP Initialization
  *               and de-Initialization codes.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN Define */

/* USER CODE END Define */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN Macro */

/* USER CODE END Macro */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
extern UART_HandleTypeDef huart1;
extern DMA_HandleTypeDef gpdma_usart1_Channel0;
extern DMA_HandleTypeDef gpdma_usart1_Channel1;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* External functions --------------------------------------------------------*/
/* USER CODE BEGIN ExternalFunctions */

/* USER CODE END ExternalFunctions */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */
/**
  * Initializes the Global MSP.
  */
void HAL_MspInit(void)
{
  /* USER CODE BEGIN MspInit 0 */

  /* USER CODE END MspInit 0 */

  __HAL_RCC_SYSCFG_CLK_ENABLE();

  /* System interrupt init*/

  /* USER CODE BEGIN MspInit 1 */

  /* USER CODE END MspInit 1 */
}

/**
* @brief UART MSP Initialization
* This function configures the hardware resources used in this example
* @param huart: UART handle pointer
* @retval None
*/
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
  if (huart->Instance == USART1)
  {
  /* USER CODE BEGIN USART1_MspInit 0 */

  /* USER CODE END USART1_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USART1;
    PeriphClkInitStruct.Usart1ClockSelection = RCC_USART1CLKSOURCE_IC9;
    PeriphClkInitStruct.ICSelection[RCC_IC9].ClockSelection = RCC_ICCLKSOURCE_PLL4;
    PeriphClkInitStruct.ICSelection[RCC_IC9].ClockDivider = 1;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
      Error_Handler();
    }

    /* Peripheral clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();

    __HAL_RCC_GPIOE_CLK_ENABLE();
    /**USART1 GPIO Configuration
    PE5     ------> USART1_TX
    PE6     ------> USART1_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

    /* GPDMA1_REQUEST_USART1_RX Init */
    gpdma_usart1_Channel1.Instance = GPDMA1_Channel1;
    gpdma_usart1_Channel1.Init.Request = GPDMA1_REQUEST_USART1_RX;
    gpdma_usart1_Channel1.Init.BlkHWRequest = DMA_BREQ_SINGLE_BURST;
    gpdma_usart1_Channel1.Init.Direction = DMA_PERIPH_TO_MEMORY;
    gpdma_usart1_Channel1.Init.SrcInc = DMA_SINC_FIXED;
    gpdma_usart1_Channel1.Init.DestInc = DMA_DINC_INCREMENTED;
    gpdma_usart1_Channel1.Init.SrcDataWidth = DMA_SRC_DATAWIDTH_BYTE;
    gpdma_usart1_Channel1.Init.DestDataWidth = DMA_DEST_DATAWIDTH_BYTE;
    gpdma_usart1_Channel1.Init.Priority = DMA_LOW_PRIORITY_LOW_WEIGHT;
    gpdma_usart1_Channel1.Init.SrcBurstLength = 1;
    gpdma_usart1_Channel1.Init.DestBurstLength = 1;
    gpdma_usart1_Channel1.Init.TransferAllocatedPort = DMA_SRC_ALLOCATED_PORT0|DMA_DEST_ALLOCATED_PORT1;
    gpdma_usart1_Channel1.Init.TransferEventMode = DMA_TCEM_BLOCK_TRANSFER;
    gpdma_usart1_Channel1.Init.Mode = DMA_NORMAL;
    if (HAL_DMA_Init(&gpdma_usart1_Channel1) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(huart, hdmarx, gpdma_usart1_Channel1);

    if (HAL_DMA_ConfigChannelAttributes(&gpdma_usart1_Channel1, (DMA_CHANNEL_PRIV | DMA_CHANNEL_SEC | DMA_CHANNEL_SRC_SEC | DMA_CHANNEL_DEST_SEC)) != HAL_OK)
    {
      Error_Handler();
    }

     /* GPDMA1_REQUEST_USART1_TX Init */
    gpdma_usart1_Channel0.Instance = GPDMA1_Channel0;
    gpdma_usart1_Channel0.Init.Request = GPDMA1_REQUEST_USART1_TX;
    gpdma_usart1_Channel0.Init.BlkHWRequest = DMA_BREQ_SINGLE_BURST;
    gpdma_usart1_Channel0.Init.Direction = DMA_MEMORY_TO_PERIPH;
    gpdma_usart1_Channel0.Init.SrcInc = DMA_SINC_INCREMENTED;
    gpdma_usart1_Channel0.Init.DestInc = DMA_DINC_FIXED;
    gpdma_usart1_Channel0.Init.SrcDataWidth = DMA_SRC_DATAWIDTH_BYTE;
    gpdma_usart1_Channel0.Init.DestDataWidth = DMA_DEST_DATAWIDTH_BYTE;
    gpdma_usart1_Channel0.Init.Priority = DMA_LOW_PRIORITY_LOW_WEIGHT;
    gpdma_usart1_Channel0.Init.SrcBurstLength  = 1;
    gpdma_usart1_Channel0.Init.DestBurstLength = 1;
    gpdma_usart1_Channel0.Init.TransferAllocatedPort      = DMA_SRC_ALLOCATED_PORT1|DMA_DEST_ALLOCATED_PORT1;
    gpdma_usart1_Channel0.Init.TransferEventMode          = DMA_TCEM_BLOCK_TRANSFER;
    gpdma_usart1_Channel0.Init.Mode = DMA_NORMAL;
    if (HAL_DMA_Init(&gpdma_usart1_Channel0) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(huart,hdmatx,gpdma_usart1_Channel0);

    if (HAL_DMA_ConfigChannelAttributes(&gpdma_usart1_Channel0, (DMA_CHANNEL_PRIV | DMA_CHANNEL_SEC | DMA_CHANNEL_SRC_SEC | DMA_CHANNEL_DEST_SEC)) != HAL_OK)
    {
      Error_Handler();
    }

    /* USART1 interrupt Init */
    HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);

    /* USER CODE BEGIN USART1_MspInit 1 */
    __HAL_RCC_TIM6_CLK_ENABLE();

    /* Enable the TIM6 global Interrupt */
    HAL_NVIC_SetPriority(TIM6_IRQn, 0, 0U);

    /* Enable the TIM6 global Interrupt */
    HAL_NVIC_EnableIRQ(TIM6_IRQn);

    /* USER CODE END USART1_MspInit 1 */
  }
}

/**
* @brief UART MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param huart: UART handle pointer
* @retval None
*/
void HAL_UART_MspDeInit(UART_HandleTypeDef *huart)
{
  if (huart->Instance == USART1)
  {
    /* USER CODE BEGIN USART1_MspDeInit 0 */

    /* USER CODE END USART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();

    /**USART1 GPIO Configuration
    PE5     ------> USART1_TX
    PE6     ------> USART1_RX
    */
    HAL_GPIO_DeInit(GPIOE, GPIO_PIN_5 | GPIO_PIN_6);

    /* USER CODE BEGIN USART1_MspDeInit 1 */

    /* USER CODE END USART1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
