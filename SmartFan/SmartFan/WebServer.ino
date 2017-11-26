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
  Serial.println("\nHTTP Server Started");
}



void handleNotFound(){
    String msg = "<h1> Your Content Is'nt Exist </h1>";
//  String message = "File Not Found\n\n";
//  message += "URI: ";
//  message += server.uri();
//  message += "\nMethod: ";
//  message += (server.method() == HTTP_GET)?"GET":"POST";
//  message += "\nArguments: ";
//  message += server.args();
//  message += "\n";
//  for (uint8_t i=0; i<server.args(); i++)
//    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  server.send(404, "text/html", msg);
}


void handleActive() {
  relayState = !relayState;
  digitalWrite(RELAY_PIN, relayState ? HIGH : LOW); 
  Serial.println(relayState ? "ON" : "OFF");
  String respone = relayState ? "On" : "Off";
  server.send(200, "text/html", respone);
}

void handleOn() {
  digitalWrite(RELAY_PIN, HIGH); 
  Serial.println("On");
  server.send(200, "text/html", "On");
}

void handleOff() {
  digitalWrite(RELAY_PIN, LOW); 
  Serial.println("Off");
  server.send(200, "text/html", "Off");
}

