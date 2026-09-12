#include <Arduino.h>
#include <SPI.h>
#include <LoRa.h>
#include <DHT.h>

#define LORA_SS 18
#define LORA_RST 14
#define LORA_DIO0 26

#define DHTPIN 4
#define DHTTYPE DHT22
#define MQ2_PIN 32
#define SOIL_PIN 33
#define NODE_ID "N1"

DHT dht(DHTPIN, DHTTYPE);

#define uS_TO_S_FACTOR 1000000ULL
#define TIME_TO_SLEEP  300

void setup() {
  Serial.begin(115200);
  
  dht.begin();
  LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);
  
  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    delay(1000);
    ESP.restart();
  }

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  int mq2_val = analogRead(MQ2_PIN);
  int soil_val = analogRead(SOIL_PIN);

  if (isnan(h) || isnan(t)) {
    h = 0; t = 0;
  }

  String payload = String(NODE_ID) + "," + String(t, 1) + "," + String(h, 1) + "," + String(mq2_val) + "," + String(soil_val);
  
  Serial.println("Transmitting: " + payload);
  
  LoRa.beginPacket();
  LoRa.print(payload);
  LoRa.endPacket();

  Serial.println("Going to sleep now");
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  esp_deep_sleep_start();
}

void loop() {
}
