
# Arduino Smart Parking Assistant

## Project Overview

A distance-based parking assistance system developed using an Arduino UNO and an HC-SR04 ultrasonic sensor.

The system measures the distance to an obstacle and provides visual and audible feedback using three LEDs and a buzzer.

## Features

- Real-time distance measurement using the HC-SR04
- Three LED indicators for different distance ranges
- Adaptive buzzer beeping based on obstacle distance
- Non-blocking buzzer timing using `millis()`
- Distance monitoring through the Serial Monitor

## Hardware Components

- Arduino UNO R3
- HC-SR04 Ultrasonic Sensor
- Red, Yellow and Green LEDs
- Three 220-ohm resistors
- Buzzer
- Breadboard and jumper wires

## Pin Configuration

| Component | Arduino Pin |
|-----------|-------------|
| Ultrasonic TRIG | D12 |
| Ultrasonic ECHO | D11 |
| Red LED | D7 |
| Yellow LED | D6 |
| Green LED | D5 |
| Buzzer | D8 |

## System Behavior

| Distance | LED | Buzzer |
|----------|-----|--------|
| Above 50 cm | Green | OFF |
| 20-50 cm | Yellow | Slow beeping |
| Below 20 cm | Red | Fast beeping |

## How It Works

The ultrasonic sensor sends sound waves and measures the time required for the echoes to return.

The Arduino calculates the distance and activates the corresponding LED.

The buzzer beeps faster as an obstacle approaches.

The system uses `millis()` for non-blocking timing.

## Software

- Arduino IDE
- Arduino C/C++

## Project Background

Developed as an extension of Lesson 10 from the ELEGOO UNO Starter Kit tutorial.

Additional features include multiple LED indicators and adaptive buzzer control.

