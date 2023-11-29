# Electric-Payment-solution-Powered_REST_API_based_ESP32
 Tensilica_Xtensa_LX6-MCU_ESP32 platform.io
 
# ESP32 RFID Time-Based Service Controller

## Overview

This project utilizes the ESP32 microcontroller to create a versatile Time-Based Service Controller system. The system allows users to access services using RFID cards, with the ESP32 managing timers, charging based on time, and controlling a Relay 12V for service activation. Additionally, the ESP32 connects to the network via Wi-Fi, incorporates a 5-inch display, and features a GPS locator.
The code consisted of **self-made multi-thread customized input/output system that i call it CIOS**, and it come with certain commands, type ?. to show the commands in the serial monitor.

## Features

- RFID card-based access control. NFC PN532 Mifare compatibility
- ESP32DevKit-32u + IPEX Antenna
- Time-based service activation and charging.
- Wi-Fi connectivity for network communication.
- 1306i2c display user interface.
- GPS locator functionality.
- Putty and serial usb cable
- Configuration through specific commands via serial communication.

--------------------------------------------------------------------

## 개요
이 프로젝트는 ESP32 마이크로컨트롤러를 활용하여 다양한 시간 기반 서비스 컨트롤러 시스템을 만들었습니다. 이 시스템은 사용자가 RFID 카드를 사용하여 서비스에 액세스할 수 있게 하며, ESP32는 타이머 관리, 시간에 기반한 충전 및 서비스 활성화를 위한 Relay 12V 제어를 수행합니다. 더불어 ESP32는 Wi-Fi를 통해 네트워크에 연결되어 있으며, 5인치 디스플레이를 통합하고 GPS 로케이터 기능을 제공합니다. 코드는 내가 CIOS라고 부르는 자체 제작 멀티 스레드 커스터마이즈된 입출력 시스템으로 구성되어 있으며, 일부 명령어는 시리얼 모니터에서 ?를 입력하여 확인할 수 있습니다.

## 특징
RFID 카드 기반 액세스 제어. NFC PN532 Mifare 호환성
ESP32DevKit-32u + IPEX 안테나
시간 기반 서비스 활성화 및 충전.
네트워크 통신을 위한 Wi-Fi 연결.
1306i2c 디스플레이 사용자 인터페이스.
GPS 로케이터 기능.
Putty 및 시리얼 USB 케이블
시리얼 통신을 통한 특정 명령을 통한 설정.


## Getting Started

### Prerequisites

- [PlatformIO](https://platformio.org/) installed on your development environment.
- ESP32-32u development board.
- NFC PN532.
- 1306i2c display.
- GPS module.
- Relay 12V zettler for service activation.

### Installation

1. Clone this repository:

2. Open the project in PlatformIO.
   
4. Clean and build the project

5. Connect the required hardware components to the ESP32.

6. Upload the code to your ESP32 device.

### Usage

1. Power on the ESP32 with all the connected peripherals.

2. Configure the system using specific commands via serial communication.

3. Present an RFID card to the module for access.

4. The system will activate the Relay 12V based on configured timers.

5. Monitor the display for real-time information.
   
7. If you have a restful API server please add the link with open network access to the WIFI

## Configuration

The ESP32 can be configured through the serial interface. Use the provided commands to adjust settings and customize the behavior of the system.

Here are bunch of commands the CIOS contain that you can use each with its own description:

?                                  show commands
 ..                                 return
 cls                                clear screen
config_show                         show the current device configuration
config_write                        save the configuration to the memory
config_show                         show the current device configuration
config_erase                        erase all the configuration from EPROM
scan_i2c                            scans i2c connected devices
reboot                              reboot the device
buzzon                              turn on the buzzer
buzzoff                             turn off the buzzer
wifi                                access wifi advanced network configuration
unit                                access this device advanced unit configuration
CI_en                               Enable the charing indicator
wifi_scan                           scan the area for nearby wifi networks
ssid_set                            set the network ssid to connect to"      
set_unit_ip                         set this device IP address, leave empty if wifi network offers DHCP
set_destination_ip                  set the data collecting server IP address
set_url                             set the URL for the destination server
set_udp_port                        set the UDP port in case of UDP is needed
network_show                        show the running network configuration of the wifi
ping                                issues an ICMP reachability check, response (1) = reachable, 0=(not-reachable)
id_set                              set the ID (identity) of this device
id_show                             show the current ID of this device

## Libraries

Platform.io will notify you to download the necessary libraries that are needed. I cannot upload the libraries due to legal and ownership issues

## Reference for development

Using LCD_1602_class instead of the 1306i2c, follow this setup and configuration:
![MinimalisticCPU_LCD_manager_theory](https://github.com/zenith85/Electric-Payment-solution_With_Customized_Input_output_system/assets/25374965/1d160887-81a4-495c-a77f-12ea350b0c65)

In case you want to implement this project using commercial parts, follow this design:
![Wroom32PinoutConnection](https://github.com/zenith85/Electric-Payment-solution_With_Customized_Input_output_system/assets/25374965/ab5f7d48-204d-47c1-b108-8beea2178458)

## Algorithms implemeted in the code

Overall design
![image](https://github.com/zenith85/Electric-Payment-solution_With_Customized_Input_output_system/assets/25374965/730ca4bf-cee7-4d82-bf7f-3ae82ff26ed3)

Time_services_provider
![Timer_Service_Provider](https://github.com/zenith85/Electric-Payment-solution_With_Customized_Input_output_system/assets/25374965/b2779e12-dbe6-477e-aeac-75f364e43c5e)

Multi-thread Tasks Manager
![Timer_Service_Provider](https://github.com/zenith85/Electric-Payment-solution_With_Customized_Input_output_system/assets/25374965/4d1ca719-436a-4868-a2f4-5f853ea4e447)

Proposed and used Card Registeration Algorithm
![CardRegisteringAlgorithm](https://github.com/zenith85/Electric-Payment-solution_With_Customized_Input_output_system/assets/25374965/a5f01dec-b264-48f8-b41d-85578727c91b)

Screen Services Indications
![image](https://github.com/zenith85/Electric-Payment-solution_With_Customized_Input_output_system/assets/25374965/1088e524-972d-46fe-9a94-38c70cc0eee7)

## Reference for the device implementation

![image](https://github.com/zenith85/Electric-Payment-solution_With_Customized_Input_output_system/assets/25374965/46b306b1-fd8c-45d8-a562-1669ac120cc1)

![b9595ce0-928a-4dff-9230-bc64fd912560](https://github.com/zenith85/Electric-Payment-solution_With_Customized_Input_output_system/assets/25374965/ec3a0dd9-2832-464d-827a-1e0a9ea18ad5)
