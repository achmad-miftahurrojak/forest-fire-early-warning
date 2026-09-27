#include <Arduino.h>
#include <HardwareSerial.h>
#include <LoRa.h>

#include "config.h"

#if __has_include("secrets.h")
#include "secrets.h"
#else
static const char* SMS_TARGET_NUMBER = "+620000000000";
#endif

HardwareSerial sim800l(2);
static uint32_t lastAlertAt = 0;

static bool parseFloatField(const String& value, float& output) {
    if (value.isEmpty()) return false;
    output = value.toFloat();
    return isfinite(output);
}

static bool parseIntField(const String& value, int& output) {
    if (value.isEmpty()) return false;
    for (size_t i = 0; i < value.length(); i++) {
        if (!isDigit(value[i])) return false;
    }
    output = value.toInt();
    return true;
}

static void sendSMSAlert(const String& message) {
    sim800l.println("AT+CMGF=1");
    delay(100);
    sim800l.print("AT+CMGS=\"");
    sim800l.print(SMS_TARGET_NUMBER);
    sim800l.println("\"");
    delay(100);
    sim800l.print(message);
    sim800l.write(26);
    delay(1000);
}

void setup() {
    Serial.begin(115200);
    sim800l.begin(9600, SERIAL_8N1, SIM_RX, SIM_TX);
    pinMode(BUZZER_PIN, OUTPUT);
    digitalWrite(BUZZER_PIN, LOW);

    LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);
    if (!LoRa.begin(LORA_FREQUENCY)) {
        Serial.println("Starting LoRa failed!");
        while (true) delay(1000);
    }
    Serial.println("Forest Fire Hub Started. Listening on LoRa...");
}

void loop() {
    const int packetSize = LoRa.parsePacket();
    if (packetSize <= 0) return;

    String incoming;
    incoming.reserve(static_cast<size_t>(packetSize));
    while (LoRa.available()) incoming += static_cast<char>(LoRa.read());

    const int firstComma = incoming.indexOf(',');
    const int secondComma = incoming.indexOf(',', firstComma + 1);
    const int thirdComma = incoming.indexOf(',', secondComma + 1);
    const int fourthComma = incoming.indexOf(',', thirdComma + 1);
    if (firstComma <= 0 || secondComma <= firstComma ||
        thirdComma <= secondComma || fourthComma <= thirdComma) {
        Serial.println("Rejected malformed LoRa packet.");
        return;
    }

    const String node = incoming.substring(0, firstComma);
    float temp = 0.0f;
    float humidity = 0.0f;
    int smoke = 0;
    int soil = 0;
    const bool valid = parseFloatField(incoming.substring(firstComma + 1, secondComma), temp) &&
                       parseFloatField(incoming.substring(secondComma + 1, thirdComma), humidity) &&
                       parseIntField(incoming.substring(thirdComma + 1, fourthComma), smoke) &&
                       parseIntField(incoming.substring(fourthComma + 1), soil);
    if (!valid || node.length() > 16 || temp < -40.0f || temp > 85.0f ||
        humidity < 0.0f || humidity > 100.0f || smoke < 0 || soil < 0) {
        Serial.println("Rejected invalid LoRa packet.");
        return;
    }

    Serial.printf("Received node=%s temp=%.1f humidity=%.1f smoke=%d soil=%d\n",
                  node.c_str(), temp, humidity, smoke, soil);

    const bool fireRisk = temp > TEMP_HIGH && humidity < HUM_LOW && smoke > SMOKE_HIGH;
    const bool cooldownExpired = millis() - lastAlertAt >= ALERT_COOLDOWN_MS;
    if (fireRisk && cooldownExpired) {
        digitalWrite(BUZZER_PIN, HIGH);
        String alert = "FIRE ALERT from " + node + "! Temp: " + String(temp, 1) + "C.";
        sendSMSAlert(alert);
        lastAlertAt = millis();
        digitalWrite(BUZZER_PIN, LOW);
    }
}
