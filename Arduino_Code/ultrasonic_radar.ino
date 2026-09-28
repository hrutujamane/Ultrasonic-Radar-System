#include <Servo.h>

Servo radarServo;

const int trigPin = 10;
const int echoPin = 11;
const int servoPin = 9;

long duration;
int distance;

int calculateDistance() {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH, 30000);

  if (duration == 0) {
    return 0;
  }

  distance = duration * 0.0343 / 2;

  return distance;
}

void setup() {

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  radarServo.attach(servoPin);

  Serial.begin(9600);
}

void loop() {

  for (int angle = 15; angle <= 165; angle += 2) {

    radarServo.write(angle);
    delay(30);

    distance = calculateDistance();

    Serial.print("Angle: ");
    Serial.print(angle);
    Serial.print(" | Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
  }

  for (int angle = 165; angle >= 15; angle -= 2) {

    radarServo.write(angle);
    delay(30);

    distance = calculateDistance();

    Serial.print("Angle: ");
    Serial.print(angle);
    Serial.print(" | Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
  }
}
