/**
  ******************************************************************************
  * @file    USB_Device/CustomHID_CDC_ACM_RTOS/Inc/usbd_customhid_if.h
  * @author  MCD Application Team
  * @brief   Header for usbd_customhid_if.c file.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USBD_CUSTOMHID_IF_H
#define __USBD_CUSTOMHID_IF_H

/* Includes ------------------------------------------------------------------*/
#include "usbd_customhid.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#define DATAOUT_REPORT_COUNT     0x01

#define DATAIN_REPORT_ID         0x01
#define DATAOUT_REPORT_ID        0x02


/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
extern USBD_CUSTOM_HID_ItfTypeDef USBD_CustomHID_fops;
void custom_hid_task_entry(void *input);
#endif /* __USBD_CUSTOMHID_IF_H */
