# ESP32-P4-Pi
<img width="757" height="1032" alt="image" src="https://github.com/user-attachments/assets/5df0ecd5-3157-45d8-9433-5a48babc8171" />

## 1 Introduction

The ESP32-P4-Pi-VIEWE development board is designed based on the VIEWE ESP32-P4-Core module, which integrates ESP32P4 and ESP32-C6 chips and supports Wi-Fi 6 and Bluetooth 5 wireless connections. It provides a variety of Human-Machine Interface (HMI) interfaces, including MIPI-CSI (integrated with Image Signal Processor ISP), MIPI-DSI, SPI, I2S, I2C, LED PWM, MCPWM, RMT, ADC, UART, and TWAI. In addition, it supports USB OTG 2.0 H5, reserves an RJ45 Ethernet interface, can be expanded with POE (Power over Ethernet) functionality, and is equipped with a 40-pin GPIO expansion interface.

## 2 Functional Features
### 2.1 CPU

•  Equipped with a RISC-V 32-bit dual-core processor (HP system), with DSP and instruction set extensions, floating-point arithmetic unit (FPU), and a main frequency of up to 400 MHz.

•  Equipped with a RISC-V 32-bit single-core processor (LP system), with a main frequency of up to 40 MHz.

•  Equipped with an ESP32-C6 WIFI/BT coprocessor, expanding functions such as WIFI 6/Bluetooth 5 through SDIO.

### 2.2 Memory
•  128 KB of high-performance (HP) system read-only memory (ROM).

•  16 KB of low-power (LP) system read-only memory (ROM).

•  768 KB of high-performance (HP) L2 memory (L2MEM).

•  32 KB of low-power (LP) SRAM.

•  8 KB of system tightly coupled memory (TCM).

•  32 MB PSRAM is stacked and sealed inside the package, and 16MB Nor Flash is connected through the QSPI interface.

### 2.3 Peripheral Interfaces

•  Powerful image and voice processing capabilities, with dedicated image and voice processing interfaces including a JPEG codec, Pixel Processing Accelerator (PPA), Image Signal Processor (ISP), and H.264 video encoder.

•  32MB PSRAM stacked and packaged within the chip; the module integrates 16MB Nor Flash.

•  Common peripheral interfaces led out on the board: MIPI-CSI, MIPI-DSI, USB 2.0 OTG, Ethernet, SDIO 3.0 SD card slot, dual microphones, speaker terminals, and RTC battery terminals.

•  2×20 pin headers led out on the board, providing access to 28 remaining programmable GPIOs.

Security mechanisms: Secure Boot, Flash encryption, hardware encryption accelerator, and hardware random number generator. It also supports hardware access protection, enabling Access Permission Management (APM) and permission separation.

## 3 Applications
With low power consumption, ESP32-P4 is an ideal choice for IoT devices in the following areas:

•  Smart Home

•  Industrial Automation

•  Health Care

•  Consumer Electronics

•  Smart Agriculture

•  Retail Self-Service Terminals (POS, Vending Machines)

•  Service Robot

•  Multimedia Player

•  Cameras for Video Streaming

•  High-Speed USB Host and Device

•  Smart Voice Interaction Terminal

•  Edge Vision AI Processor

•  HMI Control Pane

## 4 Hardware Description
### 4.1 Module Introduction

<img width="1222" height="1326" alt="image" src="https://github.com/user-attachments/assets/ed934267-8ed3-45af-b259-e5fb03558008" />

- 1、ESP32-P4-Module

  - ESP32-P4-Core Built-in ESP32-P4NRW32、ESP32-C6、16MB Nor Flash、WIFI 6/Bluetooth 5

- 2、RGB LED

- 3、Ethernet port chip

- 4、ES8311

- 5、MIC1

- 6、Speaker interface

  - MX1.25 2P connector, supporting 8Ω2W speaker

- 7、Type-A interface

USB OTG 2.0 High Speed interface

- 8、100 Mbps RJ45 Ethernet port

- 9、PoE Module interface

  - Supports external PoE module connection,use PoE supply power

- 10、Display interface

  - MIPI-2lane

- 11、MIC2

- 12、 Button

  - Boot :Press when powering on or resetting to enter download mode
  - Reset button：

- 13、Type-C interface

  - Can be used for power supply, program burning

- 14、Type-C UART interface

  - Can be used for power supply, program burning, and debugging

- 15、CH340C

- 16、ES7210

- 17、TF card slot

  - SDIO 3.0 interface protocol

- 18、ESP32-C6 UART interface

- 19、Power indicator light

- 20、Camera interface

  - MIPI 2-lane

- 21、6-axis attitude sensor

  - 3-axis accelerometer and 3-axis gyroscope sensor

- 22、ESP32-C6 SMD ANT

  - SDIO interface protocol, expanding Wi-Fi 6 and Bluetooth 5

- 23、40PIN Pin header

### 4.2 GPIO Definition
<img width="718" height="1336" alt="image" src="https://github.com/user-attachments/assets/920ae583-4c90-4f28-8741-47dc9ce32146" />
<img width="1114" height="140" alt="image" src="https://github.com/user-attachments/assets/d22dad71-6476-416a-8447-647ca443c886" />

## 5 Functional Block Diagram
The main components and connection methods of the ESP32-P4-Pi-VIEWE-Board are shown in the following figure:
<img width="1085" height="745" alt="image" src="https://github.com/user-attachments/assets/a6587c61-f473-444c-b339-3c41ce2141a9" />

## 6 Instructions for Use
This tutorial aims to guide users to set up the software environment for ESP32-P4 hardware development, and demonstrates how to use the ESP-IDF configuration menu, compile, and download firmware to the ESP32-P4 development board through simple examples.

- Preparation
- Hardware
  - ESP32-P4-Pi-VIEWE Development Board
  - USB data cable (Type-A to Type-C, prepared as needed)
  - Computer (Windows, Linux or macOS)
- Software (It is recommended to install ESP-IDF using an integrated development environment. If you are familiar with ESP-IDF, you can start directly from the ESP-IDF terminal. You can choose any of the following development methods.)
  - VSCode + ESP-IDF plugin (recommended)
  - Eclipse + ESP-IDF plugin (Espressif-IDE)
  - Arduino IDE

## Getting-start
### ESP-IDF
  - Please go to [ESP-IDF Quick Start](https://github.com/VIEWESMART/VIEWE-Tutorial/blob/main/esp-idf/esp-idf_Beginner_Tutorial.md) to see how to quickly set up the development environment and burn the application to your development board.
  - The application examples for the development board are stored in Examples. You can configure the project options by entering idf.py menuconfig in the [examples](https://github.com/VIEWESMART/ESP32-P4-Pi/tree/main/examples/esp-idf) directory.
### Arduino IDE
We are working hard to prepare. If you need anything, please contact us.

# 7 Related Documents
- [Camera Specification]()
- [Display Specification]()
- [ESP32-P4 Datasheet (Chinese)]()
- [ESP32-P4 Datasheet (English)]()
- [ESP32-P4 Technical Reference Manual (Chinese)]()
- [ESP32-P4 Technical Reference Manual (English)]()
- [ESP32-P4-Pi Datasheet]()
- [ESP32-P4-Pi Schematic]()
- [ESP32-P4-Core Schematic Diagram]()
- [ESP32-P4-Core Datasheet]()

### 8 Product Size
<img width="1185" height="1636" alt="image" src="https://github.com/user-attachments/assets/ff88e188-5feb-4968-ad8c-fd90dc912c46" />
