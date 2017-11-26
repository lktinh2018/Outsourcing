void initWiFi() {
  //Read SSID From EPPROM
  Serial.println("Reading SSID");
  String essid;
  for( int i=0; i<32; i++) 
    essid += char(EEPROM.read(i));
  Serial.print("SSID: ");
  Serial.println(essid.c_str());
  essid.trim();

  //Read Password From EPPROM
  Serial.println("Reading Password");
  String epass ="";
  for(int i=32; i<96; i++) 
    epass += char(EEPROM.read(i));
  Serial.print("Password: ");
  Serial.println(epass.c_str());
  epass.trim();
  EEPROM.end();

  //Connect to wifi
  WiFi.mode(WIFI_AP_STA);
  WiFi.begin(essid.c_str(), epass.c_str());
  byte c = 0;
  Serial.println("Connecting to wifi");
  while(WiFi.status() != WL_CONNECTED) {
    c++;
    delay(500);
    Serial.print(".");
    if(c==10) {
      Serial.println("\nChange to setting mode");
      initAP();
      return;
    }
  }

  initAP();
  initWebServer();
  WiFi.config(ip, gateway,subnet);
}

