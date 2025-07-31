#include <WiFiS3.h>
#include <Wire.h>
#include <Adafruit_BMP280.h>
#include "secrets.h"

#define SEALEVELPRESSURE_HPA (1013.25)
#define LDR_PIN A0
#define MQ135_PIN A1

WiFiClient client;
Adafruit_BMP280 bmp;

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.print("Connecting to WiFi...");
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  if (!bmp.begin(0x76)) {
    Serial.println("Could not find BMP280 sensor!");
    while (1);
  }
}

void loop() {
  float temp = bmp.readTemperature();
  float pres = bmp.readPressure() / 100.0F;
  int light = analogRead(LDR_PIN);
  int airQuality = analogRead(MQ135_PIN);  // Raw value (0–1023)
  float hum = 0.0;  // Placeholder since BMP280 has no humidity

  Serial.println("--- Sensor Readings (BMP280 + MQ-135) ---");
  Serial.print("Temp: "); Serial.println(temp);
  Serial.print("Pressure: "); Serial.println(pres);
  Serial.print("Light: "); Serial.println(light);
  Serial.print("Air Quality (MQ-135): "); Serial.println(airQuality);

  // Send to ThingSpeak
  String url = "/update?api_key=ZDTV1ZDYM9BQGHDF";
  url += "&field1=" + String(temp);
  url += "&field2=" + String(hum);
  url += "&field3=" + String(pres);
  url += "&field4=" + String(light);
  url += "&field5=" + String(airQuality);

  if (client.connect("api.thingspeak.com", 80)) {
    Serial.println("Sending to ThingSpeak...");
    client.println("GET " + url + " HTTP/1.1");
    client.println("Host: api.thingspeak.com");
    client.println("Connection: close");
    client.println();
    while (client.connected() || client.available()) {
      if (client.available()) {
        String line = client.readStringUntil('\n');
        Serial.println(line);
      }
    }
    client.stop();
  } else {
    Serial.println("Connection to ThingSpeak failed.");
  }

  delay(15000);
}
