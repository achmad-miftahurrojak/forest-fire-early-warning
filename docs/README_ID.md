<div align="center">

# Forest Fire Early Warning System

<a href="../README.md"><img alt="English" src="https://img.shields.io/badge/English-DFE0E5"></a> <a href="README_ID.md"><img alt="Bahasa Indonesia" src="https://img.shields.io/badge/Bahasa%20Indonesia-DFE0E5"></a> <a href="README_KR.md"><img alt="한국어" src="https://img.shields.io/badge/%ED%95%9C%EA%B5%AD%EC%96%B4-DFE0E5"></a>

<img alt="C++" src="https://img.shields.io/badge/C%2B%2B-11-00599C?logo=c%2B%2B&logoColor=white"> <img alt="ESP32" src="https://img.shields.io/badge/ESP32-E7352C?logo=espressif&logoColor=white"> <img alt="LoRa" src="https://img.shields.io/badge/LoRa-00A9E0?logo=semtech&logoColor=white">

Node ESP32 LoRa untuk mengukur kondisi risiko kebakaran dan mengirim alert tervalidasi ke hub pusat.

</div>

---

## Ringkasan

Node membaca suhu, kelembapan, asap, dan kelembapan tanah, lalu mengirim payload terstruktur melalui LoRa. Hub memvalidasi paket, mengevaluasi aturan risiko, dan mengaktifkan alert lokal serta SMS.

## Fitur

- Sensor DHT22, MQ-2, dan kelembapan tanah.
- Komunikasi LoRa node-ke-hub hemat daya.
- Validasi payload sebelum evaluasi risiko.
- Buzzer dan SMS SIM800L di hub.
- Proyek PlatformIO terpisah untuk node dan hub.
- Dukungan deep sleep pada node.

## Arsitektur

Lihat [ARCHITECTURE.md](../ARCHITECTURE.md) untuk alur payload dan batas desain node-ke-hub.

## Build dan upload

Persyaratan: PlatformIO, board ESP32, modul LoRa SX1278, sensor DHT22/MQ-2/soil moisture, dan SIM800L.

    git clone https://github.com/achmad-miftahurrojak/forest-fire-early-warning.git
    cd forest-fire-early-warning
    npm install
    npm run build

Untuk upload target tertentu:

    cd hub
    pio run -t upload

Simpan nomor telepon dan nilai privat lain di konfigurasi lokal berdasarkan template secret repo.

## Struktur proyek

    node/       # Sensor node bertenaga baterai
    hub/        # Receiver LoRa dan gateway alert
    ARCHITECTURE.md
    turbo.json

## Lisensi

[MIT](../LICENSE) · [Profil GitHub](https://github.com/achmad-miftahurrojak)

