void initButton() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(1, changeState, FALLING);
}

void changeState() {
  Serial.println(activated);
  activated = !activated;
  if(activated)
    digitalWrite(LED_PIN, HIGH);
  else
    digitalWrite(LED_PIN, LOW);
}

