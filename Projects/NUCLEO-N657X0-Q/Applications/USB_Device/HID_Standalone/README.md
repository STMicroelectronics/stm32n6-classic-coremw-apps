## HID_Standalone Application Description

Use of the USB device application based on the Human Interface (HID).

This is a typical application on how to use the STM32N6xx USB OTG Device peripheral where the STM32 MCU is
enumerated as a HID device using the native PC Host HID driver to which the NUCLEO-N657X0-Q
board is connected, in order to emulate the Mouse directions using User push-button mounted on the
NUCLEO-N657X0-Q board.

At the beginning of the main program the HAL_Init() function is called to reset all the peripherals,
initialize the Flash interface and the systick. The user is provided with the SystemClock_Config()
function to configure the system clock (SYSCLK) to run at 200 MHz.
The high speed OTG IP in high speed mode (HS) uses HSE clock.

#### <b>Expected success behavior</b>

When plugged to PC host, the NUCLEO-N657X0-Q must be properly enumerated as a USB HID mouse device.
During the enumeration phase, device provides host with the requested descriptors (device, configuration, string).
Those descriptors are used by host driver to identify the device capabilities.
Once the NUCLEO-N657X0-Q USB device successfully completed the enumeration phase, the device sends an HID report after a user button press.
Each report sent should move the mouse cursor by one step on host side.

#### <b>Error behaviors</b>

  - LED_RED is toggling to indicate a critical error has occured.

#### <b>Assumptions if any</b>

User is familiar with USB 2.0 "Universal Serial BUS" specification and HID class specification.

#### <b>Known limitations</b>

None

#### Notes
 1. Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.

 2. The application needs to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

For more details about the STM32Cube USB Device library, please refer to UM1734
"STM32Cube USB Device library".

### Keywords

Connectivity, USB_Device, USB, HID, high Speed, Mouse, Remote Wakeup

### Directory contents

  - USB_Device/HID_Standalone/Core/Src/main.c                        Main program
  - USB_Device/HID_Standalone/Core/Src/system_stm32n6xx.c            STM32N6xx system clock configuration file
  - USB_Device/HID_Standalone/Core/Src/stm32n6xx_it.c                Interrupt handlers
  - USB_Device/HID_Standalone/Core/Src/stm32n6xx_hal_msp.c           HAL MSP module
  - USB_Device/HID_Standalone/USB_Device/Target/usbd_conf.c          General low level driver configuration
  - USB_Device/HID_Standalone/USB_Device/App/usbd_desc.c             USB device HID descriptor
  - USB_Device/HID_Standalone/USB_Device/App/usbd_device.c           USB Device
  - USB_Device/HID_Standalone/Core/Inc/main.h                        Main program header file
  - USB_Device/HID_Standalone/Core/Inc/stm32n6xx_it.h                Interrupt handlers header file
  - USB_Device/HID_Standalone/Core/Inc/stm32n6xx_hal_conf.h          HAL configuration file
  - USB_Device/HID_Standalone/USB_Device/Target/usbd_conf.h          USB device driver Configuration file
  - USB_Device/HID_Standalone/USB_Device/App/usbd_desc.h             USB device HID descriptor header file
  - USB_Device/HID_Standalone/USB_Device/App/usbd_device.h           USB Device header
  - USB_Device/HID_Standalone/USB-PD/Target/usbpd_devices_conf.h     UCPD device configuration file
  - USB_Device/HID_Standalone/USB-PD/Target/usbpd_dpm_conf.h         UCPD stack configuration file

### Hardware and Software environment

  - This application runs on STM32N657X0H3QU devices.
  - This application has been tested with STMicroelectronics NUCLEO-N657X0-Q boards Revision MB1940-N657XOQ-C01 and can be easily tailored to any other supported device and development board.

  - **EWARM** : To monitor a variable in the live watch window, you must proceed as follow :
    - Start a debugging session.
    - Open the View > Images.
    - Double-click to deselect the second instance of HID_Standalone.out.

  - NUCLEO-N657X0-Q board Set-up
    - Connect the NUCLEO-N657X0-Q board to the PC through Type-C to standard A Male cable connected to the connector.
    - Press the USER push-button to move the cursor.

### How to use it ?

In order to make the program work, you must do the following :

 - Set the boot mode in development mode (BOOT1 switch position is 2-3, BOOT0 switch position doesn't matter).
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory. Code can be executed in this mode for debugging purposes.

Next, this program can be run in boot from flash mode. This can be done by following the instructions below:

 - Resort to CubeProgrammer to add a header to the generated binary HID_Standalone.bin with the following command
   - *STM32_SigningTool_CLI.exe -bin HID_Standalone.bin -nk -of 0x80000000 -t fsbl -o HID_Standalone-trusted.bin -hv 2.3 -dump HID_Standalone-trusted.bin*
   - The resulting binary is HID_Standalone-trusted.bin.
 - Next, in resorting again to CubeProgrammer, load the binary and its header (HID_Standalone-trusted.bin) in Nucleo board external Flash at address 0x7000'0000.
 - Set the boot mode in boot from external Flash (BOOT0 switch position is 1-2 and BOOT1 switch position is 1-2).
 - Unplug the board then plug it again. The code then executes in boot from external Flash mode.
