String dataSerial;
void setup() {
  Serial1.begin(115200);
  Serial.begin(9600);
}

void loop() {
  while(Serial1.available() > 0) {
    char c = Serial1.read();
    if(c == '\n') {
      Serial.println("Received");
      dataSerial = "";
      break;
    }
    dataSerial += c;
  }
}
