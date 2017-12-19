void initFS() {
  debug("Mounting FS...");
  if(SPIFFS.begin()) {
    debug("Mounted file system");
    if(SPIFFS.exists("/config.json")) {
      debug("Reading config file");
      File configFile = SPIFFS.open("/config.json", "r");
      if (configFile) {
        debug("Opened config file");
        size_t size = configFile.size();
        std::unique_ptr<char[]> buf(new char[size]);
        configFile.readBytes(buf.get(), size);
        DynamicJsonBuffer jsonBuffer;
        JsonObject& json = jsonBuffer.parseObject(buf.get());
        json.printTo(Serial);
        if (json.success()) {
          debug("\nParsed json");
          strcpy(defaultIP, json["defaultIP"]);
          strcpy(defaultGateway, json["defaultGateway"]);
          strcpy(defaultSubnet, json["defaultSubnet"]);
          debug("Read Static Config From FS: ");
          debug(defaultIP);
          debug(defaultGateway);
          debug(defaultSubnet);
        }else {
          debug("Failed to load json config");
        }
      }
    }
  } else {
    Serial.println("Failed to mount FS");
  }
}

