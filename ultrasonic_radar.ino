#include <Servo.h>

Servo radarServo;

// Default pins used in this documented version.
// Change them if your original wiring was different.
const int SERVO_PIN = 6;
const int TRIG_PIN  = 9;
const int ECHO_PIN  = 10;

const int MIN_ANGLE = 15;
const int MAX_ANGLE = 165;
const int STEP_ANGLE = 2;

long measureDistanceCm() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // 30 ms timeout ≈ 5 m round-trip maximum
  unsigned long duration = pulseIn(ECHO_PIN, HIGH, 30000UL);

  if (duration == 0) {
    return -1; // no echo detected
  }

  long distance = (long)(duration * 0.0343 / 2.0);
  return distance;
}

void sendReading(int angle, long distanceCm) {
  // CSV format for Serial Monitor / dashboard:
  // angle,distance
  Serial.print(angle);
  Serial.print(",");
  Serial.println(distanceCm);
}

void scanFromTo(int startAngle, int endAngle, int stepAngle) {
  if (stepAngle == 0) return;

  for (int angle = startAngle;
       (stepAngle > 0) ? (angle <= endAngle) : (angle >= endAngle);
       angle += stepAngle) {

    radarServo.write(angle);
    delay(35); // allow servo to move

    long distanceCm = measureDistanceCm();
    sendReading(angle, distanceCm);
  }
}

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  radarServo.attach(SERVO_PIN);
  radarServo.write(MIN_ANGLE);

  Serial.begin(9600);
  delay(500);
}

void loop() {
  scanFromTo(MIN_ANGLE, MAX_ANGLE, STEP_ANGLE);
  scanFromTo(MAX_ANGLE, MIN_ANGLE, -STEP_ANGLE);
}
