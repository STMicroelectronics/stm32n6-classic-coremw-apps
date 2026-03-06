## <b>CustomHID_CDC_ACM_RTOS Application Description </b>


This application is a part of the USB Device Library package using STM32Cube firmware. It describes how to 
use USB device application based on the CustomHID CDC composite device on the STM32N6xx devices.

This is a typical application on how to use the STM32N6xx USB Device peripheral where the STM32 MCU is
enumerated as a composite device containing 2 functions:

   <b>1 CDC function:</b>
   
   This is a typical application on how to use the STM32N6xx USB Device peripheral where the STM32 MCU
   behaves as a USB following the Virtual COM Port (VCP) implementation.
   
    - The STM32 exchanges data with a PC host through USB interface in Device mode.
    - When the VCP application is started, the STM32 MCU is enumerated as serial communication port and is
      configured in the same way (baudrate, data format, parity, stop bit) as it would configure a standard
      COM port. The 7-bit data length with no parity control is NOT supported.
    - During enumeration phase, two communication pipes "endpoints" are declared in the CDC class
      implementation (PSTN sub-class):
    - 1 x Bulk IN endpoint for receiving data from STM32 device to PC host
    - 1 x Bulk OUT endpoint for transmitting data from PC host to STM32 device

   <b>2 CustomHID function:</b>

   This is a typical application on how to use the STM32N6xx USB Device peripheral where the STM32 MCU is
   enumerated as a HID device using the native PC Host HID driver to which the STM32N6XX board is connected.

The application has three tasks:

  - app_usb_device_task: used to initialize USB device stack and start the composite CDC + CustomHID.
  - cdc_task: used to Read the received data from Virtual COM Port.
  - custom_hid_task: used to handle HID OUT reports and send input data.


#### <b>Notes</b>

- The user has to check the list of the COM ports in Device Manager to find out the COM port number that have been assigned (by OS) to the VCP interface.

#### <b>Expected success behavior</b>

When plugged to PC host, the NUCLEO-N657X0-Q must be properly enumerated as a USB Serial device and a USB custom HID device.

During the enumeration phase, the device must provide host with the requested descriptors (Device descriptor, configuration descriptor, string descriptors).
Those descriptors are used by host driver to identify the device capabilities.

  - CDC Function:

    - Open the hyperterminal to send data from host to device.

  - CustomHID function:

    - Start the "USB HID Demonstrator" PC applet, available for download from www.st.com,
      and connect STM32 USB to PC
    - The device should be detected and shown in the USB HID target box
    - Press Input/Output transfer button
    - Select "use SET_FEATURE" or "use SET_REPORT" in order to use SET_REPORT request to send HID Report
      for DATA write
    - Make sure that the following report ID is configured: DATAOUT ID(0x02)
    - Data should be visible on the "USB HID Demonstrator" under the DATAIN ID report (0x01) 
 
#### <b>Error behaviors</b>

  - LED_RED is toggling to indicate a critical error has occurred.

#### <b>Assumptions if any</b>

User is familiar with USB 2.0 "Universal Serial BUS" Specification, CDC class Specification and HID class specification.

#### <b> Known limitations</b>

None

#### <b>FreeRTOS usage hints</b>

The FreeRTOS heap size configTOTAL_HEAP_SIZE defined in FreeRTOSConfig.h is set accordingly to the
OS resources memory requirements of the application with +10% margin and rounded to the upper Kbyte boundary.

For more details about FreeRTOS implementation on STM32Cube, please refer to UM1722 "Developing Applications
on STM32Cube with RTOS".

### <b>Keywords</b>

RTOS, Connectivity, USB, USB_Device, High Speed, PSTN, CDC, VCP, HID, Custom.

### <b>Hardware and Software environment</b>

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

### <b>How to use it ?</b>

In order to make the program work, you must do the following :

 - Set the boot mode in development mode (BOOT1 switch position is 2-3, BOOT0 switch position doesn't matter).
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory. Code can be executed in this mode for debugging purposes.

Next, this program can be run in boot from flash mode. This can be done by following the instructions below:

 - Resort to CubeProgrammer to add a header to the generated binary CustomHID_CDC_ACM_RTOS_FSBL.bin with the following command
   - *STM32_SigningTool_CLI.exe -bin CustomHID_CDC_ACM_RTOS_FSBL.bin -nk -of 0x80000000 -t fsbl -o CustomHID_CDC_ACM_RTOS_FSBL-trusted.bin -hv 2.3 -dump CustomHID_CDC_ACM_RTOS_FSBL-trusted.bin*
   - The resulting binary is CustomHID_CDC_ACM_RTOS-trusted.bin.
 - Next, in resorting again to CubeProgrammer, load the binary and its header (CustomHID_CDC_ACM_RTOS_FSBL-trusted.bin) in Nucleo board external Flash at address 0x7000'0000.
 - Set the boot mode in boot from external Flash (BOOT0 switch position is 1-2 and BOOT1 switch position is 1-2).
 - Unplug the board then plug it again. The code then executes in boot from external Flash mode.