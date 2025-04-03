## LwIP_UDP_Echo_Server Application Description

This application guides STM32Cube HAL API users to run UDP Echo Server application
based on Raw API of LwIP TCP/IP stack

To run this application, On the remote PC, open a command prompt window.
(In Windows, select Start > All Programs > Accessories > Command Prompt.)
At the command prompt, enter:
  C:\>echotool IP_address /p udp /r 7 /l 7 /n 15 /t 2 /d Testing LwIP UDP echo server

where:
    IP_address is the actual board's IP address. If DHCP is disabled,
    the following static IP address is used: 192.168.0.10
    /p transport layer protocol used for communication (UDP)
    /r is the actual remote port on the echo server (echo port)
    /l is the actual local port for the client (echo port)
    /n is the number of echo requests (for application, 15)
    /t is the connection timeout in seconds (for application, 2)
    /d is the message to be sent for echo

If a DHCP server is available, a dynamic IP address can be allocated by enabling
the DHCP process (#define LWIP_DHCP to 1 in lwipopts.h)
The user will be notified about the application status with the LEDs and state
messages printed on the HyperTerminal.

At the beginning of the main program the HAL_Init() function is called to reset
all the peripherals, initialize the Flash interface and the systick.
Then the SystemClock_Config() function is used to configure the system clock
(SYSCLK) to run at 600 MHz.

#### Expected success behavior
   - The board's IP address is printed on the HyperTerminal
   - LED_GREEN is ON indicating the ethernet cable is connected.
   - If the echotool utility is used the state of the replies sent by the UDP server are displayed on the PC console.

#### Error behaviors
   - LED_RED is ON indicating the ethernet cable is not connected.
   - LED_RED is toggling to indicate a critical error has occured.
   - The error message is printed on the HyperTerminal.

#### Assumptions if any
   - If the Application is using the DHCP to acquire IP address, thus a DHCP server should be reachable by the board in
   the LAN used to test the application.
   - The application is configuring the Ethernet IP with a static predefined MAC Address, make sure to change it in case
   multiple boards are connected on the same LAN to avoid any potential network traffic issues.
   - The MAC Address is defined in the stm32n6xx_hal_conf.h

#### Known limitations
None

#### Notes
 1. Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.

 2. The application needs to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.


For more details about this application, refer to UM1713 "STM32Cube interfacing with LwIP and applications

### Keywords

Connectivity, LwIP, Ethernet, TCP/IP, DHCP, echo server, UART

### Directory contents

  - LwIP/LwIP_UDP_Echo_Server/Src/main.c                      Main program
  - LwIP/LwIP_UDP_Echo_Server/Src/stm32n6xx_hal_msp.c         HAL MSP Module
  - LwIP/LwIP_UDP_Echo_Server/Src/system_stm32n6xx_fsbl.c          STM32N6xx system clock configuration file
  - LwIP/LwIP_UDP_Echo_Server/Src/stm32n6xx_it.c              STM32 interrupt handlers
  - LwIP/LwIP_UDP_Echo_Server/LWIP/App/app_ethernet.c         Ethernet specific module
  - LwIP/LwIP_UDP_Echo_Server/LWIP/App/udp_echoserver.c       udp echoserver application
  - LwIP/LwIP_UDP_Echo_Server/LWIP/Target/ethernetif.c        Interfacing LwIP to ETH driver
  - LwIP/LwIP_UDP_Echo_Server/Inc/main.h                      Main program header file
  - LwIP/LwIP_UDP_Echo_Server/Inc/stm32n6xx_it.h              STM32 interrupt handlers header file
  - LwIP/LwIP_UDP_Echo_Server/Inc/stm32n6xx_hal_conf.h        HAL configuration file
  - LwIP/LwIP_UDP_Echo_Server/Inc/stm32n6xx_nucleo_conf.h     NUCLEO-N663ZI configuration file
  - LwIP/LwIP_UDP_Echo_Server/LWIP/App/app_ethernet.h         header of app_ethernet.c file
  - LwIP/LwIP_UDP_Echo_Server/LWIP/App/udp_echoserver.h       Header for udp echoserver application
  - LwIP/LwIP_UDP_Echo_Server/LWIP/Target/ethernetif.h        header for ethernetif.c file
  - LwIP/LwIP_UDP_Echo_Server/LWIP/Target/lwipopts.h          LwIP stack configuration options

### Hardware and Software environment

  - This application runs on STM32N657X0H3QU devices.

  - This application has been tested with the following environments:
     - NUCLEO-N657X0-Q boards revision MB1940-N657X0Q-C01
     - echotool: (http://bansky.net/echotool/) is used as echo client that sends
       data to the server and checking whether they came back
     - DHCP server:  PC utility TFTPD32 (http://tftpd32.jounin.net/) is used as a DHCP server

  - This application uses USART1 to display logs, the hyperterminal configuration is as follows:
      - BaudRate = 115200 baud
      - Word Length = 8 Bits
      - Stop Bit = 1
      - Parity = None
      - Flow control = None

  - NUCLEO-N657X0-Q Set-up
    - Connect the nucleo board to remote PC (through a crossover ethernet cable)
      or to your local network (through a straight ethernet cable)

  - Remote PC Set-up
    - PC must share the same LAN network configuration with the NUCLEO-N657X0-Q board


### How to use it ?

In order to make the program work, you must do the following :

 - Set the boot mode in development mode (BOOT1 switch position is 2-3, BOOT0 switch position doesn't matter).
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory. Code can be executed in this mode for debugging purposes.

Next, this program can be run in boot from flash mode. This can be done by following the instructions below:

 - Resort to CubeProgrammer to add a header to the generated binary LwIP_UDP_Echo_Server.bin with the following command
   - *STM32_SigningTool_CLI.exe -bin LwIP_UDP_Echo_Server.bin -nk -of 0x80000000 -t fsbl -o LwIP_UDP_Echo_Server-trusted.bin -hv 2.3 -dump LwIP_UDP_Echo_Server-trusted.bin*
   - The resulting binary is LwIP_UDP_Echo_Server-trusted.bin.
 - Next, in resorting again to CubeProgrammer, load the binary and its header (LwIP_UDP_Echo_Server-trusted.bin) in Nucleo board external Flash at address 0x7000'0000.
 - Set the boot mode in boot from external Flash (BOOT0 switch position is 1-2 and BOOT1 switch position is 1-2).
 - Press the reset button. The code then executes in boot from external Flash mode.
