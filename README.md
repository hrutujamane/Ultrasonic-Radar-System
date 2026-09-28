# 📚 Project Documentation

This folder contains the technical documentation for the Ultrasonic Radar System.

## Included

- `CONNECTIONS.md` — wiring notes
- `block_diagram.png` — system architecture
- `system_flowchart.png` — operating flow

## System Summary

The HC-SR04 measures object distance. The SG90 servo changes the sensing direction. The Arduino controls both devices and sends angle/distance data to a computer over USB serial. A browser dashboard can visualize the scan.

The ESP8266 prototype explores a Wi-Fi-based variation separately.
