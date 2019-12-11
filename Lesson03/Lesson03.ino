#include <ESP8266WiFi.h>

#define LED 16

WiFiClient m_Client;
WiFiServer m_Server(80);

// WIFI settings
IPAddress apIP(192, 168, 4, 1);
const char* ssid = "Lesson03";
const char* password = "1234abcd";

void setup() {
  // Set pinmode
  pinMode(LED, OUTPUT);

  // Initialize WiFi with Static IP Address
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(ssid, password);
  m_Server.begin();

  delay(1000);
}

void loop() {
  // Receive WiFi command
  m_Client = m_Server.available();

  if (m_Client) {
    while (!m_Client.available()) delay(1);

    String msg = m_Client.readStringUntil('\r');
    
    msg.remove(0, 5);
    msg.remove(msg.length() - 9, 9);

    if (msg.length() > 0) {
      if (msg == "on") {
        digitalWrite(LED, LOW);
        m_Client.write("Nooo");
      }
      else digitalWrite(LED, HIGH);
    }
  }
}
