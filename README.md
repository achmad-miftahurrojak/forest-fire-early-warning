# Forest Fire Early Warning System

An IoT-based LoRa node-to-hub system for real-time forest fire detection and early warning alerts.

![C++](https://img.shields.io/badge/C++-11-00599C?logo=c%2B%2B&logoColor=white)
![PlatformIO](https://img.shields.io/badge/PlatformIO-Core-F56600?logo=platformio&logoColor=white)
![ESP32](https://img.shields.io/badge/ESP32-Espressif-E7352C)
![LoRa](https://img.shields.io/badge/LoRa-Communication-00A9E0)

## Table of Contents

1. [Features](#features)
2. [Architecture](#architecture)
3. [Getting Started](#getting-started)
4. [Usage](#usage)
5. [Directory Structure](#directory-structure)
6. [API Reference](#api-reference)
7. [Contributing](#contributing)
8. [License](#license)
9. [Contact](#contact)

## Features

- LoRa Communication: Long-range, low-power data transmission from sensor nodes to the central hub.
- Multi-Sensor Array: Integrates MQ-2 (gas/smoke), DHT22 (temperature/humidity), and soil moisture sensors.
- Real-Time Alerts: Automated SMS notification dispatch via SIM800L module upon critical threshold detection.
- Distributed Architecture: Separate codebases for peripheral sensor nodes and the central coordinating hub.
- Turborepo Integration: Optimized parallel build processes for multiple microcontroller targets.

## Architecture

See [ARCHITECTURE.md](ARCHITECTURE.md) for the node-to-hub data flow and alert path.

## Getting Started

### Prerequisites

- PlatformIO IDE or CLI
- Node.js (for Turborepo orchestration)
- Hardware: ESP32 development boards, LoRa SX1278 modules, various environmental sensors

### Installation Steps

```bash
git clone https://github.com/achmad-miftahurrojak/forest-fire-early-warning.git
cd hardware/forest-fire-early-warning
npm install
```

### Configuration

Ensure the correct COM ports are specified in the `platformio.ini` files within both the `node/` and `hub/` directories.

## Usage

Build the firmware for both the hub and the nodes simultaneously:
```bash
npm run build
```

To upload to a specific device, navigate to its directory:
```bash
cd hub
pio run -t upload
```

## Directory Structure

- `node/`: Firmware for distributed environmental sensor units.
- `hub/`: Firmware for the central receiver and SMS alert gateway.

## API Reference

The communication protocol between nodes and the hub utilizes a custom structured payload over LoRa. Refer to the `include/` directory within the respective project folders for data structure definitions.

## Contributing

Modifications to the LoRa payload structure must maintain backward compatibility. Verify compilation across all target boards before committing.

## License

This project is licensed under the MIT License.

## Contact

Created by Achmad Miftahurrojak.
[GitHub](https://github.com/achmad-miftahurrojak)
