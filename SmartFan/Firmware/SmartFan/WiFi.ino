void initWiFi() {
  debug("Configuring Static IP");
  IPAddress ip, gateway, subnet;
  ip = stringToIPAddress(defaultIP);
  gateway = stringToIPAddress(defaultGateway);
  subnet = stringToIPAddress(defaultSubnet);
  WiFi.config(ip, gateway, subnet);
  debug("Local IP:");
  debug((WiFi.localIP()).toString());
  debug((WiFi.gatewayIP()).toString());
  debug((WiFi.subnetMask()).toString());
}

IPAddress stringToIPAddress(char* var) {
  String s = String(var);
  int parts[4] = {0,0,0,0};
  int part = 0;
  
  for(int i=0; i<s.length(); i++) {
    char c = s[i];
    if (c == '.') {
      part++;
      continue;
    }
    parts[part] *= 10;
    parts[part] += c - '0';
  }
  IPAddress result(parts[0], parts[1], parts[2], parts[3]);
  return result;
}

