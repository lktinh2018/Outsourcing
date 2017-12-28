void initSIM() {
  Sim.begin(9600);
  debug(F("You can now send AT commands"));
}

void loopSIM() {
  while(Serial.available()) {
    Sim.write(Serial.read());
  }
  
  while(Sim.available()) {
    char c = Sim.read();
    data += c;
    if(c == '\n') {
      debug(data);
      handleData(data);
      data = "";
    }
      
  }
}

void handleData(String data) {
  if(data.indexOf("+CLIP") != -1) {
    hangUp();
    debug("Phone's coming: ");
    byte startIndex = 8;
    byte endIndex   = data.indexOf("\"", 10);
    String phoneNum = data.substring(startIndex, endIndex);
    debug(phoneNum);
    if(phoneNum == phoneNumber) {
      activatedRelay = !activatedRelay;
      if(activatedRelay) {
        activeRelay();
        sendSMS(phoneNumber, "Da kich hoat may bom");
      } else {
        deactiveRelay();
        sendSMS(phoneNumber, "Da tat may bom");
      }
    }
  } else if(data.indexOf("+CUSD") != -1) {
    byte startIndex = data.indexOf("\"");
    byte endIndex   = data.indexOf("\"", startIndex+1);
    String ussdRespone = data.substring(startIndex+1, endIndex-1);
    debug(ussdRespone);
    sendSMS(phoneNumber, ussdRespone);
  } else if(data.indexOf("+CMT") != -1) {
    byte startIndex = data.indexOf("\"");
    byte endIndex = data.indexOf("\"", startIndex+1);
    String phoneNum = data.substring(startIndex+1, endIndex);
    phoneNumber.replace("+84", "0");
    phoneNum.replace("+84", "0");
    if(phoneNum == phoneNumber) {
      debug("ABCXYZ: " + data.indexOf("\n"));
      String smsContent = data.substring(data.indexOf("\n") + 2); 
   
      debug("Phone Number:" + phoneNum);
      debug("SMS Content: " +smsContent);
    }
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
  debug("Hang up");
  Sim.print("ATH\r\n");
  delay(2000);
}

void ussd(String code) {
  Sim.print("AT+CUSD=1,\"" + code + "\"\r\n");
}

