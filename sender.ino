#include <SPI.h>
#include <LoRa.h>

#define SS    D8
#define RST   D0
#define SENSOR_PIN D2  // OUT pin of sensor

void setup() {
  Serial.begin(9600);
  pinMode(SENSOR_PIN, INPUT);

  LoRa.setPins(SS, RST, -1); // DIO0 not used

  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa init failed!");
    while (1);
  }

  Serial.println("LoRa Sender Ready");
}

void loop() {
  bool sensorValue = digitalRead(SENSOR_PIN);
  String message;

  // REVERSED: LOW = DETECTED, HIGH = NOT DETECTED
  if (sensorValue == LOW) {
    message = "Track DETECTED";
  } else {
    message = "Track not detected";
  }

  Serial.println("Sending: " + message);
  LoRa.beginPacket();
  LoRa.print(message);
  LoRa.endPacket();

  delay(500); // check sensor and send every 0.5 seconds
}
