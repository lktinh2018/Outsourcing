void initWiFi() {
//  //Read ssidWiFi from EPPROM
//  for(int i=0; i<=31; i++)
//    ssidWiFi[i] = EEPROM.read(i);
//  
//  //Read ssidPassword from EPPROM
//  for(int i=33; i<=96; i++)
//    passwordWiFi[i] = EEPROM.read(i);
    
  //Connect to access point
  WiFi.begin(ssidWiFi, passwordWiFi);
  byte c = 0;
  Serial.println("Connecting to wifi");
  while(WiFi.status() != WL_CONNECTED) {
    c++;
    delay(500);
    if(c==100) {
      Serial.println("Change to setting mode");
      initAP();
      return;
    }
    Serial.print(".");
  }
  Serial.println();
//  stopAP();
  initWebServer();
  WiFi.config(ip, gateway,subnet);
}

