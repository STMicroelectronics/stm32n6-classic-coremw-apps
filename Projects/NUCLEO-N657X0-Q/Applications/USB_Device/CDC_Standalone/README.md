## CDC_Standalone Application Description

This application is a part of the USB Device Library package using STM32Cube firmware.
 It describes how to
use USB device application based on the Device Communication Class (CDC) following the PSTN subprotocol
in the STM32N6xx devices using the OTG-USB and UART peripherals.

This is a typical application on how to use the STM32N6xx USB OTG Device peripheral where the STM32 MCU
behaves as a USB-to-UART bridge following the Virtual COM Port (VCP) implementation.
 - On one side, the STM32 exchanges data with a PC host through USB interface in Device mode.
 - On the other side, the STM32 exchanges data with other devices (same host, other host,
   other devices ) through the UART interface.

At the beginning of the main program the HAL_Init() function is called to reset all the peripherals,
initialize the Flash interface and the systick. The user is provided with the SystemClock_Config()
function to configure the system clock (SYSCLK) to run at 200 MHz.
The high speed OTG IP in high speed mode (HS) uses HSE clock.

When the VCP application is started, the STM32 MCU is enumerated as serial communication port and is
configured in the same way (baudrate, data format, parity, stop bit) as it would configure a standard
COM port. The 7-bit data length with no parity control is NOT supported.

During enumeration phase, three communication pipes "endpoints" are declared in the CDC class
implementation (PSTN sub-class):
 - 1 x Bulk IN endpoint for receiving data from STM32 device to PC host:
   When data are received over UART they are saved in the buffer "UserTxBuffer". Periodically, in a
   timer callback the state of the buffer "UserTxBuffer" is checked. If there are available data, they
   are transmitted in response to IN token otherwise it is NAKed.
   The polling period depends on "CDC_POLLING_INTERVAL" value.

 - 1 x Bulk OUT endpoint for transmitting data from PC host to STM32 device:
   When data are received through this endpoint they are saved in the buffer "UserRxBuffer" then they
   are transmitted over UART using interrupt mode and in meanwhile the OUT endpoint is NAKed.
   Once the transmission is over, the OUT endpoint is prepared to receive next packet in
   HAL_UART_TxCpltCallback().

 - 1 x Interrupt IN endpoint for setting and getting serial-port parameters:
   When control setup is received, the corresponding request is executed in CDC_Itf_Control().
   In this application, two requests are implemented:
    - Set line: Set the bit rate, number of Stop bits, parity, and number of data bits
    - Get line: Get the bit rate, number of Stop bits, parity, and number of data bits
   The other requests (send break, control line state) are not implemented.

#### <b>Expected success behavior</b>

When plugged to PC host, the NUCLEO-N657X0-Q must be properly enumerated as a USB Serial device and an STlink COM port.
During the enumeration phase, device provides host with the requested descriptors (device, configuration, string).
Those descriptors are used by host driver to identify the device capabilities.
Once the NUCLEO-N657X0-Q USB device successfully completed the enumeration phase, open two hyperterminals
(USB com port and UART com port(USB STLink VCP)) to send/receive data to/from host from/to device.

#### <b>Error behaviors</b>

  - LED_RED is toggling to indicate a critical error has occured.

#### <b>Assumptions if any</b>

User is familiar with USB 2.0 "Universal Serial BUS" specification and CDC class specification.

#### <b>Known limitations</b>

None

#### Notes
 1. Receiving data over UART is handled by interrupt while transmitting is handled by DMA allowing
      hence the application to receive data at the same time it is transmitting another data (full-
      duplex feature).

The support of the VCP interface is managed through the ST Virtual COM Port driver available for
download from www.st.com.

 2. The user has to check the list of the COM ports in Device Manager to find out the number of the
      COM ports that have been assigned (by OS) to the VCP interface.

This application uses UART as a communication interface. The UART instance and associated resources
(GPIO, NVIC) can be tailored in "usbd_cdc_if.h" header file according to your hardware
configuration. Moreover, this application can be customized to communicate with interfaces other than UART.
For that purpose a template CDC interface is provided in:
Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src directory.


To run this application, the user can use one of the following configurations:

 - Configuration 1:
   Connect USB cable to host and UART (STLK) to a different host (PC or other device) or to same host.
   In this case, you can open two hyperterminals to send/receive data to/from host to/from device.

 - Configuration 2:
   Connect USB cable to Host and connect UART TX pin to UART RX pin on the NUCLEO-N657X0-Q board
   (Loopback mode). In this case, you can open one terminal (relative to USB com port or UART com port)
   and all data sent from this terminal will be received by the same terminal in loopback mode.
   This mode is useful for test and performance measurements.

 3. If using this example in loopback mode (ie. USART Tx IO connected to USART Rx IO on STM32 side)
