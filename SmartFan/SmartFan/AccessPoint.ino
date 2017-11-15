void initAP() {
  Serial.println("Configuring access point...");
  WiFi.softAP(ssidAP, passwordAP);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", handleRoot);
  server.begin();
  Serial.println("AP started");
}

void stopAP() {
  WiFi.softAPdisconnect();
  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  delay(100);
}

void handleRoot() {
  server.send(200, "text/html", "<h1>You are connected</h1>");
}
