# ESP32-P4-Pi
[中文](/README_CN.md)

<img width="757" height="1032" alt="ESP32-p4-pi" src="image/ESP32-p4-pi.png" />

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

<img width="1222" height="1326" alt="Module_definition" src="image/Module_definition.png" />

- 1、ESP32-P4-Module

  - ESP32-P4-Core Built-in ESP32-P4NRW32、ESP32-C6、16MB Nor Flash、WIFI 6/Bluetooth 5

- 2、RGB LED

- 3、Ethernet port chip

- 4、ES8311

- 5、MIC1

- 6、Speaker interface

  - MX1.25 2P connector, supporting 8Ω2W speaker

- 7、Type-A interface

  - USB OTG 2.0 High Speed interface

- 8、100 Mbps RJ45 Ethernet port

- 9、PoE Module interface

  - Supports external PoE module connection,use PoE supply power

- 10、Display interface

  - MIPI-2lane

- 11、MIC2

- 12、 Button

  - Boot :Press when powering on or resetting to enter download mode
  - Reset button

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
<img width="718" height="1336" alt="image" src="image/pin_definition.png" />

## 5 Functional Block Diagram
The main components and connection methods of the ESP32-P4-Pi-VIEWE-Board are shown in the following figure:
<img width="1085" height="745" alt="image" src="image/flowchart.png" />

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

## 7 Software

We provide comprehensive support for **Arduino**, **PlatformIO**, and **ESP-IDF** frameworks, with pre-ported **LVGL** examples.

### 7.1 Software Examples
Examples are available in the [GitHub Repository](examples).

| Framework | Example Path | Description |
| :--- | :--- | :--- |
| **Arduino** | `examples/arduino/gui/lvgl_v8` | **LVGL Benchmark**: Usage example of lvgl v8. It can also be directly opened in the Arduino IDE. |
| **esp-idf** | `examples/esp_idf/lvgl_v9_port` | **lvgl port**: Example of porting and using lvgl in esp-idf |
| **PlatformIO**| `examples/platformio/lvgl_v8_port` | **lvgl v8 port**: Usage example of lvgl v8. |

> [!NOTE]
> **Arduino**: Not supported temporarily, but we will provide corresponding steps and launch the update as soon as possible.
> 
> **PlatformIO**: Not supported temporarily, but we will provide corresponding steps and launch the update as soon as possible.



### 7.2 Getting Started

#### 7.2.1 Preparation
* **Hardware**: ESP32-P4-PI Board, USB-C Cable.
* **Software**: VS Code (ESP-IDF v5.5+) or Arduino IDE (v2.0+) or VS Code (PlatformIO).
* **Library**: The following libraries are needed for Arduino IDE and PlatformIO

    |Libraries|version|Description|
    | :--- | :--- | :--- |
    |`ESP32_Display_Panel`| `1.0.3+` |by Espressif, This is necessary to drive the screen.|
    |`ESP32_IO_Expander`| `Arduino automatic selection` |The dependency library of `ESP32_Display_Panel` should be selected for installation together during the installation process.|
    |`esp-lib-utils`| `Arduino automatic selection` |The dependency library of `ESP32_Display_Panel` should be selected for installation together during the installation process.|
    |`lvgl`| `8.4.0` | A free and open-source embedded graphics library. |

#### 7.2.2  ESP-IDF Setup
1.  **Open platformio example**
    * go to GitHub to download the program. You can download the main branch by clicking on the "<> Code" with green text
    * Open the example using VS Code(ESP-IDF)
2.  **Compile and upload**:
    * Click `build` in the upper right corner to compile.
    * connect the microcontroller to the computer.If the compilation is correct.
    * Click `upload` in the upper right corner to download.

