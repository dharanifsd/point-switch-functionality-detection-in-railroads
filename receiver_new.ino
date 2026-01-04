#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define SS          D8
#define RST         D0
#define BUZZER_PIN  D3
#define STATUS_LED  D4

LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C LCD address

unsigned long lastReceiveTime = 0;
const unsigned long SIGNAL_TIMEOUT = 5000; // 5 seconds timeout

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();

  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(STATUS_LED, OUTPUT);

  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(STATUS_LED, LOW);

  lcd.setCursor(0, 0);
  lcd.print("Connecting LoRa");

  // Try to initialize LoRa
  LoRa.setPins(SS, RST, -1);
  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa init failed!");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("LoRa Init Failed");
    while (1);
  }

  // Wait for signal initially
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Waiting  for signal...");

  bool messageReceived = false;
  unsigned long startTime = millis();

  while (millis() - startTime < SIGNAL_TIMEOUT) {
    int packetSize = LoRa.parsePacket();
    if (packetSize > 0) {
      String msg = "";
      while (LoRa.available()) {
        msg += (char)LoRa.read();
      }
      msg.trim();
      Serial.println("First Message: " + msg);
      messageReceived = true;
      lastReceiveTime = millis();
      break;
    }
  }

  if (messageReceived) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("CONNECTION");
    lcd.setCursor(0, 1);
    lcd.print("ESTABLISHED");
    Serial.println("LoRa CONNECTED");

    // Beep 3 times
    for (int i = 0; i < 3; i++) {
      digitalWrite(BUZZER_PIN, HIGH);
      delay(200);
      digitalWrite(BUZZER_PIN, LOW);
      delay(200);
    }
    delay(500);
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Waiting for msg");
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize > 0) {
    String message = "";
    while (LoRa.available()) {
      message += (char)LoRa.read();
    }

    message.trim();
    Serial.println("Received: " + message);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Status:");
    lcd.setCursor(0, 1);
    lcd.print(message);

    // LED control
    if (message == "Track DETECTED") {
      digitalWrite(STATUS_LED, HIGH);
    } else if (message == "Track not detected") {
      digitalWrite(STATUS_LED, LOW);
    }

    lastReceiveTime = millis(); // update time of last received message
  }

  // If no message received for 5 seconds, show "Waiting for signal"
  if (millis() - lastReceiveTime > SIGNAL_TIMEOUT) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Waiting signal...");
    digitalWrite(STATUS_LED, LOW); // Turn off LED if no signal
  }

  delay(100);
}
