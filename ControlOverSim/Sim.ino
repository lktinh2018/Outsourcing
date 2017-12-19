void initSIM() {
  Sim.begin(9600);
  Serial.println(F("You can now send AT commands"));
}

void loopSIM() {
  while(Serial.available()) {
    Sim.write(Serial.read());
  }
  
  while(Sim.available()) {
    char c = Sim.read();
    data += c;
    if(c == '\n') {
      Serial.print(data);
      handleData(data);
      data = "";
    }
      
  }
}

void handleData(String data) {
  if(data.indexOf("+CLIP") != -1) {
    hangUp();
    Serial.println("Co cuoc goi den: ");

    byte startIndex = 8;
    byte endIndex   = data.indexOf("\"", 10);
    String phoneNum = data.substring(startIndex, endIndex);
    Serial.print(phoneNum);
  }
}

void call(String phoneNumber) {
  Sim.print("ATD" + phoneNumber + ";\r\n");
  delay(15000);
}

void sendSMS(String phoneNumber, String contentSMS) {
  Sim.print("AT+CMGF=1\r\n");
  delay(1000);
  Sim.print("AT+CSCS=\"GSM\"\r\n");
  delay(1000);
  Sim.print("AT+CMGS=\"" + phoneNumber + "\"\r\n");
  delay(2000);
  Sim.print(contentSMS + "\r\n");
  delay(1000);
  Sim.write(26);
  delay(1000);
}

void hangUp() {
  Sim.print("ATH\r\n");
}

