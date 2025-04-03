/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usbpd_devices_conf.h
  * @author  MCD Application Team
  * @brief   This file contains the device define.
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

#ifndef USBPD_DEVICE_CONF_H
#define USBPD_DEVICE_CONF_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32n6xx_hal.h"
#include "stm32n6xx_ll_bus.h"
#include "stm32n6xx_ll_dma.h"
#include "stm32n6xx_ll_gpio.h"
#include "stm32n6xx_ll_rcc.h"
#include "stm32n6xx_ll_ucpd.h"
#include "stm32n6xx_ll_pwr.h"
#include "stm32n6xx_ll_tim.h"
#include "usbpd_pwr_if.h"
#include "stm32n6xx_nucleo_usbpd_pwr.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* -----------------------------------------------------------------------------
      usbpd_hw.c
-------------------------------------------------------------------------------*/

/* defined used to configure function : USBPD_HW_GetUSPDInstance */
#define UCPD_INSTANCE0 UCPD1

/* defined used to configure  USBPD_HW_SetFRSSignalling */
#define UCPDFRS_INSTANCE0_FRSCC1
#define UCPDFRS_INSTANCE0_FRSCC2

#define UCPD_INSTANCE0_ENABLEIRQ  do{                                                                 \
                                        NVIC_SetPriority(UCPD1_IRQn,2);                              \
                                        NVIC_EnableIRQ(UCPD1_IRQn);                                  \
                                    } while(0)

#ifdef __cplusplus
}
#endif

#endif /* USBPD_DEVICE_CONF_H */
