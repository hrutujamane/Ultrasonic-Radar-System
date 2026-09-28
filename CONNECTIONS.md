# 🔌 Connection Guide

## Arduino Uno Version

| Device | Pin |
|---|---|
| SG90 signal | D6 |
| SG90 VCC | 5V |
| SG90 GND | GND |
| HC-SR04 TRIG | D9 |
| HC-SR04 ECHO | D10 |
| HC-SR04 VCC | 5V |
| HC-SR04 GND | GND |

> These are the defaults used by the reconstructed repository code. If your original build used different pins, change the pin constants in the sketch.

## Servo Power Note

A small SG90 may sometimes run from the Arduino 5V pin during light testing, but servo startup/stall current can cause resets. For a more reliable build, use a suitable external 5V supply and **connect the grounds together**.

## ESP8266 Safety Note

Do not feed the HC-SR04 5V ECHO signal directly into an ESP8266 GPIO. Use a voltage divider or level shifter.
