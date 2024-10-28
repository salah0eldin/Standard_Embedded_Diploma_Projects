
# Standard Embedded Diploma Projects
![Version](https://img.shields.io/badge/Version-1-brightgreen)
![Author](https://img.shields.io/badge/Authors-Salah%20Eldin-blue)
![Date](https://img.shields.io/badge/Date-28%20OCT%202024-orange)    

## Overview
Welcome to the Standard Embedded Diploma Projects repository! This repository contains all the projects I worked on during the Standard Embedded Diploma program under the guidance of Eng. Mohammed Tarek.

## Table of Contents

- [Projects](#Projects)
- [High Lights](#High-Lights)
  - [Final Project](#Final-Project)
  - [Standard Drivers](#stdDrivers)
 - [Author](#author)

## Projects
Here you will find a collection of projects developed during the Standard Embedded Diploma. Each project is designed to enhance your understanding of embedded systems and improve your practical skills.

### Final Project : Dual Microcontroller-Based Door Locker Security System Using Password Authentication Usiing FreeRTOS
- **Description**: A secure door locking system that employs two microcontrollers for enhanced security, utilizing FreeRTOS for task management and efficient operation.
- **Features**: Password authentication, dual microcontroller communication, real-time monitoring, and alert notifications for unauthorized access attempts.

### C Project: Student Management System
- **Description**: A console-based application to manage student records using C programming.
- **Features**: Add, delete, and update student records, search for students by ID, display all student records.

### Interfacing Project: Stopwatch using AVR ATmega32
- **Description**: A stopwatch implemented using the AVR ATmega32 microcontroller and simulated with Proteus.
- **Features**: Start, stop, and reset functionality, display time on a 7-segment display.

### Interfacing Project: Smart Home System
- **Description**: A smart home system implemented using AVR ATmega32 microcontroller.
- **Features**: Control lights, fans, and display system status on an LCD.

### Interfacing Project: Car Parking System
- **Description**: A distance-measuring system that alerts the driver when the vehicle is close to obstacles to prevent collisions.
- **Features**: Ultrasonic distance measurement, real-time proximity alerts, and visual or auditory alarm for nearby obstacles.

### Test ADC Negative
- **Description**: A project to test the ADC functionality with negative values.
- **Features**: Read and display ADC values, handle negative inputs.

## High-Lights

### Final-Project

This project is a FreeRTOS-based application developed for a human-machine interface (HMI) control system. It integrates various components such as a keypad, LCD, buzzer, DC motor, and PIR sensor to create an interactive and responsive control environment. The architecture follows a modular design, allowing for easy scalability and maintenance.

#### HMIEcu
- **APP**: Contains application-specific code for the human-machine interface.
  - **ControlInterface**: Manages the interaction between the control system and the user.
  - **HumanInterface**: Handles user interface operations and interactions.
- **ECU**: Contains components for input and output.
  - **Keypad**: Code for handling keypad input.
  - **LCD**: Code for displaying information on an LCD.
- **FreeRTOS**: Contains the FreeRTOS kernel files.
- **LIB**: Utility files providing common macros and type definitions.
- **MCAL**: Microcontroller Abstraction Layer containing hardware interaction code.

#### controlEcu
- **APP**: Application-specific code for the control ECU.
  - **Door**: Controls the door mechanism.
  - **HMIECUInterface**: Interface code between HMI and control ECU.
- **ECU**: Contains components for other actuators and sensors.
  - **Buzzer**: Code for buzzer operations.
  - **DCMotor**: Code for controlling DC motors.
  - **I2C_EEPROM**: Code for handling EEPROM through I2C communication.
  - **PIR**: Code for handling passive infrared sensor input.
- **FreeRTOS**: Contains the FreeRTOS kernel files.
- **LIB**: Utility files for common macros and type definitions.
- **MCAL**: Contains hardware interaction code.

#### shared
- **shared.h**: Common definitions shared between the ECUs.


### stdDrivers

The `stdDrivers` folder `PATH:interfacing2/Eclipse` contains standard drivers used across various projects. These drivers are essential for interfacing with different hardware components and ensuring smooth operation of the embedded systems. The drivers include:

#### MCAL (Microcontroller Abstraction Layer)
- **ADC**: For analog-to-digital conversion.
- **EEPROM**: For non-volatile data storage and retrieval.
- **ExternalInterrupts**: For responding to external events and triggering actions.
- **GPIO**: For general-purpose input/output operations.
- **I2C**: For inter-integrated circuit communication, allowing multiple devices to communicate.
- **SPI**: For serial peripheral interface communication, enabling high-speed data transfer.
- **USART**: For universal synchronous/asynchronous receiver-transmitter communication, facilitating serial communication.
- **Timers**: For handling timer operations, including delay generation and event scheduling.

#### ECU (Electronic Control Unit) Layer
- **Button**: Module for detecting button presses and user input.
- **Buzzer**: Module for controlling a buzzer.
- **DCMotor**: Module for controlling a DC motor.
- **FlameSensor**: Module for interfacing with a flame sensor.
- **I2C_EEPROM**: Module for interfacing with an I2C-based EEPROM for data storage.
- **Keypad**: Module for interfacing with a keypad.
- **LCD**: Module for interfacing with an LCD display.
- **LDR**: Module for interfacing with a light-dependent resistor.
- **LED**: Module for controlling LEDs.
- **LM35**: Module for interfacing with an LM35 temperature sensor.
- **PIR**: Module for detecting motion using a passive infrared sensor.
- **SevenSegment**: Module for controlling a seven-segment display.
- **TimeCounter**: Module for keeping track of elapsed time or counting events.
- **UltraSonicICU**: Module for measuring distance using ultrasonic sensors.

## Getting Started
To get a local copy up and running, follow these simple steps.

### Prerequisites
- Eclipse 
- Proteus

Feel free to explore the projects and use the drivers in your own embedded systems projects. If you have any questions or need further assistance, don't hesitate to reach out.

## Author

- [Salah Eldin](https://github.com/salah0eldin)

