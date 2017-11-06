void initSDCard() {
  if (!SD.begin(4)) {
    Serial.println("Initialization SD card failed!");
    return;
  }
  Serial.println("Initialization SD card done.");
}

String loadFromSD(String path) {
  String data;
  myFile = SD.open(path);
  if (myFile) {
    while (myFile.available()) {
      data += (char)myFile.read();
    }
    myFile.close();
  }
  return data;
}

void saveFileToSD(String filename, uint8_t data[], int length) {
  //If the file opened okay, write to it
  if (myFile) {
    myFile.write(data, length);
    //Close the file:
  }
}