#### 7.2.3 Arduino Setup ([Novice tutorial](https://github.com/VIEWESMART/VIEWE-Tutorial/blob/main/Arduino%20Tutorial/Arduino%20Getting%20Started%20Tutorial.md))
1.  **Install[Arduino](https://www.arduino.cc/en/software)**
    - Choose installation based on your system type.
    - Newcomers please refer to the [beginner's tutorial](https://github.com/VIEWESMART/VIEWE-Tutorial/blob/main/Arduino%20Tutorial/Arduino%20Getting%20Started%20Tutorial.md).
2.  **Install ESP32 Board Package**:
    - Open Arduino IDE
    - Go to `File` > `Preferences`
    - Add to `Additional boards manager URLs`:
    ```
    https://espressif.github.io/arduino-esp32/package_esp32_index.json
    ```
    * Go to *Tools > Board > Boards Manager*.
    * Search `esp32` by Espressif and install version **3.0.0+**.
3.  **Install Libraries**:
    * Go to *Sketch > Include Library > Library Manager*.
    * Search `ESP32_Display_Panel` by Espressif and install version **1.0.4+**. You will be prompted whether to install its dependencies, please click **INSTALL ALL** to install all.
    * Install `lvgl` (v8.4.0 recommended).
4.  **Open example**:
    * Navigate to `File` > `Examples` > `ESP32_Display_Panel`
    * Select `Arduino` > `gui` > `lvgl_v8` > `simple_port`
5.  **Select Board**:
    * Target: `ESP32P4 Dev Module`.
    * Settings:
        * **Flash Size**: 32MB
        * **Partition Scheme**: 32M Flash
        * **PSRAM**: **OPI PSRAM** (Crucial!)
6.  **config esp supported panel board**:
    * Open the `esp_panel_board_supported_conf.h` file in the example
    * Enable this file: change the `ESP_PANEL_BOARD_DEFAULT_USE_SUPPORTED` macro definition to `1`
    * ensure you uncomment: `#define BOARD_VIEWE_ESP32_P4_PI`
    ```c
    ...
    /**
    * @brief Flag to enable supported board configuration (0/1)
    *
    * Set to `1` to enable supported board configuration, `0` to disable
    */
    #define ESP_PANEL_BOARD_DEFAULT_USE_SUPPORTED       (1)
    ...
    // #define BOARD_VIEWE_SMARTRING
    // #define BOARD_VIEWE_UEDX24240013_MD50E
    // #define BOARD_VIEWE_UEDX24320024E_WB_A
    // #define BOARD_VIEWE_UEDX24320028E_WB_A
    // #define BOARD_VIEWE_UEDX24320035E_WB_A
    // #define BOARD_VIEWE_UEDX32480035E_WB_A
    // #define BOARD_VIEWE_UEDX46460015_MD50ET
    // #define BOARD_VIEWE_UEDX48270043E_WB_A
    // #define BOARD_VIEWE_UEDX48480021_MD80E_V2
    // #define BOARD_VIEWE_UEDX48480021_MD80E
    // #define BOARD_VIEWE_UEDX48480021_MD80ET
    // #define BOARD_VIEWE_UEDX48480028_MD80ET
    // #define BOARD_VIEWE_UEDX48480040E_WB_A
    // #define BOARD_VIEWE_UEDX80480043E_WB_A
    // #define BOARD_VIEWE_UEDX80480050E_AC_A
    // #define BOARD_VIEWE_UEDX80480050E_WB_A
    // #define BOARD_VIEWE_UEDX80480050E_WB_A_2
    // #define BOARD_VIEWE_UEDX80480070E_WB_A
    #define BOARD_VIEWE_ESP32_P4_PI
    ...
    ```
7.  **Configure the example**:
    - [Optional] Edit the macro definitions in the `lvgl_v8_port.h` file
        - **If using `RGB/MIPI-DSI` interface**, change the `LVGL_PORT_AVOID_TEARING_MODE` macro definition to `1`/`2`/`3` to enable the avoid tearing function. After that, change the `LVGL_PORT_ROTATION_DEGREE` macro definition to the target rotation degree
        - **If using other interfaces**, please don't modify the `LVGL_PORT_AVOID_TEARING_MODE` and `LVGL_PORT_ROTATION_DEGREE` macro definitions
    - [Optional] Edit the macro definitions in the `lv_conf.h` file
        - **If using `SPI/QSPI` interface**, change the `LV_COLOR_16_SWAP` macro definition to `1`.
8.  **Select the correct port**:
    * Connect to the device.
    * Go to *Tools > Port*, Select the corresponding port.
9.  **Compile and upload**:
    * Click `√` in the upper right corner to compile.
    * connect the microcontroller to the computer.If the compilation is correct.
    * Click `→` in the upper right corner to download.


> [!TIP]
> **Configuration**: In `esp_panel_board_supported_conf.h`, ensure you uncomment:
> `#define BOARD_VIEWE_ESP32_P4_PI`
> Do not enable both `ESP_PANEL_BOARD_DEFAULT_USE_SUPPORTED` and `ESP_PANEL_BOARD_DEFAULT_USE_CUSTOM`
> You cannot enable multiple esp supported panel boards at the same time.

#### 7.2.4 PlatformIO Setup
1.  **Open platformio example**
    * go to GitHub to download the program. You can download the main branch by clicking on the "<> Code" with green text
    * Open the example using VS Code(PlatformIO)
2.  **Configure PlatformIO**:
    * This example uses the `BOARD_ESPRESSIF_ESP32_S3_LCD_EV_BOARD_2_V1_5` board as default. Choose `BOARD_VIEWE_UEDX24320024E_WB_A` in the `[platformio]:default_envs` of the `platformio.ini` file.
3.  **Configure the example**:
    - [Optional] Edit the macro definitions in the `lvgl_v8_port.h` file
        - **If using `RGB/MIPI-DSI` interface**, change the `LVGL_PORT_AVOID_TEARING_MODE` macro definition to `1`/`2`/`3` to enable the avoid tearing function. After that, change the `LVGL_PORT_ROTATION_DEGREE` macro definition to the target rotation degree
        - **If using other interfaces**, please don't modify the `LVGL_PORT_AVOID_TEARING_MODE` and `LVGL_PORT_ROTATION_DEGREE` macro definitions
4.  **Compile and upload the project**
    - Click the `√`(Compile) button
    - Connect the board to your computer.If the compilation is correct.
    - Click the `→`(upload) button
---

## 8 Related Documents
- [Camera Specification](peripheral/camera_datasheet.pdf)
- [Display Specification]()
- [ESP32-P4 Datasheet (Chinese)](Datasheet/P4-Core%20Datasheet/esp32-p4-chip-revision-v1.3_datasheet_cn.pdf)
- [ESP32-P4 Datasheet (English)](Datasheet/P4-Core%20Datasheet/esp32-p4-chip-revision-v1.3_datasheet_en.pdf)
- [ESP32-C6 Datasheet (Chinese)](Datasheet/P4-Core%20Datasheet/esp32-c6_datasheet_cn.pdf)
- [ESP32-C6 Datasheet (English)](Datasheet/P4-Core%20Datasheet/esp32-c6_datasheet_en.pdf)
- [ESP32-P4 Technical Reference Manual (Chinese)](Datasheet/P4-Core%20Datasheet/Esp32-p4_technical_reference_manual_cn.pdf)
- [ESP32-P4 Technical Reference Manual (English)](Datasheet/P4-Core%20Datasheet/Esp32-p4_technical_reference_manual_en.pdf)
- [ESP32-P4-Pi Datasheet](Datasheet/ESP32-P4-Pi-VIEWE_SPEC_V1.1.pdf)
- [ESP32-P4-Pi Schematic](Schematic/SCH_ESP32-ESP32-P4-Pi-VIEWE-V1.1_2025-10-23.pdf)
- [ESP32-P4-Core Schematic Diagram](Schematic/SCH_ESP32-P4-Core_2025-11-24.pdf)
- [ESP32-P4-Core Datasheet](Datasheet/P4-Core%20Datasheet/ESP32-P4-Core-VIEWE_SPEC_V1.0.pdf)
- [IMU](Datasheet/peripheral/QMI8658A.pdf)

## 9 Product Size
<img width="1185" height="1636" alt="image" src="https://github.com/user-attachments/assets/ff88e188-5feb-4968-ad8c-fd90dc912c46" />

## 10 Technical support

Contact person: VIEWE-Ayang

Email: smartrd1@viewedisplay.com

QQ technical exchange group: 1014311090

WeChat:
![wechat](image/wechat.jpg)

