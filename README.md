⚡ IoT-Based Smart Energy Monitoring, Control and Safety System
📖 Project Overview

The IoT-Based Smart Energy Monitoring, Control and Safety System is an intelligent embedded system designed to monitor electrical energy consumption, remotely control electrical appliances, and provide safety features through IoT technology. The project aims to improve energy efficiency, reduce electricity wastage, and enhance user safety by integrating real-time monitoring, cloud connectivity, and AI-based authentication.

The system is built around the ESP32 microcontroller, which collects electrical parameters from voltage and current sensors, calculates energy consumption, and transmits the data to the Blynk IoT Platform. Users can remotely monitor voltage, current, power, energy consumption, and estimated electricity bills using a smartphone.

Apart from energy monitoring, the project also includes relay-based load control, allowing users to switch appliances ON/OFF from anywhere through the internet. Safety features such as fire detection, gas leakage detection, door lock control, and face recognition authentication make the system suitable for modern smart homes and industries.

🎯 Objectives
Monitor electrical parameters in real time.
Measure voltage, current, power, and energy consumption.
Display live electrical data on LCD and mobile application.
Control appliances remotely using IoT.
Improve electrical safety through fire and gas detection.
Provide secure access using face recognition.
Calculate estimated electricity bill automatically.
Reduce unnecessary power consumption.
✨ Features
Energy Monitoring
Real-time Voltage Monitoring
Real-time Current Monitoring
Power Calculation
Energy Consumption Monitoring
Electricity Bill Estimation
Smart Appliance Control
Remote Bulb Control
Remote Socket Control
Remote Motor Control
Manual Switch Control
Relay Based Load Switching
Safety Features
Fire Detection
Gas Leakage Detection
Buzzer Alert System
LED Status Indication
Smart Security
Face Recognition Authentication
Authorized User Verification
Automatic Door Lock Control using Servo Motor
IoT Features
Blynk Mobile Dashboard
Real-time Sensor Monitoring
Internet-Based Device Control
Live Notifications
Data Logging
🛠 Hardware Components
Component	Purpose
ESP32 Dev Board	Main Controller
ACS712 Current Sensor	Current Measurement
ZMPT101B Voltage Sensor	Voltage Measurement
16×2 LCD Display	Local Data Display
Relay Modules	Appliance Control
Servo Motor	Door Lock System
Flame Sensor	Fire Detection
MQ Gas Sensor	Gas Leakage Detection
Active Buzzer	Alarm System
LEDs	Status Indication
Breadboard	Circuit Assembly
Jumper Wires	Connections
Power Supply	System Power
💻 Software Requirements
Arduino IDE
Python
OpenCV
VS Code
Blynk IoT Platform
IFTTT
Node-RED (Optional)
Git
⚙ Technologies Used
Embedded C
Python
ESP32
IoT
OpenCV
Computer Vision
Blynk Cloud
IFTTT Automation
HTTP Communication
Wi-Fi Networking
🧠 Working Principle
Step 1

The ESP32 continuously reads electrical parameters from:

ACS712 Current Sensor
ZMPT101B Voltage Sensor
Step 2

The controller calculates

Voltage
Current
Instantaneous Power
Energy Consumption (kWh)

using RMS-based calculations.

Step 3

The calculated values are displayed on

16×2 LCD
Blynk Mobile Dashboard
Step 4

The user can remotely control

Bulb
Socket
Motor

using relay modules through the Blynk application.

Step 5

Safety sensors continuously monitor

Fire
Gas Leakage

Whenever danger is detected,

Buzzer activates
LED glows
User receives notification.
Step 6

The face recognition system continuously monitors the camera.

If an authorized user is detected:

Door Unlocks
Servo rotates

Otherwise

Door remains locked.
🔐 Face Recognition Module

The security module uses

OpenCV
Python
Teachable Machine Model

The webcam captures live images.

Each frame is classified using the trained model.

If

Confidence > Threshold

Door Unlocks

Else

Door Remains Locked.

📱 IoT Dashboard Features

The Blynk dashboard contains

Bulb ON/OFF
Socket ON/OFF
Motor ON/OFF
Vacation Mode
Voltage Gauge
Current Gauge
Power Display
Unit Consumed
Bill Analysis
Door Status
Fire Status
Gas Status
Live Charts
🔥 Safety Module

The system constantly checks

Flame Sensor
Gas Sensor

When abnormal values are detected,

Relay can disconnect load
Alarm activates
LED turns ON
Notification sent
⚡ Energy Calculation

The project calculates

Power

Power = Voltage × Current

Energy

Energy = Power × Time

Electricity Bill

Bill = Units Consumed × Tariff
🌍 Applications
Smart Home
Smart Office
Smart Classroom
Industrial Monitoring
Hostel Energy Management
Laboratory Automation
College Projects
Home Automation
Energy Audit Systems
📊 Advantages
Low Cost
Easy to Build
Real-Time Monitoring
Remote Appliance Control
Energy Saving
Secure Access
Safety Monitoring
User Friendly
Scalable Architecture
Low Power Consumption
🚀 Future Enhancements
Machine Learning Based Energy Prediction
Solar Energy Monitoring
Smart Meter Integration
Mobile Push Notifications
Voice Control using Google Assistant
Alexa Integration
MQTT Communication
Cloud Database
Power Theft Detection
Predictive Maintenance
AI-Based Energy Optimization
Smart Scheduling
Mobile App Development
Multiple User Authentication
Fingerprint Authentication
📁 Project Structure
Smart-Energy-Monitoring-System/
│
├── Arduino_Code/
│   ├── Smart_Energy_System.ino
│
├── Face_Recognition/
│   ├── teachable_unlock.py
│   ├── fix_model.py
│   ├── keras_model.h5
│   ├── labels.txt
│
├── Images/
│   ├── Hardware.jpg
│   ├── Dashboard.png
│   ├── FaceRecognition.png
│
├── Circuit_Diagram/
│
├── Documentation/
│   ├── Report.pdf
│
├── README.md
│
└── LICENSE
📸 Project Demonstration

The project includes:

ESP32-based hardware prototype
Live Blynk IoT Dashboard
OpenCV Face Recognition
Servo Door Lock Mechanism
Relay Controlled Appliances
Energy Monitoring Dashboard
Fire & Gas Safety System
🎓 Learning Outcomes

Through this project, I gained hands-on experience in:

ESP32 Programming
Embedded Systems
IoT Application Development
Blynk IoT Dashboard Design
Electrical Parameter Measurement
Sensor Integration
Relay Automation
OpenCV Face Recognition
Python Programming
Embedded C
Hardware Debugging
Real-Time Data Visualization
Smart Home Automation
Energy Management Systems
👨‍💻 Developed By

Monishraj K
B.E. Electronics and Communication Engineering
Kongu Engineering College, Tamil Nadu, India

⭐ If you found this project useful, consider giving it a Star on GitHub!