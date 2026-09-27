<div align="center">

# Forest Fire Early Warning System

<a href="README.md"><img alt="English" src="https://img.shields.io/badge/English-DFE0E5"></a> <a href="README.id.md"><img alt="Bahasa Indonesia" src="https://img.shields.io/badge/Bahasa%20Indonesia-DFE0E5"></a> <a href="README.ko.md"><img alt="한국어" src="https://img.shields.io/badge/%ED%95%9C%EA%B5%AD%EC%96%B4-DFE0E5"></a>

<img alt="C++" src="https://img.shields.io/badge/C%2B%2B-11-00599C?logo=c%2B%2B&logoColor=white"> <img alt="ESP32" src="https://img.shields.io/badge/ESP32-E7352C?logo=espressif&logoColor=white"> <img alt="LoRa" src="https://img.shields.io/badge/LoRa-00A9E0?logo=semtech&logoColor=white">

ESP32 LoRa nodes that measure fire-risk conditions and send validated alerts to a central hub.

[Features](#features) · [Architecture](ARCHITECTURE.md) · [Build](#build-and-upload) · [Project layout](#project-layout)

</div>

---

## Overview

The node reads temperature, humidity, smoke, and soil moisture signals, then sends a structured payload over LoRa. The hub validates the packet, evaluates the configured risk rule, and activates local and SMS alerts when thresholds are crossed.

## Features

- DHT22, MQ-2, and soil-moisture sensing.
- Low-power node-to-hub LoRa communication.
- Payload validation before risk evaluation.
- Buzzer and SIM800L SMS alerts at the hub.
- Separate PlatformIO projects for the node and hub.
- Deep-sleep support on sensor nodes.

## Architecture

```text
Node sensors -> LoRa payload -> Hub validation -> Risk rule
                                                /       \
                                               v         v
                                            Buzzer    SIM800L SMS
```

See [ARCHITECTURE.md](ARCHITECTURE.md) for the payload path and the limits of this node-to-hub design.

## Build and upload

### Requirements

- PlatformIO Core or PlatformIO IDE
- ESP32 boards
- LoRa SX1278 modules
- DHT22, MQ-2, and soil-moisture sensors
- SIM800L module for hub alerts

```bash
git clone https://github.com/achmad-miftahurrojak/forest-fire-early-warning.git
cd forest-fire-early-warning
npm install
npm run build
```

Upload a specific target from its directory:

```bash
cd hub
pio run -t upload
```

Keep phone numbers and other private values in local configuration files based on the repository's example secret headers.

## Project layout

```text
node/       # Battery-powered sensor node
hub/        # LoRa receiver and alert gateway
ARCHITECTURE.md
turbo.json
```

## License

[MIT](LICENSE) · [GitHub profile](https://github.com/achmad-miftahurrojak)
