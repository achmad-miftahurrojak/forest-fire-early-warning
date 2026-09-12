# Forest Fire Early Warning System

A LoRa mesh-based early warning system designed to detect forest fires in remote areas with zero internet connectivity. The architecture consists of ultra-low-power sensor nodes deployed in the field and a central hub receiver stationed at a local monitoring post.

## System Architecture

### 1. Sensor Node (`/node`)
The sensor node gathers environmental data and transmits it wirelessly.

*   **Extreme Power Saving:** Leverages ESP32 Deep Sleep, waking up only every 5 minutes to read sensors and transmit data, allowing months of battery life.
*   **Data Compression:** Compresses sensor readings into a lightweight, comma-separated string to minimize LoRa bandwidth and transmission time.
*   **Sensors:** Monitors Temperature and Humidity (DHT22), Smoke (MQ-2), and Soil Moisture.

### 2. Central Hub (`/hub`)
The central hub listens for incoming LoRa packets and triggers alerts.

*   **Fire Detection Engine:** Evaluates incoming data against critical fire risk thresholds (high temperature, low humidity, high smoke).
*   **Dual Alerting:** Triggers a local siren (buzzer) and dispatches an SMS alert via a SIM800L GSM module when a fire risk is confirmed.

## Hardware Requirements

*   **Node:** ESP32, LoRa Transceiver (915MHz), DHT22, MQ-2 Gas Sensor, Capacitive Soil Moisture Sensor.
*   **Hub:** ESP32, LoRa Transceiver (915MHz), SIM800L GSM Module, Active Buzzer.

## Software Stack

*   **Environment:** PlatformIO / Arduino framework
*   **Language:** C++
*   **Libraries:** `SPI`, `LoRa`, `DHT sensor library`, `HardwareSerial`

## Setup Instructions

1.  Open the `/node` and `/hub` folders as separate PlatformIO projects.
2.  Upload the respective firmware to your ESP32 boards.
3.  Ensure both LoRa modules are configured to the same frequency band (e.g., 915MHz).
