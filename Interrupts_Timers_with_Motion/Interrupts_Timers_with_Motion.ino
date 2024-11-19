#define intervalSeconds 3   

const int ledPin = 26;
int motionSensor = 2;

unsigned long lastTrigger = 0;  // will store last time LED was updated
unsigned long now = millis();
boolean startTimer = false;
int motion = LOW;

void detectsMovement() {
  digitalWrite(ledPin, HIGH);
  startTimer = true;
  lastTrigger = millis();
}

void setup() {
  Serial.begin(115200);

  pinMode(motionSensor, INPUT);
  attachInterrupt(digitalPinToInterrupt(motionSensor), detectsMovement, RISING);

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
}

void loop() {
  now = millis();

  if(digitalRead(ledPin) && (motion == false)) {
    Serial.println("Motion detected");
    Serial.println(digitalRead(ledPin));
    motion = true;
  }

  if(startTimer && (now - lastTrigger > (intervalSeconds * 1000))) {
    Serial.println("Motion stopped");
    digitalWrite(ledPin, LOW);
    startTimer = false;
    motion = false;
  }
}
