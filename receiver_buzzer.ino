#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define SS          D8
#define RST         D0
#define BUZZER_PIN  D3
#define STATUS_LED  D4  // Single LED pin

LiquidCrystal_I2C lcd(0x27, 16, 2); // LCD address may vary (0x27 or 0x3F)

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

  // Initialize LoRa
  LoRa.setPins(SS, RST, -1); // DIO0 not used
  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa init failed!");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("LoRa Failed");
    while (1);
  }

  // LoRa successfully connected
  Serial.println("LoRa CONNECTED");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("LoRa CONNECTED");

  // 🔔 Beep 3 times to indicate connection
  for (int i = 0; i < 3; i++) {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(200);
    digitalWrite(BUZZER_PIN, LOW);
    delay(200);
  }

  // Show waiting message after beep
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

    message.trim(); // Remove any trailing whitespace
    Serial.println("Received: " + message);

    // Update LCD with received message
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Status:");
    lcd.setCursor(0, 1);
    lcd.print(message);

    // LED control based on message
    if (message == "Track DETECTED") {
      digitalWrite(STATUS_LED, HIGH);  // Turn ON LED
    } else if (message == "Track not detected") {
      digitalWrite(STATUS_LED, LOW);   // Turn OFF LED
    }
  }

  delay(100); // Avoid rapid polling
}
