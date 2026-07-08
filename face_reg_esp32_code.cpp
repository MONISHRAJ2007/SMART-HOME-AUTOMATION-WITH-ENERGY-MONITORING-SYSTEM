#include <WiFi.h>
#include <WebServer.h>
#include <ESP32Servo.h>

const char* ssid = "POCO M5";
const char* password = "123456789";

WebServer server(80);

Servo doorServo;
int servoPin = 13;

// Track door state
bool isOpen = false;
unsigned long openTime = 0;

void unlockDoor() {
  Serial.println("🔓 OPEN COMMAND RECEIVED");

  doorServo.write(90);   // OPEN
  isOpen = true;
  openTime = millis();

  server.send(200, "text/plain", "Door Opened");
}

void setup() {
  Serial.begin(115200);

  // Servo setup
  doorServo.setPeriodHertz(50);      // REQUIRED for ESP32
  doorServo.attach(servoPin, 500, 2400);

  doorServo.write(0);  // CLOSED position

  WiFi.begin(ssid, password);

  Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  server.on("/unlock", unlockDoor);
  server.begin();
}

void loop() {
  server.handleClient();

  // Auto close after 5 seconds
  if (isOpen && millis() - openTime > 2000) {
    Serial.println("🔒 AUTO CLOSE");

    doorServo.write(0);   // CLOSE
    isOpen = false;
  }
}