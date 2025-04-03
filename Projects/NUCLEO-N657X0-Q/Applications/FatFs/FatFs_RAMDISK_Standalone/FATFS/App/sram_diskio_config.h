/**
  ******************************************************************************
  * @file    sram_diskio_config.h
  * @author  MCD Application Team
  * @brief   Header for the sram_diskio_config.h
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the st_license.txt
  * file in the root directory of this software component.
  * If no st_license.txt file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

#ifndef SRAM_DISKIO_CONFIG_H
#define SRAM_DISKIO_CONFIG_H


#ifdef __cplusplus
extern "C" {
#endif
/* Includes ------------------------------------------------------------------*/
#include "stm32n6xx.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Block size */
#define BLOCK_SIZE                512U

/* Base Address */
#define SRAM_DISK_BASE_ADDR       SRAM3_AXI_BASE_S

/* SRAM Disk size in bytes */
#define SRAM_DISK_SIZE            SRAM3_AXI_SIZE


#ifdef __cplusplus
}
#endif

#endif /* SRAM_DISKIO_CONFIG_H */