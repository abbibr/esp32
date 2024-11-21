String stringSeconds;
int SECONDS;
unsigned long microSeconds = 1000000;

RTC_DATA_ATTR int count = 0;
int bluePin = 2;
int redPin = 4;

void setup() {
  Serial.begin(115200);
  Serial.println("Enter the second which you want to sleep mode of esp32: ");

  pinMode(bluePin, OUTPUT);
  pinMode(redPin, OUTPUT);

  while (!Serial.available()) {
    delay(100);
  }

  stringSeconds = Serial.readString();
  stringSeconds.trim();
  SECONDS = stringSeconds.toInt();

  if(SECONDS <= 0) {
    Serial.println("Please enter the integer seconds!");
    return;
  }
  
  Serial.println("You entered " + String(SECONDS) + " seconds");
  count++;
    
  if(count == 1 || count == 2){
    digitalWrite(bluePin, HIGH);
    Serial.println("Blue pin is lighting on!");
  }
  else{
    digitalWrite(redPin, HIGH);
    Serial.println("Red pin is lighting on...");
  }

  Serial.println("Count is: " + String(count));
  delay(2000);
  digitalWrite(bluePin, LOW);
  digitalWrite(redPin, LOW);

  esp_sleep_enable_timer_wakeup(SECONDS * microSeconds);
  esp_deep_sleep_start();
}

void loop() {
  //
}
