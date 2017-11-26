void initAP() {
  Serial.println("Configuring access point...");
  WiFi.softAP(ssidAP, passwordAP);
//  IPAddress ipAP(192, 168, 1, 1);
//  IPAddress subnetAP (255, 255, 255, 0);  
//  WiFi.softAPConfig(ipAP, ipAP, subnet);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  server.on("/", [] () {
    IPAddress ip = WiFi.softAPIP();
    String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);
    content = "<!DOCTYPE HTML>\r\n<html>";
    content += "<div align=center> <h2>Setting</h2>";
    content += "<form method=\"get\" action=\"setting\">";
    content += "<div>SSID</div>";
    content += "<div><input name=\"ssid\" size=\"40\"></div>";
    content += "<div>Password</div>";
    content += "<div><input name=\"pass\" size=\"40\"></div> <br>";
    content += "<div><button type='submit'> Save Information </div>";
    content += "<p>";
    content += st;
    content += "</p>";
    content += "<form method=\"get\" action=\"cleareeprom\"> <button type='submit'> Clear EEPROM </div>";
    content += "</div>";
    content += "</html>";
    server.send(200, "text/html", content);
  });
    
  server.on("/cleareeprom", []() {
    content = "<!DOCTYPE HTML>\r\n<html>";
    content += "<h2>XSwitch</h2><p>Clearing the EEPROM</p></html>";
    server.send(200, "text/html", content);
    Serial.println("Clearing EEPROM");
    EEPROM.begin(512);
    for (int i = 0; i < 128; ++i)
       EEPROM.write(i, 0);
    EEPROM.commit();
    EEPROM.end();
    Serial.println("EEPROM Cleared");
  });
  
  server.on("/setting", []() {
      String qsid = server.arg("ssid");
      String qpass = server.arg("pass");
      if (qsid.length() > 0 && qpass.length() > 0) {
        EEPROM.begin(512);
        Serial.println("clearing eeprom");
        for (int i = 0; i < 128; ++i)
          EEPROM.write(i, 0);
        EEPROM.commit();
        Serial.println(qsid);
        Serial.println("");
        Serial.println(qpass);
        Serial.println("");
        Serial.println("writing eeprom ssid:");
        for (int i = 0; i < qsid.length(); ++i) {
           EEPROM.write(i, qsid[i]);
           Serial.print("Wrote: ");
           Serial.println(qsid[i]);
        }
        Serial.println("writing eeprom pass:");
        for (int i = 0; i < qpass.length(); ++i) {
           EEPROM.write(32 + i, qpass[i]);
           Serial.print("Wrote: ");
           Serial.println(qpass[i]);
        }
        EEPROM.commit();
        EEPROM.end();
        content = "{\"Success\":\"Configuring \"}";
        statusCode = 200;
      } else {
        content = "{\"Error\":\"404 not found\"}";
        statusCode = 404;
        Serial.println("Sending 404");
      }
      server.send(statusCode, "application/json", content);
      ESP.restart();
  });
//  server.begin();
  Serial.println("AP started");
}

void stopAP() {
  WiFi.softAPdisconnect();
  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  delay(100);
}

