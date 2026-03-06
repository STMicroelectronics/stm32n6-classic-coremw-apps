/**
******************************************************************************
* @file    USB_Device/CustomHID_CDC_ACM_RTOS/USB_Device/App/usb_device.c
* @author  MCD Application Team
* @brief   This file implements the USB Device
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

/* Includes ------------------------------------------------------------------*/
#include "usb_device.h"
#include "usbd_desc.h"
#include "usbd_cdc_if.h"
#include "usbd_composite_builder.h"
#include "main.h"

/* Private define ------------------------------------------------------------*/
#define APP_DEFAULT_STACK_SIZE    (configMINIMAL_STACK_SIZE)
#define APP_DEFAULT_PRIORITY      (configMAX_PRIORITIES / 6U)

/* Private variables ---------------------------------------------------------*/
/* USB Device Core handle declaration. */
USBD_HandleTypeDef hUsbDeviceHS;

uint8_t CustomHID_InstID, CDC_InstID;

uint8_t CDC_EpAdd[3] = {CDC_IN_EP, CDC_OUT_EP, CDC_CMD_EP};  /* CDC Endpoint Address */
uint8_t CHID_EpAdd[2] = {CUSTOM_HID_EPIN_ADDR, CUSTOM_HID_EPOUT_ADDR};  /* CUSTOM HID Endpoint Address */

TaskHandle_t app_usb_device_task;
TaskHandle_t cdc_task;
TaskHandle_t custom_hid_task;

SemaphoreHandle_t   usbd_cdc_semaphore;
SemaphoreHandle_t   custom_hid_semaphore;

/* Private function prototypes -----------------------------------------------*/
static void app_usb_device_task_entry(void *args);

/**
* Init USB device Library, add supported class and start the library
* @retval None
*/
void MX_USB_Device_Init(void)
{

  /* Create app_usb_device_task.  */
  if (xTaskCreate(app_usb_device_task_entry, "app usb device task entry", APP_DEFAULT_STACK_SIZE,
                  (void *) NULL, APP_DEFAULT_PRIORITY, &app_usb_device_task) != pdPASS)
  {
    Error_Handler();
  }

  /* Create usbd_cdc_semaphore.  */
  usbd_cdc_semaphore = xSemaphoreCreateBinary();

  /* Create custom_hid_semaphore.  */
  custom_hid_semaphore = xSemaphoreCreateBinary();

  /* Create cdc_task_entry.  */
  if (xTaskCreate(cdc_task_entry, "cdc task entry", APP_DEFAULT_STACK_SIZE,
                  (void *) NULL, APP_DEFAULT_PRIORITY, &cdc_task) != pdPASS)
  {
    Error_Handler();
  }

  /* Create custom_hid_task_entry.  */
  if (xTaskCreate(custom_hid_task_entry, "custom hid task entry", APP_DEFAULT_STACK_SIZE,
                  (void *) NULL, APP_DEFAULT_PRIORITY, &custom_hid_task) != pdPASS)
  {
    Error_Handler();
  }
}

/**
* @brief  Function implementing app_ux_device_task_entry.
* @param  input: User task input parameter.
* @retval none
*/

void app_usb_device_task_entry(void *input)
{
  /* Init Device Library */
  USBD_Init(&hUsbDeviceHS, &COMPOSITE_Desc, 0);

  /* Store CDC instance Class ID */
  CDC_InstID = hUsbDeviceHS.classId;

  /* Register CDC class second instance */
  USBD_RegisterClassComposite(&hUsbDeviceHS, USBD_CDC_CLASS, CLASS_TYPE_CDC, CDC_EpAdd);

  /* Store CustomHID instance Class ID */
  CustomHID_InstID = hUsbDeviceHS.classId;

  /* Register the Custom HID class */
  USBD_RegisterClassComposite(&hUsbDeviceHS, USBD_CUSTOM_HID_CLASS, CLASS_TYPE_CHID, CHID_EpAdd);

  /* Add CDC Interface Class */
  if (USBD_CMPSIT_SetClassID(&hUsbDeviceHS, CLASS_TYPE_CDC, 0) != 0xFF)
  {
    USBD_CDC_RegisterInterface(&hUsbDeviceHS, &USBD_Interface_fops_HS);
  }

  /* Add custom HID Interface Class */
  if (USBD_CMPSIT_SetClassID(&hUsbDeviceHS, CLASS_TYPE_CHID, 0) != 0xFF)
  {
    USBD_CUSTOM_HID_RegisterInterface(&hUsbDeviceHS, &USBD_CustomHID_fops);
  }

  /* Start Device Process */
  if (USBD_Start(&hUsbDeviceHS) != USBD_OK)
  {
    Error_Handler();
  }

  /* Delete app_usb_device_task.  */
  vTaskDelete(app_usb_device_task);
}

/**
* @}
*/

/**
* @}
*/

