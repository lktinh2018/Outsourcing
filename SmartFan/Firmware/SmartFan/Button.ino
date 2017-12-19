void initButton() {
  attachInterrupt(BUTTON_PIN, handleButton, FALLING);
}

void handleButton() {
  int buttonState = digitalRead(BUTTON_PIN);
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if(buttonState == LOW) {
      stateFan++;
      if(stateFan == 4)
        stateFan = 0;
      
      switch(stateFan) {
        case 0:
          debug("Off");
          digitalWrite(RELAY_PIN_1, LOW);
          digitalWrite(RELAY_PIN_2, LOW);
          digitalWrite(RELAY_PIN_3, LOW);
          break;
    
        case 1:
          debug("On: 1");
          digitalWrite(RELAY_PIN_1, HIGH);
          digitalWrite(RELAY_PIN_2, LOW);
          digitalWrite(RELAY_PIN_3, LOW);
          break;
          
        case 2:
          debug("On: 2");
          digitalWrite(RELAY_PIN_1, LOW);
          digitalWrite(RELAY_PIN_2, HIGH);
          digitalWrite(RELAY_PIN_3, LOW);
          break;
          
        case 3:
          debug("On: 3");
          digitalWrite(RELAY_PIN_1, LOW);
          digitalWrite(RELAY_PIN_2, LOW);
          digitalWrite(RELAY_PIN_3, HIGH);
          break;
      }
      lastDebounceTime = millis();
    }
  }
}

