
#### FatFs_RAMDISK_Standalone Application Description

How to use STM32Cube firmware with FatFs middleware component as a generic FAT
file system module. This example develops an application that exploits FatFs
features to configure the ram as a fat drive.

At the beginning of the main program the HAL_Init() function is called to reset
all the peripherals, initialize the Flash interface and the systick.
Then the SystemClock_Config() function is used to configure the system clock
(SYSCLK) to run at 100 MHz.

The application is based on writing and reading back a text file from a drive,
and it's performed using FatFs APIs to access the FAT volume as described
in the following steps:

 - Link the RAM disk I/O driver;
 - Register the file system object (mount) to the FatFs module for the RAM drive;
 - Create a FAT file system (format) on the RAM drive;
 - Create and Open new text file object with write access;
 - Write data to the text file;
 - Close the open text file;
 - Open text file object with read access;
 - Read back data from the text file;
 - Close the open text file;
 - Check on read data from text file;
 - Unlink the RAM disk I/O driver.

It is worth nothing that the application manages any error occurred during the
access to FAT volume, when using FatFs APIs. Otherwise, user can check if the
written text file is available on the RAM.

It is possible to fine tune needed FatFs features by modifying defines values
in FatFs configuration file "ffconf.h" available under the project includes
directory, in a way to fit the application requirements.

#### <b>Expected success behavior</b>

- A blinking green LED light marks the success of the file operations.

#### <b>Error behaviors</b>

- On failure, the red LED should start blinking.

#### <b>Assumptions if any</b>

None.

#### <b>Known limitations</b>

None.

#### Notes
 1. Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.

 2. The application needs to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

### Keywords

FatFs, Ramdisk, File system, FAT Volume, Format, Mount, Read, Write,

### Directory contents

  - FatFs/FatFs_RAMDISK_Standalone/Core/Inc/stm32n6xx_hal_conf.h                HAL configuration file
  - FatFs/FatFs_RAMDISK_Standalone/Core/Inc/stm32n6xx_it.h                      Interrupt handlers header file
  - FatFs/FatFs_RAMDISK_Standalone/Core/Inc/main.h                              Header for main.c module
  - FatFs/FatFs_RAMDISK_Standalone/Core/Src/stm32n6xx_it.c                      Interrupt handlers
  - FatFs/FatFs_RAMDISK_Standalone/Core/Src/main.c                              Main program
  - FatFs/FatFs_RAMDISK_Standalone/Core/Src/system_stm32n6xx.c                  STM32N6xx system source file
  - FatFs/FatFs_RAMDISK_Standalone/FATFS/Target/ffconf.h                        FAT file system module configuration file
  - FatFs/FatFs_RAMDISK_Standalone/FATFS/Target/sram_diskio.h                   sram diskio header file
  - FatFs/FatFs_RAMDISK_Standalone/FATFS/Target/sram_diskio.c                   FatFs sram diskio driver
  - FatFs/FatFs_RAMDISK_Standalone/FATFS/App/app_fatfs.h                        Header file for App_fatfs.c file
  - FatFs/FatFs_RAMDISK_Standalone/FATFS/App/app_fatfs.c                        FatFs application code

### Hardware and Software environment

  - This application runs on STM32N657X0H3QU devices.
  - This application has been tested with STMicroelectronics NUCLEO-N657X0-Q (MB1940)
    board and can be easily tailored to any other supported device
    and development board.

  - **EWARM** : To monitor a variable in the live watch window, you must proceed as follow :
    - Start a debugging session.
    - Open the View > Images.
    - Double-click to deselect the second instance of FatFs_RAMDISK_Standalone.out.

### How to use it ?

In order to make the program work, you must do the following :

 - Set the boot mode in development mode (BOOT1 switch position is 2-3, BOOT0 switch position doesn't matter).
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory. Code can be executed in this mode for debugging purposes.

Next, this program can be run in boot from flash mode. This can be done by following the instructions below:

 - Resort to CubeProgrammer to add a header to the generated binary FatFs_RAMDISK_Standalone.bin with the following command
   - *STM32_SigningTool_CLI.exe -bin FatFs_RAMDISK_Standalone.bin -nk -of 0x80000000 -t fsbl -o FatFs_RAMDISK_Standalone-trusted.bin -hv 2.3 -dump FatFs_RAMDISK_Standalone-trusted.bin*
   - The resulting binary is FatFs_RAMDISK_Standalone-trusted.bin.
 - Next, in resorting again to CubeProgrammer, load the binary and its header (FatFs_RAMDISK_Standalone-trusted.bin) in Nucleo board external Flash at address 0x7000'0000.
 - Set the boot mode in boot from external Flash (BOOT0 switch position is 1-2 and BOOT1 switch position is 1-2).
 - Press the reset button. The code then executes in boot from external Flash mode.
