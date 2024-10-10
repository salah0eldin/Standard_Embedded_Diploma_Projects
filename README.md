# Standard Embedded Diploma Projects

Welcome to the Standard Embedded Diploma Projects repository! This repository contains all the projects I worked on during the Standard Embedded Diploma program under the guidance of Eng. Mohammed Tarek.

## Tree
.
|-- MCAL
|   |-- ADC
|   |   |-- adc.c
|   |   `-- adc.h
|   |-- GPIO
|   |   |-- gpio.c
|   |   |-- gpio.h
|   |   `-- gpio_registers.h
|   |-- Timers
|   |   |-- timer0.c
|   |   |-- timer0.h
|   |   |-- timer1.c
|   |   |-- timer1.h
|   |   |-- timer2.c
|   |   `-- timer2.h
|   `-- USART
|       |-- usart.c
|       `-- usart.h
|-- ECU
|   |-- Buzzer
|   |   |-- buzzer.c
|   |   `-- buzzer.h
|   |-- DCMotor
|   |   |-- dcmotor.c
|   |   `-- dcmotor.h
|   |-- FlameSensor
|   |   |-- flame.c
|   |   `-- flame.h
|   |-- Keypad
|   |   |-- keypad.c
|   |   `-- keypad.h
|   |-- LCD
|   |   |-- lcd.c
|   |   `-- lcd.h
|   |-- LDR
|   |   |-- ldr.c
|   |   `-- ldr.h
|   |-- LED
|   |   |-- led.c
|   |   `-- led.h
|   |-- LM35
|   |   |-- lm35.c
|   |   `-- lm35.h
|   |-- SevenSegment
|   |   |-- sevenseg.c
|   |   |-- sevenseg.h
|   |   `-- sevenseg_cfg.h
|   `-- UltraSonicICU
|       |-- ultra_icu.c
|       `-- ultra_icu.h
|-- common_macros.h
|-- main.c
`-- std_types.h

## Table of Contents
- Projects
- stdDrivers

## Projects
Here you will find a collection of projects developed during the Standard Embedded Diploma. Each project is designed to enhance your understanding of embedded systems and improve your practical skills.

### C Project: Student Management System
- **Description**: A console-based application to manage student records using C programming.
- **Features**: Add, delete, and update student records, search for students by ID, display all student records.

### Interfacing Project: Stopwatch using AVR ATmega32
- **Description**: A stopwatch implemented using the AVR ATmega32 microcontroller and simulated with Proteus.
- **Features**: Start, stop, and reset functionality, display time on a 7-segment display.

### Interfacing Project: Smart Home System
- **Description**: A smart home system implemented using AVR ATmega32 microcontroller.
- **Features**: Control lights, fans, and display system status on an LCD.

### Test ADC Negative
- **Description**: A project to test the ADC functionality with negative values.
- **Features**: Read and display ADC values, handle negative inputs.

## stdDrivers
!stdDrivers

The `stdDrivers` folder contains standard drivers used across various projects. These drivers are essential for interfacing with different hardware components and ensuring smooth operation of the embedded systems. The drivers include:

### MCAL (Microcontroller Abstraction Layer)
- **ADC**: For analog-to-digital conversion.
- **GPIO**: For general-purpose input/output operations.
- **Timers**: For handling timer operations.

### ECU (Electronic Control Unit) Layer
- **Buzzer**: Module for controlling a buzzer.
- **DCMotor**: Module for controlling a DC motor.
- **FlameSensor**: Module for interfacing with a flame sensor.
- **Keypad**: Module for interfacing with a keypad.
- **LCD**: Module for interfacing with an LCD display.
- **LDR**: Module for interfacing with a light-dependent resistor.
- **LED**: Module for controlling LEDs.
- **LM35**: Module for interfacing with an LM35 temperature sensor.
- **SevenSegment**: Module for controlling a seven-segment display.

## Getting Started
To get a local copy up and running, follow these simple steps.

### Prerequisites
- Eclipse or any prefered editor
- Proteus

Feel free to explore the projects and use the drivers in your own embedded systems projects. If you have any questions or need further assistance, don't hesitate to reach out.

