#include <Arduino.h>
#include <SPI.h>
#include <LoRa.h>
#include <HardwareSerial.h>

#define LORA_SS 18
#define LORA_RST 14
#define LORA_DIO0 26
#define BUZZER_PIN 25
#define SIM_TX 17
#define SIM_RX 16

HardwareSerial sim800l(2);

const float TEMP_HIGH = 40.0;
const float HUM_LOW = 30.0;
const int SMOKE_HIGH = 2000;

void setup() {
  Serial.begin(115200);
  sim800l.begin(9600, SERIAL_8N1, SIM_RX, SIM_TX);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);
  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  Serial.println("Forest Fire Hub Started. Listening on LoRa...");
}

void sendSMSAlert(String message) {
  sim800l.println("AT+CMGF=1");
  delay(100);
  sim800l.println("AT+CMGS=\"+6281234567890\"");
  delay(100);
  sim800l.print(message);
  delay(100);
  sim800l.write(26);
  delay(1000);
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    String incoming = "";
    while (LoRa.available()) {
      incoming += (char)LoRa.read();
    }
    Serial.println("Received: " + incoming);

    int firstComma = incoming.indexOf(',');
    int secComma = incoming.indexOf(',', firstComma + 1);
    int thirdComma = incoming.indexOf(',', secComma + 1);
    int fourthComma = incoming.indexOf(',', thirdComma + 1);

    if (firstComma > 0 && secComma > 0 && thirdComma > 0) {
      String node = incoming.substring(0, firstComma);
      float temp = incoming.substring(firstComma + 1, secComma).toFloat();
      float hum = incoming.substring(secComma + 1, thirdComma).toFloat();
      int smoke = incoming.substring(thirdComma + 1, fourthComma).toInt();

      bool fire_risk = (temp > TEMP_HIGH) && (hum < HUM_LOW) && (smoke > SMOKE_HIGH);

      if (fire_risk) {
        Serial.println("FIRE RISK DETECTED!");
        digitalWrite(BUZZER_PIN, HIGH);
        String alertMsg = "FIRE ALERT from " + node + "! Temp: " + String(temp) + "C, Smoke detected!";
        sendSMSAlert(alertMsg);
        delay(5000);
        digitalWrite(BUZZER_PIN, LOW);
      }
    }
  }
}
