#include <SoftwareSerial.h>
SoftwareSerial Sim(2, 3); // RX, TX

String phoneNumber = "0963366093";

String data;
void setup() {
  // Set console baud rate
  Serial.begin(9600);
  initSIM();
  delay(5000);
//  sendSMS(phoneNumber, "Hello, I'm Sim900A");
//  call(phoneNumber);
}

void loop() {
  loopSIM();
}

//Call phoneNumber        ATD+phoneNumber;
//Read SMS From Index 1:  AT+CMGR=1

