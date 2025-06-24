
// Intelligent Gas Leakage Detection and Safety System

#include <SoftwareSerial.h>

int gasSensor = A0;
int fanRelay = 8;
int buzzer = 9;
int threshold = 400;

SoftwareSerial gsm(7, 6); // RX, TX

void setup() {
  pinMode(fanRelay, OUTPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
  gsm.begin(9600);
}

void loop() {
  int gasValue = analogRead(gasSensor);
  Serial.println(gasValue);

  if (gasValue > threshold) {
    digitalWrite(fanRelay, HIGH);
    digitalWrite(buzzer, HIGH);
    sendSMS("Gas Leakage Detected! Take immediate action.");
  } else {
    digitalWrite(fanRelay, LOW);
    digitalWrite(buzzer, LOW);
  }

  delay(1000);
}

void sendSMS(String message) {
  gsm.println("AT+CMGF=1");
  delay(100);
  gsm.println("AT+CMGS="+911234567890""); // Replace with your number
  delay(100);
  gsm.print(message);
  delay(100);
  gsm.write(26);
}
