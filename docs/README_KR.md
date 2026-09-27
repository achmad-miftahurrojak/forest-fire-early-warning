<div align="center">

# Forest Fire Early Warning System

<a href="../README.md"><img alt="English" src="https://img.shields.io/badge/English-DFE0E5"></a> <a href="README_ID.md"><img alt="Bahasa Indonesia" src="https://img.shields.io/badge/Bahasa%20Indonesia-DFE0E5"></a> <a href="README_KR.md"><img alt="한국어" src="https://img.shields.io/badge/%ED%95%9C%EA%B5%AD%EC%96%B4-DFE0E5"></a>

<img alt="C++" src="https://img.shields.io/badge/C%2B%2B-11-00599C?logo=c%2B%2B&logoColor=white"> <img alt="ESP32" src="https://img.shields.io/badge/ESP32-E7352C?logo=espressif&logoColor=white"> <img alt="LoRa" src="https://img.shields.io/badge/LoRa-00A9E0?logo=semtech&logoColor=white">

화재 위험을 측정하고 중앙 허브로 검증된 경보를 보내는 ESP32 LoRa 시스템입니다.

</div>

---

## 개요

노드는 온도, 습도, 연기, 토양 수분을 측정해 구조화된 payload를 LoRa로 전송합니다. 허브는 패킷을 검증하고 위험 규칙을 평가한 뒤 로컬 경보와 SMS를 활성화합니다.

## 기능

- DHT22, MQ-2, 토양 수분 센서
- 저전력 node-to-hub LoRa 통신
- 위험 평가 전 payload 검증
- 허브의 buzzer 및 SIM800L SMS 경보
- 노드와 허브를 분리한 PlatformIO 프로젝트
- 센서 노드 deep sleep 지원

## 아키텍처

payload 흐름과 node-to-hub 설계의 범위는 [ARCHITECTURE.md](../ARCHITECTURE.md)에서 확인할 수 있습니다.

## 빌드 및 업로드

필요 항목: PlatformIO, ESP32 보드, SX1278 LoRa, DHT22/MQ-2/토양 수분 센서, SIM800L.

    git clone https://github.com/achmad-miftahurrojak/forest-fire-early-warning.git
    cd forest-fire-early-warning
    npm install
    npm run build

특정 target을 업로드하려면:

    cd hub
    pio run -t upload

전화번호와 개인 값은 secret template을 참고해 로컬 설정에 보관하세요.

## 프로젝트 구조

    node/       # 배터리 센서 노드
    hub/        # LoRa receiver 및 경보 gateway
    ARCHITECTURE.md
    turbo.json

## 라이선스

[MIT](../LICENSE) · [GitHub 프로필](https://github.com/achmad-miftahurrojak)

