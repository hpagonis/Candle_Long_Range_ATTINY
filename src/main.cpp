#include <Arduino.h>
#include <SPI.h>
#include <LoRa.h>

#define LED_PIN 3
#define CS_PIN 4
#define RESET_PIN -1
#define DIO0_PIN -1
#define CANDLE_ID 3

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN,LOW);
  LoRa.setPins(CS_PIN, RESET_PIN, DIO0_PIN);
  LoRa.setSpreadingFactor(12);
  LoRa.setCodingRate4(8);
  LoRa.setSignalBandwidth(7.8E3);
  LoRa.setGain(6);
  LoRa.setSyncWord(0xBA);
  if (!LoRa.begin(433E6)) {
    while (1) {
      digitalWrite(LED_PIN, HIGH);
      delay(500);
      digitalWrite(LED_PIN, LOW);
      delay(500);
    }
  }
  digitalWrite(LED_PIN, HIGH);
  delay(1000);
  digitalWrite(LED_PIN, LOW);
}

void loop() {
  
  if (LoRa.parsePacket()) {
    // char cid = LoRa.read();
    // if (cid != CANDLE_ID) {
    //   return;
    // }
    // switch (cmd) {
    //   case 'I':
    //     digitalWrite(LED_PIN, HIGH);
    //     break;
    //   case 'O':
    //     digitalWrite(LED_PIN, LOW);
    //     break;
    // }
    byte cmd = ((byte) LoRa.read() & (1 << CANDLE_ID));
    digitalWrite(LED_PIN, cmd ? HIGH : LOW);
  }
}