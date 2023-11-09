#include <Arduino.h>

const int trig_pin = 9;
const int echo_pin = 10;
const int led_low = 11;
const int led_high = 12;
const int ldr_pin = A0;
long duration;
int distance;

void setup() {
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  pinMode(ldr_pin, INPUT);
  pinMode(led_low, OUTPUT);
  pinMode(led_high, OUTPUT);
  Serial.begin(9600);

  digitalWrite(led_low, LOW);
  digitalWrite(led_high, LOW);
}

void loop() {
  // trigger ultrasonic sensor
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(10);
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);

  duration = pulseIn(echo_pin, HIGH);
  distance = duration * 0.034 / 2;

  int lightIntensity = analogRead(ldr_pin);

  Serial.print("Light Intensity: ");
  Serial.println(lightIntensity);
  Serial.print("Distance: ");
  Serial.println(distance);
//  delay(800);

  if (lightIntensity <= 75) {
    digitalWrite(led_low, HIGH);
    if (distance <= 25) {
      digitalWrite(led_low, LOW);
      digitalWrite(led_high, HIGH);
      delay(10);
    }
    else if (distance > 25) {
      digitalWrite(led_low, HIGH);
      digitalWrite(led_high, LOW);
      delay(10);
    }
    delay(200);
  } else if (lightIntensity > 75) {
    digitalWrite(led_low, LOW);
    delay(10);
  }
}
