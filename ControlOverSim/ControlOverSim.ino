#include <SoftwareSerial.h>
SoftwareSerial Sim(2, 3); // RX, TX

#define DEBUG_MODE
#define RELAY_PIN 5

String phoneNumber = "0963366093";

boolean activatedRelay = false;

String data;
void setup() {
  // Set console baud rate
  Serial.begin(9600);
  initRelay();
  initSIM();
  delay(5000);
//  sendSMS(phoneNumber, "Hello, I'm Sim900A");
//  call(phoneNumber);
}

void loop() {
  loopSIM();
}

void debug(String s) {
  #ifdef DEBUG_MODE
    Serial.println(s);
  #endif
}
//Call phoneNumber        ATD+phoneNumber;
//Read SMS From Index 1:  AT+CMGR=1
//USSD                    AT+CUSD=1,"*101#"


