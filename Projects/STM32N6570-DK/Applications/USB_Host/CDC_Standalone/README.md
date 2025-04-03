## CDC_Standalone Application Description

This application is a part of the USB Host Library package using STM32Cube firmware. It describes how to use
USB host application based on the Communication Class (CDC) on the STM32N657X0H3QU devices.

This is a typical application on how to use the STM32N657X0H3QU USB OTG Host peripheral to interact with an USB
CDC device application based on the two CDC transfer directions with a dynamic serial configuration:

 - Transmission:
   by pressing the user1 button a message "USB_STM32_Host_CDC_ACM" will be sent from the host to a device and this message will be displayed in the hyper terminal of the device in hyperterminal
   The data to be transmitted is stored in the CDC_TX_Buffer and can be viewed via the Hyperterminal.

 - Reception:
   The data entered by the user using the Hyperterminal in ASCII format is transferred by the device board
   to the host board and displayed on the hyperterminal on the host side.
   The CDC_RX_Buffer is the buffer used for receiving data.

At the beginning of the main program the HAL_Init() function is called to reset
all the peripherals, initialize the Flash interface and the systick.
The SystemClock_Config() function is used to configure the system clock for STM32N657XXXXX Devices :
The CPU at 200MHz

#### <b>Expected success behavior</b>

When a CDC device is plugged to STM32N6570-DK board, a message will be displayed on the UART HyperTerminal showing
the Vendor ID and Product ID of the attached device.
After enumeration phase, a message will indicate that the device is ready for use.
Open two hyperterminals (USB com port and UART com port(USB STLink VCP)) to send/receive data to/from host from/to device.

#### <b>Error behaviors</b>

  - Errors are detected (such as unsupported device, enumeration fail) and the corresponding message is displayed on the HyperTerminal.
  - LED_RED is toggling to indicate a critical error has occured.

#### <b>Assumptions if any</b>

User is familiar with USB 2.0 "Universal Serial BUS" specification and CDC class specification.

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

Connectivity, UART/USART, USB_Host, Type C, USB, CDC

### Directory contents

  - USB_Host/CDC_Standalone/Core/Src/main.c                         Main program
  - USB_Host/CDC_Standalone/Core/Src/system_stm32n6xx.c             STM32N6xx system clock configuration File
  - USB_Host/CDC_Standalone/Core/Src/stm32n6xx_it.c                 Interrupt handlers
  - USB_Host/CDC_Standalone/Core/Src/stm32n6xx_hal_msp.c            HAL MSP Module
  - USB_Host/CDC_Standalone/Core/Inc/main.h                         Main program header File
  - USB_Host/CDC_Standalone/Core/Inc/stm32n6xx_hal_conf.h           HAL configuration File
  - USB_Host/CDC_Standalone/Core/Inc/stm32n6xx_it.h                 Interrupt handlers header File
  - USB_Host/CDC_Standalone/USB_Host/App/usb_host.c                 CDC State Machine
  - USB_Host/CDC_Standalone/USB_Host/App/cdc_receive.c              CDC receive functions File
  - USB_Host/CDC_Standalone/USB_Host/App/cdc_send.c                 CDC send functions File
  - USB_Host/CDC_Standalone/USB_Host/App/usb_host.h                 CDC State Machine Header File
  - USB_Host/CDC_Standalone/USB_Host/App/cdc_receive.h              CDC receive functions Header File
  - USB_Host/CDC_Standalone/USB_Host/App/cdc_send.h                 CDC send functions Header File
  - USB_Host/CDC_Standalone/USB_Host/Target/usbh_conf.c             General low level driver configuration
  - USB_Host/CDC_Standalone/USB_Host/Target/usbh_conf.h             USB Host driver configuration File

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

    A second virtual COM port will then appear in the HyperTerminal when plugging the device:
     - Hyperterminal configuration
       - Data Length = 8 Bits
       - One Stop Bit
       - No parity
       - BaudRate = 115200 baud
       - Flow control: None

     - To send data from the USB CDC Host use the user push-button USER1 and data will be received
       and displayed in the HyperTerminal connected to the CDC Device.

  - **EWARM** : To monitor a variable in the live watch window, you must proceed as follow :
    - Start a debugging session.
    - Open the View > Images.
    - Double-click to deselect the second instance of project.out.

### How to use it ?

In order to make the program work, you must do the following :

  - Set the boot mode in development mode (BOOT1 switch position is 1-3, BOOT0 switch position doesn't matter).
  - Open your preferred toolchain
  - Rebuild all files and load your image into target memory. Code can be executed in this mode for debugging purposes.
  - Open the configured uart HyperTerminal in order to display debug messages.
  - Run the application

 Next, this program can be run in boot from flash mode. This is done by following the instructions below:

 - Resort to CubeProgrammer to add a header to the generated binary CDC_Standalone.bin with the following command
   - *STM32_SigningTool_CLI.exe -bin CDC_Standalone.bin -nk -of 0x80000000 -t fsbl -o CDC_Standalone-trusted.bin -hv 2.3 -dump CDC_Standalone-trusted.bin*
   - The resulting binary is CDC_Standalone-trusted.bin.
 - Next, in resorting again to CubeProgrammer, load the binary and its header (CDC_Standalone-trusted.bin) in DK board external Flash at address 0x7000'0000.
 - Set the boot mode in boot from external Flash (BOOT0 switch position is 1-2 and BOOT1 switch position is 1-2).
 - Press the reset button. The code then executes in boot from external Flash mode.

### <b>Note</b>

The user has to check the list of the COM ports in Device Manager to find out the number
of the COM ports that have been assigned (by OS) to the Stlink VCP.
The application uses the external HSE clock as USB source clock.
