int bluePin = 26;

int intervalSeconds = 3000;
int state = LOW;
unsigned long previous = 0;

void setup() {
  Serial.begin(115200);

  pinMode(bluePin, OUTPUT);
}

void loop() {
  unsigned long now = millis();

  if(now - previous >= intervalSeconds) {
    previous = now;

    if(state == LOW) {
      state = HIGH;

      Serial.println("Led is working");
    }
    else {
      state = LOW;

      Serial.println("Led is stopped!");
    }

    digitalWrite(bluePin, state);
  }
}
