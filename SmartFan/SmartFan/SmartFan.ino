#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>


//Pin
#define RELAY_PIN 5

//Config AP
const char *ssidAP = "Smart Fan";
const char *passwordAP = "123456789";

//Create server
ESP8266WebServer server(80);

//Static IP
IPAddress ip(192, 168, 1, 200);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet (255, 255, 255, 0);

//Status device
boolean relayState = false;

//Web Server
String content;
String st;
int statusCode;


void setup() {
  Serial.begin(115200);
  EEPROM.begin(512);
  pinMode(RELAY_PIN, OUTPUT);
  initWiFi();
  digitalWrite(RELAY_PIN, LOW);
}

void loop() {
  server.handleClient();
}
