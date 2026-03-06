/**
  ******************************************************************************
  * @file    USB_Device/CustomHID_CDC_ACM_RTOS/Src/usbd_customhid_if.c
  * @author  MCD Application Team
  * @brief   USB Device Custom HID interface file.
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

/* Includes ------------------------------------------------------------------ */
#include "usbd_customhid_if.h"
#include "main.h"

/* Private typedef ----------------------------------------------------------- */
/* Private define ------------------------------------------------------------ */
/* Private macro ------------------------------------------------------------- */
/* Private function prototypes ----------------------------------------------- */
static int8_t CustomHID_Init(void);
static int8_t CustomHID_DeInit(void);
static int8_t CustomHID_OutEvent(uint8_t event_idx, uint8_t state);
#ifdef USBD_CUSTOMHID_CTRL_REQ_COMPLETE_CALLBACK_ENABLED
static int8_t CUSTOM_HID_CtrlReqComplete(uint8_t request, uint16_t wLength);
#endif /* USBD_CUSTOMHID_CTRL_REQ_COMPLETE_CALLBACK_ENABLED */

#ifdef USBD_CUSTOMHID_CTRL_REQ_GET_REPORT_ENABLED
static uint8_t *CUSTOM_HID_GetReport(uint16_t *ReportLength);
#endif /* USBD_CUSTOMHID_CTRL_REQ_GET_REPORT_ENABLED */

/* Private variables --------------------------------------------------------- */
uint8_t ReportBuff[64];

/* External variables --------------------------------------------------------*/
extern SemaphoreHandle_t   custom_hid_semaphore;
extern uint8_t CustomHID_InstID;
extern USBD_HandleTypeDef hUsbDeviceHS;

USBD_CUSTOM_HID_HandleTypeDef *hhid;
__ALIGN_BEGIN
static uint8_t CustomHID_ReportDesc[USBD_CUSTOM_HID_REPORT_DESC_SIZE]
__ALIGN_END =
{
  0x06, 0xFF, 0x00,      /* USAGE_PAGE (Vendor Page: 0xFF00) */
  0x09, 0x01,            /* USAGE (Demo Kit)               */
  0xa1, 0x01,            /* COLLECTION (Application)       */
  /* 6 */



  /* DATA OUT Report */
  0x85, DATAOUT_REPORT_ID,    /*     REPORT_ID (2)              */
  0x09, 0x02,                 /*     USAGE (DATA OUT)           */
  0x15, 0x00,                 /*     LOGICAL_MINIMUM (0)       */
  0x25, 0x01,                 /*     LOGICAL_MAXIMUM (1)        */
  0x75, 0x08,                 /*     REPORT_SIZE (8)           */
  0x95, DATAOUT_REPORT_COUNT, /*     REPORT_COUNT (1)          */
  0xB1, 0x82,                 /*     FEATURE (Data,Var,Abs,Vol)*/



  0x85, DATAOUT_REPORT_ID,    /*     REPORT_ID (2)              */
  0x09, 0x02,                 /*     USAGE (DATA OUT)          */
  0x91, 0x82,                 /*     OUTPUT (Data,Var,Abs,Vol) */
  /* 26 */



  /* DATA IN Report */
  0x85, DATAIN_REPORT_ID,   /*     REPORT_ID (1)              */
  0x09, 0x01,               /*     USAGE (DATA IN) */
  0x15, 0x00,               /*     LOGICAL_MINIMUM (0)        */
  0x25, 0x01,               /*     LOGICAL_MAXIMUM (1)        */
  0x75, 0x01,               /*     REPORT_SIZE (1)            */
  0x81, 0x82,               /*     INPUT (Data,Var,Abs,Vol)   */



  0x09, 0x01,               /*     USAGE (DATA IN) */
  0x75, 0x01,               /*     REPORT_SIZE (1)            */
  0xb1, 0x82,               /*     FEATURE (Data,Var,Abs,Vol) */



  0x75, 0x07,               /*     REPORT_SIZE (7)            */
  0x81, 0x83,               /*     INPUT (Cnst,Var,Abs,Vol)   */
  0x85, DATAIN_REPORT_ID,   /*     REPORT_ID (1)              */



  0x75, 0x07,               /*     REPORT_SIZE (7)            */
  0xb1, 0x83,               /*     FEATURE (Cnst,Var,Abs,Vol) */
  /* 142 */



  0xc0                         /*     END_COLLECTION                 */
};

