#include <WiFi.h>
#include <WiFiClient.h>
#include <HTTPClient.h>
#include <WiFiManager.h>

const char* serverName = "http://192.168.1.36:5000/receive_data";

void setup() {
  Serial.begin(115200);
  delay(1000);

  WiFiManager wifiManager;
  wifiManager.resetSettings();

  wifiManager.setConfigPortalTimeout(180);
  if (!wifiManager.autoConnect("ESP32_AP")) {
    Serial.println("Failed to connect and hit timeout");
    ESP.restart();
  }

  Serial.println("Connected to WiFi");

  randomSeed(analogRead(0));
}

void loop() {
  int randomData = random(0, 101);
  sendDataToServer(randomData);
  
  delay(1000);
}

void sendDataToServer(int data) {
  HTTPClient http;
  
  http.begin(serverName);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  int httpResponseCode = http.POST("data=" + String(data));
  
  if (httpResponseCode > 0) {
    Serial.print("Data sent: ");
    Serial.println(data);
  } else {
    Serial.println("Error sending data");
  }

  http.end();
}
