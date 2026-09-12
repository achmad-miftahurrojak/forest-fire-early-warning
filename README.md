# Forest Fire Early Warning System

A LoRa mesh network architecture designed for early forest fire detection in areas lacking internet connectivity.

![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)
![Platform: ESP32](https://img.shields.io/badge/Platform-ESP32-lightgrey.svg)
![Language: C++](https://img.shields.io/badge/Language-C++-red.svg)

## Table of Contents
1. [Features](#features)
2. [Hardware Requirements](#hardware-requirements)
3. [Getting Started](#getting-started)
4. [Usage](#usage)
5. [Directory Structure](#directory-structure)
6. [Contributing](#contributing)
7. [License](#license)
8. [Contact](#contact)

## Features
* Dual architecture consisting of ultra low power sensor nodes and a central alert hub.
* Advanced power saving using ESP32 deep sleep functionality for field nodes.
* String compression algorithms to optimize LoRa payload bandwidth.
* Dual alerting mechanism via an active siren and automated SMS notifications.

## Hardware Requirements
* ESP32 Development Boards
* LoRa Transceivers (915MHz)
* DHT22 Temperature and Humidity Sensor
* MQ-2 Gas and Smoke Sensor
* Capacitive Soil Moisture Sensor
* SIM800L GSM Module
* Active Buzzer

## Getting Started

### Prerequisites
* PlatformIO installed on your development machine.

### Installation
```bash
git clone https://github.com/hamin-baek/forest-fire-early-warning.git
cd forest-fire-early-warning/node
pio run --target upload
cd ../hub
pio run --target upload
```

## Usage
Deploy the sensor node in the target area and power the central hub at a monitoring station. The node will sample data and enter deep sleep. The hub will remain active to receive packets and trigger alerts if fire risk thresholds are met.

## Directory Structure
```text
node/
  src/main.cpp      # Sensor node firmware
  platformio.ini    # Node build configuration
hub/
  src/main.cpp      # Central hub firmware
  platformio.ini    # Hub build configuration
```

## Contributing
We welcome contributions. Please review the open issues and submit pull requests for enhancements.

## License
This project is licensed under the MIT License.

## Contact
Developed by Achmad Miftahurrojak.
GitHub: [hamin-baek](https://github.com/hamin-baek)

***
**Description:** LoRa based wireless sensor network for forest fire detection.
**Tags:** lora, esp32, wireless-sensor-network
