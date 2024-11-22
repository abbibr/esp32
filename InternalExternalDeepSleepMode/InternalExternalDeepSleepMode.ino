RTC_DATA_ATTR int count = 0;
#define SECONDS 3
unsigned long microSeconds = 1000000;

int bluePin = 2;
int redPin = 32;
int yellowPin = 33;
int externalButton = 4;

void setup() {
  Serial.begin(115200);

  // Pin configurations
  pinMode(bluePin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(externalButton, INPUT_PULLUP);

  // Increment count for each wake-up cycle
  count++;
  Serial.println("Count: " + String(count));

  // Determine the wake-up source
  esp_sleep_wakeup_cause_t wakeupCause = esp_sleep_get_wakeup_cause();

  if (wakeupCause == ESP_SLEEP_WAKEUP_EXT0) {
    // Wake-up caused by the external button
    digitalWrite(redPin, HIGH); // Light up red LED
    Serial.println("Woke up via External Button!");
    delay(1000);
    digitalWrite(redPin, LOW);
  } 
  else if (wakeupCause == ESP_SLEEP_WAKEUP_TIMER) {
    // Wake-up caused by timer
    Serial.println("Woke up via Timer!");
    if (count % 2 == 0) {
      digitalWrite(bluePin, HIGH); // Light up blue LED
    } 
    else {
      digitalWrite(yellowPin, HIGH); // Light up yellow LED
    }
    delay(1000);
    digitalWrite(bluePin, LOW);
    digitalWrite(yellowPin, LOW);
  } 
  else {
    // First boot or unknown cause
    Serial.println("First boot or unknown wake-up cause.");
  }

  // Configure timer-based wake-up
  esp_sleep_enable_timer_wakeup(SECONDS * microSeconds);

  // Configure external GPIO wake-up (active LOW)
  esp_sleep_enable_ext0_wakeup((gpio_num_t)externalButton, LOW);

  Serial.println("Entering Deep Sleep Mode...");
  delay(100); // Short delay for stability

  // Enter deep sleep
  esp_deep_sleep_start();
}

void loop() {
  // No code required in loop
}
