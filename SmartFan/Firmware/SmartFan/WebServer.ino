void initWebServer() {
  //Set URL 
  server.on("/active", handleActive);
  server.on("/on", handleOn);
  server.on("/off", handleOff);
  
  server.onNotFound(handleNotFound);
  //Here is the list of headers to be recorded
  const char* headerkeys[] = {"User-Agent", "Cookie"};
  size_t headerkeyssize = sizeof(headerkeys)/sizeof(char*);
  //Ask server to track these headers
  server.collectHeaders(headerkeys, headerkeyssize);
  server.begin();
  debug("HTTP Server Started");
}

void loopWebServer() {
  server.handleClient();
}

void handleActive() {
  stateFan++;
  if(stateFan == 4)
    stateFan = 0;
  
  switch(stateFan) {
    case 0:
      digitalWrite(RELAY_PIN_1, LOW);
      digitalWrite(RELAY_PIN_2, LOW);
      digitalWrite(RELAY_PIN_3, LOW);
      break;

    case 1:
      digitalWrite(RELAY_PIN_1, HIGH);
      digitalWrite(RELAY_PIN_2, LOW);
      digitalWrite(RELAY_PIN_3, LOW);
      break;
      
    case 2:
      digitalWrite(RELAY_PIN_1, LOW);
      digitalWrite(RELAY_PIN_2, HIGH);
      digitalWrite(RELAY_PIN_3, LOW);
      break;
      
    case 3:
      digitalWrite(RELAY_PIN_1, LOW);
      digitalWrite(RELAY_PIN_2, LOW);
      digitalWrite(RELAY_PIN_3, HIGH);
      break;
  }

  String respone = stateFan ? ("On: " + String(stateFan)) : "Off";  
  server.send(200, "text/plain", respone.c_str());
  debug(respone);
}

void handleOn() {
  stateFan = 3;
  digitalWrite(RELAY_PIN_1, LOW);
  digitalWrite(RELAY_PIN_2, LOW);
  digitalWrite(RELAY_PIN_3, HIGH);
  server.send(200, "text/plain", "On: 3");
  debug("On: 3");
}

void handleOff() {
  stateFan = 0;
  digitalWrite(RELAY_PIN_1, LOW);
  digitalWrite(RELAY_PIN_2, LOW);
  digitalWrite(RELAY_PIN_3, LOW);
  server.send(200, "text/plain", "Off");
  debug("Off");
}

void handleNotFound(){
  String msg = "<h1> File Not Found </h1>";
  server.send(404, "text/plain", msg);
}