and with baudrates higher than 9600, there might be communication errors.

 4. Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.

 5. The application needs to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

For more details about the STM32Cube USB Device library, please refer to UM1734
"STM32Cube USB Device library".

### Keywords

Connectivity, USB_Device, USB, UART, High Speed, CDC, PSTN,  USB-to-UART, Bridge, VCP, Com port

### Directory contents

  - USB_Device/CDC_Standalone/Core/Src/main.c                        Main program
  - USB_Device/CDC_Standalone/Core/Src/system_stm32n6xx.c            STM32N6xx system clock configuration file
  - USB_Device/CDC_Standalone/Core/Src/stm32n6xx_it.c                Interrupt handlers
  - USB_Device/CDC_Standalone/Core/Src/stm32n6xx_hal_msp.c           HAL MSP module
  - USB_Device/CDC_Standalone/USB_Device/Target/usbd_conf.c          General low level driver configuration
  - USB_Device/CDC_Standalone/USB_Device/App/usbd_desc.c             USB device CDC descriptor
  - USB_Device/CDC_Standalone/USB_Device/App/usbd_cdc_if.c           USBD CDC interface
  - USB_Device/CDC_Standalone/USB_Device/App/usbd_device.c           USB Device
  - USB_Device/CDC_Standalone/Core/Inc/stm32n6xx_hal_conf.h          HAL configuration file
  - USB_Device/CDC_Standalone/Core/Inc/main.h                        Main program header file
  - USB_Device/CDC_Standalone/Core/Inc/stm32n6xx_it.h                Interrupt handlers header file
  - USB_Device/CDC_Standalone/Core/Inc/stm32n6xx_nucleo_conf.h       Nucleo board configuration file.
  - USB_Device/CDC_Standalone/USB_Device/Target/usbd_conf.h          USB device driver Configuration file
  - USB_Device/CDC_Standalone/USB_Device/App/usbd_desc.h             USB device CDC descriptor header file
  - USB_Device/CDC_Standalone/USB_Device/App/usbd_device.h           USB Device header
  - USB_Device/CDC_Standalone/USB_Device/App/usbd_cdc_if.h           USBD CDC interface header file
  - USB_Device/CDC_Standalone/USB-PD/Target/usbpd_devices_conf.h     UCPD device configuration file
  - USB_Device/CDC_Standalone/USB-PD/Target/usbpd_dpm_conf.h         UCPD stack configuration file

### Hardware and Software environment

  - This application runs on STM32N657X0H3QU devices.
  - This application has been tested with STMicroelectronics NUCLEO-N657X0-Q boards Revision MB1940-N657XOQ-C01 and can be easily tailored to any other supported device and development board.

  - **EWARM** : To monitor a variable in the live watch window, you must proceed as follow :
    - Start a debugging session.
    - Open the View > Images.
    - Double-click to deselect the second instance of project.out. 

  - NUCLEO-N657X0-Q set-up:
    - Connect the NUCLEO-N657X0-Q board CN8 to the PC through "TYPE-C" to "Standard A" cable.
    - For VCP the configuration is dynamic for example it can be :
        - BaudRate = 115200 baud
        - Word Length = 8 Bits
        - Stop Bit = 1
        - Parity = None
        - Flow control = None

  - The USART1 interface available on PE5 and PE6 of the microcontroller are connected to ST-LINK MCU. By default the USART1 communication between the target MCU and ST-LINK MCU is enabled.
  Its configuration is as follows:
    - BaudRate = 115200 baud
    - Word Length = 8 Bits
    - Stop Bit = 1
    - Parity = None
    - Flow control = None

### How to use it ?

In order to make the program work, you must do the following :

 - Set the boot mode in development mode (BOOT1 switch position is 2-3, BOOT0 switch position doesn't matter).
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory. Code can be executed in this mode for debugging purposes.

Next, this program can be run in boot from flash mode. This can be done by following the instructions below:

 - Resort to CubeProgrammer to add a header to the generated binary CDC_Standalone.bin with the following command
   - *STM32_SigningTool_CLI.exe -bin CDC_Standalone.bin -nk -of 0x80000000 -t fsbl -o CDC_Standalone-trusted.bin -hv 2.3 -dump CDC_Standalone-trusted.bin*
   - The resulting binary is CDC_Standalone-trusted.bin.
 - Next, in resorting again to CubeProgrammer, load the binary and its header (CDC_Standalone-trusted.bin) in Nucleo board external Flash at address 0x7000'0000.
 - Set the boot mode in boot from external Flash (BOOT0 switch position is 1-2 and BOOT1 switch position is 1-2).
 - Unplug the board then plug it again. The code then executes in boot from external Flash mode.
