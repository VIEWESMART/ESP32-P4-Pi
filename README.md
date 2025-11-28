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

### 3 Applications
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
