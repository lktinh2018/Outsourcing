void initRelay() {
  pinMode(RELAY_PIN, OUTPUT);
}

void activeRelay() {
  digitalWrite(RELAY_PIN, LOW);
  debug("Relay's activated");
}

void deactiveRelay() {
 digitalWrite(RELAY_PIN, HIGH);
 debug("Relay's deactivated");
}

