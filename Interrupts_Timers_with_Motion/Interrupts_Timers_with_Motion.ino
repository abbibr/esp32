int bluePin = 26;
int motionSensor = 2;

unsigned long previous = 0;
String intervalSeconds;
int intervalSecondsInteger;
bool startTimer = false;
bool motion = false;

void workingSensor() {
  digitalWrite(bluePin, HIGH);

  startTimer = true;
  previous = millis();
}

void setup() {
  Serial.begin(115200);

  pinMode(motionSensor, INPUT);
  attachInterrupt(digitalPinToInterrupt(motionSensor), workingSensor, RISING);

  pinMode(bluePin, OUTPUT);
  digitalWrite(bluePin, LOW);

  Serial.println("Enter the seconds that you want to turn on the LED when motion is detected...");
}

void loop() {
  unsigned long now = millis();

  if(Serial.available()) {
    intervalSeconds = Serial.readString();
    intervalSeconds.trim();

    Serial.print("You entered ");
    Serial.print(intervalSeconds);
    Serial.println(" seconds");

    intervalSecondsInteger = intervalSeconds.toInt() * 1000;

    if(intervalSecondsInteger <= 0) {
      Serial.println("Invalid input! Please enter a positive number.");
    }
    else {
      Serial.print("LED will stay on for ");
      Serial.print(intervalSecondsInteger / 1000);
      Serial.println(" seconds when motion is deteced.");
    }
  }

  if(motion == false) {
    motion = true;

    Serial.println("Motion is detected.");
  }

  if(startTimer && (now - previous >= intervalSecondsInteger)) {
    startTimer = false;
    motion = false;

    digitalWrite(bluePin, LOW);
    Serial.println("Motion is stopped! ");
  }
}
