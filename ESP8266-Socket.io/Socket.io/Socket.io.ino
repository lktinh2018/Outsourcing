#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <SocketIoClient.h>

ESP8266WiFiMulti WiFiMulti;
SocketIoClient webSocket;

boolean connectFlag = false;

//Config Wifi
const char* ssid      = "Arduino_coffee_F3";
const char* password  = "78lelai@";

//Data
String jsonString = "\"Hello server, I'm ESP8266\"";

//Pin
int pin = D8;

//Status
int status = LOW;

void setup() {

  Serial.begin(115200);
  pinMode(pin, OUTPUT);
  WiFiMulti.addAP(ssid, password);

  while(WiFiMulti.run() != WL_CONNECTED) {
      delay(100);
  }

  
  webSocket.on("connect", &connectEvent);
  webSocket.on("disconnected", &disconnectedEvent);
  webSocket.on("change_status", &changeStatusEvent);
  webSocket.begin("192.168.1.16", 3000);
  Serial.println("Init Successful");
}

void loop() {
    webSocket.loop();
}

void changeStatusEvent(const char* payload, size_t length) {
  Serial.println(payload);
  status = String(payload) == "true" ? HIGH : LOW;
  Serial.println(status);
  digitalWrite(pin, status);
  
}

void connectEvent(const char* payload, size_t length) {
  Serial.println("Connected");
  webSocket.emit("connected", "\"Hello server, I'm ESP8266\"");
  connectFlag = true;
}

void disconnectedEvent(const char* payload, size_t length) {
  Serial.println("Disconnected");
  Serial.println("Reconnect");
  webSocket.begin("192.168.1.16", 3000);
  connectFlag = false;
}


