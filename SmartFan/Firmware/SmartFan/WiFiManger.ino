void initWiFiManager() {
  WiFiManagerParameter customText("<hr><h3>Config Static IP</h3>");
  WiFiManagerParameter customIP("ip", "IP", defaultIP, 16);
  WiFiManagerParameter customGateway("gateway", "Gateway", defaultGateway, 16);
  WiFiManagerParameter customSubnet("subnet", "Subnet",  defaultSubnet, 16);

  WiFiManager wifiManager;
  wifiManager.setSaveConfigCallback(saveConfigCallback);
  
  wifiManager.addParameter(&customIP);
  wifiManager.addParameter(&customGateway);
  wifiManager.addParameter(&customSubnet);
  //wifiManager.resetSettings();
  if(!wifiManager.autoConnect(ssidAP, passwordAP)) {
    debug("Failed to connect");
    delay(3000);
    ESP.restart();
    delay(3000);
  }
  strcpy(defaultIP, customIP.getValue());
  strcpy(defaultGateway, customGateway.getValue());
  strcpy(defaultSubnet, customSubnet.getValue());

  if(shouldSaveConfig) {
    Serial.println("Saving config");
    DynamicJsonBuffer jsonBuffer;
    JsonObject& json = jsonBuffer.createObject();
    json["defaultIP"]      = defaultIP;
    json["defaultGateway"] = defaultGateway;
    json["defaultSubnet"]  = defaultSubnet;
  
    File configFile = SPIFFS.open("/config.json", "w");
    if (!configFile) {
      debug("Failed to open config file for writing");
    }
    
    json.prettyPrintTo(Serial);
    json.printTo(configFile);
    configFile.close();
  }
}

void saveConfigCallback () {
  debug("Should save config");
  shouldSaveConfig = true;
}
