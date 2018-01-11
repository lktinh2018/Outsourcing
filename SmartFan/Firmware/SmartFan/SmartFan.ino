#include <FS.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <ArduinoJson.h>

//Debug 
#define DEBUG_MODE

//Pin
#define RELAY_PIN_1 12
#define RELAY_PIN_2 14
#define RELAY_PIN_3 13
#define BUTTON_PIN  16

//Config AP
const char* ssidAP      = "Quat Thong Minh";
const char* passwordAP  = "123456789";

//Static IP
char defaultIP[16]      = "192.168.1.200";
char defaultGateway[16] = "192.168.1.1";
char defaultSubnet[16]  = "255.255.255.0";

//Create server
ESP8266WebServer server(80);

//Web Server
String content;
String st;
int statusCode;

//State Fan
byte stateFan = 0;

//Flag for saving data
bool shouldSaveConfig = false;

//Debounce button
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 300;

void setup() {
  #ifdef DEBUG_MODE  
    Serial.begin(115200);
  #endif
  initPin();
  initButton();
  initFS();
  initWiFiManager();
  initWebServer();
  initWiFi();
}

void loop() {
  loopWebServer();
}

void debug(String s) {
  #ifdef DEBUG_MODE
    Serial.println(s);
  #endif
}

