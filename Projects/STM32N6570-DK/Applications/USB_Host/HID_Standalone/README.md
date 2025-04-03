## HID_Standalone Application Description

This application is a part of the USB Host Library package using STM32Cube firmware. It describes how to use
USB host application based on the Human Interface Class (HID) on the STM32N657X0H3QU devices.

This is a typical application on how to use the STM32N657X0H3QU USB OTG Host peripheral to interact with an USB
HID Device such as a Mouse or a Keyboard.

At the beginning of the main program the HAL_Init() function is called to reset
all the peripherals, initialize the Flash interface and the systick.
The SystemClock_Config() function is used to configure the system clock for STM32N657XXXXX Devices :
The CPU at 200MHz

#### <b>Expected success behavior</b>

When a HID device is plugged to STM32N6570-DK board, a message will be displayed on the UART HyperTerminal showing
the Vendor ID and Product ID of the attached device.
After enumeration phase, a message will indicate that the device is ready for use.
The host must be able to properly decode HID reports sent by the corresponding device and display those information on the HyperTerminal.

The received HID reports are used by host to identify:
- in case of a mouse
   - (x,y) mouse position
   - Wheel position
   - Pressed mouse buttons

- in case of a keyboard
   - Pressed key

#### <b>Error behaviors</b>

  - Errors are detected (such as unsupported device, enumeration fail) and the corresponding message is displayed on the HyperTerminal.
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


For more details about the STM32Cube USB Host library, please refer to UM1720
"STM32Cube USB Host library".

-  2. In case of using an AZERTY keyboard, user should add "AZERTY_KEYBOARD" define to ensure correct
displaying taped characters.

It is possible to fine tune needed USB Host features by modifying defines values in USBH configuration
file “usbh_conf.h” available under the project includes directory, in a way to fit the application
requirements, such as:
- Level of debug: USBH_DEBUG_LEVEL
                  0: No debug messages
                  1: Only User messages are shown
                  2: User and Error messages are shown
                  3: All messages and internal debug messages are shown
   By default debug messages are displayed on the debugger IO terminal; to redirect the Library
   messages to uart terminal, stm32n6xx_hal_uart.c driver needs to be added to the application sources.
   Debug messages are displayed on the uart terminal using ST-Link.


### Keywords

Connectivity, USB_Host, USB, HID, Human Interface, Mouse, Keyboard


### Directory contents

  - USB_Host/HID_Standalone/Core/Src/main.c                         Main program
  - USB_Host/HID_Standalone/Core/Src/system_stm32n6xx.c             STM32N6xx system clock configuration File
  - USB_Host/HID_Standalone/Core/Src/stm32n6xx_it.c                 Interrupt handlers
  - USB_Host/HIS_Standalone/Core/Src/stm32n6xx_hal_msp.c            HAL MSP Module
  - USB_Host/HID_Standalone/Core/Inc/main.h                         Main program header File
  - USB_Host/HID_Standalone/Core/Inc/stm32n6xx_hal_conf.h           HAL configuration File
  - USB_Host/HID_Standalone/Core/Inc/stm32n6xx_it.h                 Interrupt handlers header File
  - USB_Host/HID_Standalone/USB_Host/App/usb_host.c                 HID State Machine
  - USB_Host/HID_Standalone/USB_Host/App/mouse.c                    HID mouse functions File
  - USB_Host/HID_Standalone/USB_Host/App/keyboard.c                 HID keyboard functions File
  - USB_Host/HID_Standalone/USB_Host/App/usb_host.h                 HID State Machine Header File
  - USB_Host/HID_Standalone/USB_Host/App/mouse.h                    HID mouse functions Header File
  - USB_Host/HID_Standalone/USB_Host/App/keyboard.h                 HID keyboard functions Header File
  - USB_Host/HID_Standalone/USB_Host/Target/usbh_conf.c             General low level driver configuration
  - USB_Host/HID_Standalone/USB_Host/Target/usbh_conf.h             USB Host driver configuration File

### Hardware and Software environment

  - This application runs on STM32N657X0H3QU devices.

  - This application has been tested with STMicroelectronics STM32N6570-DK boards Revision MB1939-N6570-C01 and can be easily tailored to any other supported device and development board.

- STM32N6570-DK Set-up
    - Plug the USB key into the STM32N657xx board through 'Type C' cable to the connector:
      - CN18 : to use USB High Speed OTG IP
    - Connect ST-Link cable to the PC USB port to display data on the HyperTerminal.

  - A virtual COM port will then appear in the HyperTerminal:
     - Hyperterminal configuration
       - Data Length = 8 Bits
       - One Stop Bit
       - No parity
       - BaudRate = 115200 baud
       - Flow control: None

  - **EWARM** : To monitor a variable in the live watch window, you must proceed as follow :
    - Start a debugging session.
    - Open the View > Images.
    - Double-click to deselect the second instance of HID_Standalone.out.

### How to use it ?

In order to make the program work, you must do the following :

  - Set the boot mode in development mode (BOOT1 switch position is 1-3, BOOT0 switch position doesn't matter).
  - Open your preferred toolchain
  - Rebuild all files and load your image into target memory. Code can be executed in this mode for debugging purposes.
  - Open the configured uart HyperTerminal in order to display debug messages.
  - Run the application

 Next, this program can be run in boot from flash mode. This is done by following the instructions below:

 - Resort to CubeProgrammer to add a header to the generated binary HID_Standalone.bin with the following command
   - *STM32_SigningTool_CLI.exe -bin HID_Standalone.bin -nk -of 0x80000000 -t fsbl -o HID_Standalone-trusted.bin -hv 2.3 -dump HID_Standalone-trusted.bin*
   - The resulting binary is HID_Standalone-trusted.bin.
 - Next, in resorting again to CubeProgrammer, load the binary and its header (HID_Standalone-trusted.bin) in DK board external Flash at address 0x7000'0000.
 - Set the boot mode in boot from external Flash (BOOT0 switch position is 1-2 and BOOT1 switch position is 1-2).
 - Press the reset button. The code then executes in boot from external Flash mode.

### <b>Note</b>

The user has to check the list of the COM ports in Device Manager to find out the number
of the COM ports that have been assigned (by OS) to the Stlink VCP.
The application uses the external HSE clock as USB source clock.

