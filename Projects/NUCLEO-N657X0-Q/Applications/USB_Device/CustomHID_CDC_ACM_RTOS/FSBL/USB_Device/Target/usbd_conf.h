/**
  ******************************************************************************
  * @file    USB_Device/CustomHID_CDC_ACM_RTOS/USB_Device/Target/usbd_conf.h
  * @author  MCD Application Team
  * @brief   General low level driver configuration
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
#ifndef __USBD_CONF_H
#define __USBD_CONF_H

/* Includes ------------------------------------------------------------------*/
#include "stm32n6xx_hal.h"
#include <stdlib.h>
#include <string.h>

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/* Activate the IAD option */
#define USBD_COMPOSITE_USE_IAD                             1U

/* Activate the composite builder */
#define USE_USBD_COMPOSITE

/* Activate HID and CDC classes in composite builder */
#define USBD_CMPSIT_ACTIVATE_CUSTOMHID                     1U
#define USBD_CMPSIT_ACTIVATE_CDC                           1U

#define USBD_CUSTOMHID_CTRL_REQ_GET_REPORT_ENABLED

#define USBD_CUSTOMHID_CTRL_REQ_COMPLETE_CALLBACK_ENABLED

#define USBD_CONFIG_STR_DESC_IDX                           4U
#define USBD_MAX_POWER                                     20U


/* The definition of endpoint numbers must respect the order of classes instantiation  */
#define CDC_IN_EP                             0x81U  /* EP1 for data IN */
#define CDC_OUT_EP                            0x01U  /* EP1 for data OUT */
#define CDC_CMD_EP                            0x82U  /* EP2 for data IN */

#define CUSTOM_HID_EPIN_ADDR                  0x83U
#define CUSTOM_HID_EPOUT_ADDR                 0x03U

#define CUSTOM_HID_EPOUT_SIZE                 64U
#define CUSTOM_HID_EPIN_SIZE                  64U

/* Common Config */
#define USBD_MAX_NUM_INTERFACES               4U
#define USBD_MAX_NUM_CONFIGURATION            1U
#define USBD_MAX_STR_DESC_SIZ                 0x100U
#define USBD_SUPPORT_USER_STRING_DESC         0U
#define USBD_SELF_POWERED                     1U
#define USBD_DEBUG_LEVEL                      0U
#define USBD_CUSTOMHID_OUTREPORT_BUF_SIZE     64U
#define USBD_CUSTOM_HID_REPORT_DESC_SIZE      56U
#define CUSTOM_HID_FS_BINTERVAL               0x5U

/* Exported variables --------------------------------------------------------*/
extern PCD_HandleTypeDef hpcd_USB_DRD_FS;

/* Exported macro ------------------------------------------------------------*/
/* Memory management macros */
#define MAX_STATIC_ALLOC_SIZE     4 /* HID and CDC Class structure size */
#define USBD_malloc               (uint32_t *)USBD_static_malloc
#define USBD_free                 USBD_static_free
#define USBD_memset               memset
#define USBD_memcpy               memcpy
#define USBD_Delay                HAL_Delay


#define SIZE_OF_PAGE      64  /* 64 Bytes pages */
#define MAX_PAGE_NUMBER   20  /* Handle a maximum of 128 pages */

/* DEBUG macros */
#if (USBD_DEBUG_LEVEL > 0U)
#define  USBD_UsrLog(...)   do { \
                            printf(__VA_ARGS__); \
                            printf("\n"); \
} while (0)
#else
#define USBD_UsrLog(...) do {} while (0)
#endif

#if (USBD_DEBUG_LEVEL > 1U)

#define  USBD_ErrLog(...) do { \
                            printf("ERROR: ") ; \
                            printf(__VA_ARGS__); \
                            printf("\n"); \
} while (0)
#else
#define USBD_ErrLog(...) do {} while (0)
#endif

#if (USBD_DEBUG_LEVEL > 2U)
#define  USBD_DbgLog(...)   do { \
                            printf("DEBUG : ") ; \
                            printf(__VA_ARGS__); \
                            printf("\n"); \
} while (0)
#else
#define USBD_DbgLog(...) do {} while (0)
#endif

/* Exported functions ------------------------------------------------------- */
void *USBD_static_malloc(uint32_t size);
void USBD_static_free(void *p);

#endif /* __USBD_CONF_H */
