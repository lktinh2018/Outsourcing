void initWebServer() {
  //Connect to access point
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED)
    delay(500);
  WiFi.config(ip, gateway,subnet);
  //Set URL 
  server.on("/", handleRoot);
  server.on("/login", handleLogin);
  server.on("/user", changePassword);
  server.on("/upload", HTTP_POST, [&](){
//      server.sendHeader("Connection", "close");
//      server.sendHeader("Access-Control-Allow-Origin", "*");
      server.send(200, "text/html", (Update.hasError())?"FAIL":"OK");
      //"<META http-equiv=\"refresh\" content=\"15;URL=/login\">OK"
    },[&](){
      // handler for the file upload, get's the sketch bytes, and writes
      // them through the Update object
      HTTPUpload& upload = server.upload();
       if(upload.status == UPLOAD_FILE_START) {
          //Delete file if exist
          if(SD.exists((char*)upload.filename.c_str()))
            SD.remove((char*)upload.filename.c_str());
          myFile = SD.open((char*)upload.filename.c_str(),  O_WRITE | O_CREAT | O_TRUNC);
          Serial.print("File type: ");
          Serial.println(upload.type.c_str());
       } else if(upload.status == UPLOAD_FILE_END){
          myFile.close();
          Serial.println("Save File End");
       } else if(upload.status == UPLOAD_FILE_WRITE) {
          saveFileToSD(upload.filename.c_str(), upload.buf, upload.currentSize);
       }
    });

  
  server.onNotFound(handleNotFound);
  //Here is the list of headers to be recorded
  const char* headerkeys[] = {"User-Agent", "Cookie"};
  size_t headerkeyssize = sizeof(headerkeys)/sizeof(char*);
  //Ask server to track these headers
  server.collectHeaders(headerkeys, headerkeyssize);
  server.begin();
  Serial.println("\nHTTP Server Started");
}

void loopWebServer() {
  server.handleClient();
}

void handleRoot(){
  String header;
  if (!is_authentified()){
    String header = "HTTP/1.1 301 OK\r\nLocation: /login\r\nCache-Control: no-cache\r\n\r\n";
    server.sendContent(header);
    return;
  }
  String content = dashboard_page;
  server.send(200, "text/html", content);
}

void handleLogin(){
  String msg;
  if (server.hasHeader("Cookie")){   
    String cookie = server.header("Cookie");
  }
  if (server.hasArg("DISCONNECT")){
    String header = "HTTP/1.1 301 OK\r\nSet-Cookie: ESPSESSIONID=0\r\nLocation: /\r\nCache-Control: no-cache\r\n\r\n";
    server.sendContent(header);
    return;
  }
  if (server.hasArg("USERNAME") && server.hasArg("PASSWORD")){
    if(server.arg("USERNAME") == username_auth &&  server.arg("PASSWORD") == password_auth ){
      String header = "HTTP/1.1 301 OK\r\nSet-Cookie: ESPSESSIONID=1\r\nLocation: /\r\nCache-Control: no-cache\r\n\r\n";
      server.sendContent(header);
      return;
    }
  }
  String content = login_page;
  server.send(200, "text/html", content);
}

bool is_authentified(){
  if (server.hasHeader("Cookie")){   
    String cookie = server.header("Cookie");
    if (cookie.indexOf("ESPSESSIONID=1") != -1) {
      return true;
    }
  }
  return false;  
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

void changePassword() {
  if (server.hasArg("PASSWORD")){
    password_auth = server.arg("PASSWORD");
    server.send(200, "text/html", (Update.hasError())?"FAIL":"<META http-equiv='refresh' content='15;URL=/login?DISCONNECT=YES'>Your password's changed");
  } else {                                                  
    server.send(200, "text/html", "Error");
  }
}

