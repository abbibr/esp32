#define SECONDS 5
unsigned long microSeconds = 1000000;

// Real Time Clock memory
RTC_DATA_ATTR int count = 0;

void setup() {
  // Do what you want
  Serial.begin(115200);
  count++;

  Serial.println("Count: " + String(count));

  // Wake up mode
  esp_sleep_enable_timer_wakeup(SECONDS * microSeconds);
  
  // Prepare for sleep mode
  Serial.flush();

  // Enable deep sleep mode
  esp_deep_sleep_start();
}

void loop() {
  //
}
