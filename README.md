# 📡 Arduino-Based Ultrasonic Radar System

This project is an Arduino-based ultrasonic radar system developed using an Arduino Uno, HC-SR04 ultrasonic sensor, and SG90 servo motor.

The ultrasonic sensor is mounted on the servo motor. As the servo rotates, the sensor scans different directions and measures the distance of nearby objects.

## 🧰 Components Used

- Arduino Uno R3
- HC-SR04 Ultrasonic Sensor
- SG90 Servo Motor
- Breadboard
- Jumper Wires
- USB Cable
- Laptop with Arduino IDE

## ⚙️ Working Principle

The servo motor rotates the HC-SR04 ultrasonic sensor from one side to another.

At every angle, the sensor sends an ultrasonic pulse.

When the pulse hits an object, it reflects back to the sensor.

Arduino measures the time taken by the pulse and calculates the distance using:

Distance = (Time × Speed of Sound) / 2

## 🔌 Connections

### HC-SR04

| HC-SR04 | Arduino Uno |
|---|---|
| VCC | 5V |
| GND | GND |
| TRIG | Pin 10 |
| ECHO | Pin 11 |

### SG90 Servo

| Servo | Arduino Uno |
|---|---|
| Red | 5V |
| Brown/Black | GND |
| Orange/Yellow | Pin 9 |

## 🔄 Project Flow

Start  
↓  
Initialize Arduino  
↓  
Rotate Servo  
↓  
Trigger Ultrasonic Sensor  
↓  
Measure Echo Time  
↓  
Calculate Distance  
↓  
Display Angle and Distance  
↓  
Repeat

## 💻 Software Used

- Arduino IDE
- Embedded C/C++
- Serial Monitor

## 🎯 Features

- Real-time distance measurement
- Object detection
- Automatic servo scanning
- Angle-based object detection
- Serial Monitor output
- Low-cost embedded system

## 📚 What I Learned

Through this project, I learned:

- Arduino programming
- Sensor interfacing
- Servo motor control
- HC-SR04 working
- Distance measurement
- Serial communication
- Embedded systems
- Hardware debugging

## 🚀 Applications

- Robot obstacle detection
- Parking assistance
- Security monitoring
- Object detection
- Autonomous robots

## 🔮 Future Improvements

- Radar-style graphical interface
- LCD display
- Buzzer alert
- RGB LED distance indication
- ESP8266/ESP32 web dashboard
- IoT monitoring

## 📌 Note

The hardware prototype was previously implemented successfully. This repository documents the project source code, architecture, circuit connections, and implementation details.

## 👩‍💻 Developed By

Hrutuja Mane  
Electronics & Telecommunication Engineering