USBD_CUSTOM_HID_ItfTypeDef USBD_CustomHID_fops = {
  CustomHID_ReportDesc,
  CustomHID_Init,
  CustomHID_DeInit,
  CustomHID_OutEvent,
#ifdef USBD_CUSTOMHID_CTRL_REQ_COMPLETE_CALLBACK_ENABLED
  CUSTOM_HID_CtrlReqComplete,
#endif /* USBD_CUSTOMHID_CTRL_REQ_COMPLETE_CALLBACK_ENABLED */
#ifdef USBD_CUSTOMHID_CTRL_REQ_GET_REPORT_ENABLED
  CUSTOM_HID_GetReport,
#endif /* USBD_CUSTOMHID_CTRL_REQ_GET_REPORT_ENABLED */
};

/* Private functions --------------------------------------------------------- */

/**
  * @brief  CustomHID_Init
  *         Initializes the CUSTOM HID media low layer
  * @param  None
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CustomHID_Init(void)
{
  return (USBD_OK);
}

/**
  * @brief  CustomHID_DeInit
  *         DeInitializes the CUSTOM HID media low layer
  * @param  None
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CustomHID_DeInit(void)
{
  /*
   * Add your de-initialization code here */
  return (0);
}

/**
  * @brief  CustomHID_OutEvent
  *         Manage the CUSTOM HID class Out Event
  * @param  event_idx: DATA Report Number
  * @param  data
  */
static int8_t CustomHID_OutEvent(uint8_t event_idx, uint8_t data)
{
  uint32_t idx;
  hhid = (USBD_CUSTOM_HID_HandleTypeDef *)hUsbDeviceHS.pClassDataCmsit[CustomHID_InstID];
  for (idx = 0U; idx < sizeof(ReportBuff); idx++)
  {
    ReportBuff[idx] = hhid->Report_buf[idx];
  }
  xSemaphoreGiveFromISR(custom_hid_semaphore, NULL);
  return (USBD_OK);
}


#ifdef USBD_CUSTOMHID_CTRL_REQ_COMPLETE_CALLBACK_ENABLED
/**
  * @brief  CUSTOM_HID_CtrlReqComplete
  *         Manage the CUSTOM HID control request complete
  * @param  request: control request
  * @param  wLength: request wLength
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CUSTOM_HID_CtrlReqComplete(uint8_t request, uint16_t wLength)
{
  UNUSED(wLength);

  switch (request)
  {
    case CUSTOM_HID_REQ_SET_REPORT:

      break;

    case CUSTOM_HID_REQ_GET_REPORT:

      break;

    default:
      break;
  }
  return (0);
}
#endif /* USBD_CUSTOMHID_CTRL_REQ_COMPLETE_CALLBACK_ENABLED */

#ifdef USBD_CUSTOMHID_CTRL_REQ_GET_REPORT_ENABLED
/**
  * @brief  CUSTOM_HID_GetReport
  *         Manage the CUSTOM HID control Get Report request
  * @param  event_idx: event index
  * @param  state: event state
  * @retval return pointer to HID report
  */
static uint8_t *CUSTOM_HID_GetReport(uint16_t *ReportLength)
{
  *ReportLength = 16U;
  uint8_t *pbuff = ReportBuff;

  return (pbuff);
}
#endif /* USBD_CUSTOMHID_CTRL_REQ_GET_REPORT_ENABLED */

/**
  * @brief  Function implementing custom_hid_task_entry.
  * @param  input: Not used
  * @retval none
  */
void custom_hid_task_entry(void *input)
{
  uint8_t sendbuff[2];
  sendbuff[0]=0x01;

  while(1)
  {
    if (xSemaphoreTake(custom_hid_semaphore, portMAX_DELAY ) == pdPASS)
    {
       sendbuff[1]=ReportBuff[1];
       USBD_CUSTOM_HID_SendReport(&hUsbDeviceHS, sendbuff, sizeof(sendbuff), CustomHID_InstID);
       USBD_CUSTOM_HID_ReceivePacket(&hUsbDeviceHS);
    }
  }
}
