# ⚡ IoT-Based Smart Energy Monitoring, Control and Safety System

An intelligent IoT-based home automation system that provides **real-time energy monitoring**, **remote appliance control**, **electrical safety**, and **secure access using face recognition**. Built using the ESP32 microcontroller, this project integrates IoT, embedded systems, and computer vision to create a cost-effective smart energy management solution.

---

## 📖 Project Overview

The **IoT-Based Smart Energy Monitoring, Control and Safety System** is designed to monitor electrical energy consumption, remotely control electrical appliances, and improve safety through IoT technology.

The system is powered by an **ESP32 microcontroller**, which acts as the central controller for data acquisition, processing, and wireless communication. Electrical parameters are measured using the **ACS712 Current Sensor** and **ZMPT101B Voltage Sensor**. The ESP32 processes these readings to calculate voltage, current, power consumption, energy usage (kWh), and estimated electricity bills in real time.

The measured values are displayed on a **16×2 LCD** for local monitoring and transmitted to the **Blynk IoT Dashboard** for remote monitoring through a smartphone.

The project also allows users to remotely control electrical appliances using relay modules through the Blynk mobile application. Manual switching is also supported.

To enhance user safety, the system continuously monitors for fire and gas leakage. If an abnormal condition is detected, the buzzer is activated and the user is alerted immediately.

For improved security, an **OpenCV-based Face Recognition System** authenticates users before unlocking the door using a servo motor, ensuring that only authorized individuals can access the system.

This project demonstrates how IoT, embedded systems, and computer vision can be combined to build a secure, intelligent, and energy-efficient smart home solution.

---

# 🎯 Objectives

- Monitor voltage, current, power, and energy consumption in real time.
- Display live energy data on an LCD and Blynk dashboard.
- Control electrical appliances remotely through the Internet.
- Improve electrical safety using fire and gas detection.
- Provide secure access using face recognition.
- Estimate electricity bills based on energy consumption.
- Reduce unnecessary electricity wastage.

---

# ✨ Features

### ⚡ Energy Monitoring

- Real-Time Voltage Monitoring
- Real-Time Current Monitoring
- Power Calculation
- Energy Consumption (kWh)
- Electricity Bill Estimation
- Live Data Visualization

### 📱 IoT Appliance Control

- Remote Bulb Control
- Remote Socket Control
- Remote Motor Control
- Manual Relay Control
- Online Appliance Monitoring

### 🔥 Safety Features

- Fire Detection
- Gas Leakage Detection
- Automatic Buzzer Alert
- LED Status Indication
- Emergency Notification

### 🔐 Security Features

- OpenCV Face Recognition
- Authorized User Authentication
- Automatic Servo Door Lock

### 📊 Dashboard Features

- Voltage Monitoring
- Current Monitoring
- Power Monitoring
- Energy Consumption
- Electricity Bill
- Appliance Status
- Door Status
- Fire Status
- Gas Status
- Live Charts

---

# 🛠 Hardware Components

| Component | Purpose |
|-----------|---------|
| ESP32 Development Board | Main Controller |
| ACS712 Current Sensor | Current Measurement |
| ZMPT101B Voltage Sensor | Voltage Measurement |
| 16×2 LCD Display | Local Display |
| 4-Channel Relay Module | Appliance Control |
| Servo Motor | Door Lock |
| Flame Sensor | Fire Detection |
| MQ Gas Sensor | Gas Detection |
| Active Buzzer | Alarm |
| LEDs | Status Indicators |
| Breadboard | Circuit Assembly |
| Jumper Wires | Wiring |
| Power Supply | System Power |

---

# 💻 Software Requirements

- Arduino IDE
- Python 3.x
- OpenCV
- Visual Studio Code
- Blynk IoT
- IFTTT
- Git
- GitHub

---

# 🔧 Technologies Used

- ESP32
- Embedded C
- Python
- OpenCV
- Arduino Framework
- Internet of Things (IoT)
- Wi-Fi Communication
- Blynk Cloud
- HTTP Protocol

---

# ⚙ System Architecture

The system consists of five major modules:

## 1. Energy Monitoring Module

Measures AC voltage and current using the ZMPT101B and ACS712 sensors. The ESP32 calculates:

- Voltage (V)
- Current (A)
- Power (W)
- Energy (kWh)

---

## 2. IoT Communication Module

The ESP32 connects to Wi-Fi and synchronizes data with the Blynk Cloud.

Users can:

- Monitor live sensor values
- Control appliances remotely
- View electricity consumption
- Check estimated electricity bills

---

## 3. Appliance Control Module

Electrical appliances are connected through relay modules.

Supported loads include:

- Bulb
- Fan
- Motor
- Socket

Each appliance can be controlled:

- Manually
- Through the Blynk App
- Via Internet

---

## 4. Safety Monitoring Module

The safety module continuously monitors:

- Fire
- Gas Leakage

Whenever an abnormal condition is detected:

- Buzzer activates
- LED turns ON
- User receives an alert

---

## 5. Face Recognition Module

The security module uses:

- Python
- OpenCV
- Teachable Machine

The webcam continuously captures images.

If an authorized user is detected:

- Door Unlocks
- Servo rotates

Otherwise:

- Door remains locked.

---

# 🔄 Working Principle

1. The ESP32 powers up and initializes all sensors.
2. Voltage and current sensors continuously measure electrical parameters.
3. The ESP32 calculates power, energy consumption, and estimated electricity bills.
4. Data is displayed on the LCD and transmitted to the Blynk dashboard.
5. Users can remotely control connected appliances through the mobile application.
6. Fire and gas sensors monitor environmental conditions continuously.
7. If an abnormal condition is detected, the buzzer activates and the user is alerted.
8. The face recognition system authenticates users before unlocking the door.

---

# 📐 Energy Calculation

### Power

```text
Power (W) = Voltage (V) × Current (A)
```

### Energy

```text
Energy (kWh) = Power × Time
```

### Electricity Bill

```text
Bill = Energy Consumed × Tariff
```

---

# 📱 Blynk Dashboard

The dashboard provides:

- Voltage Monitoring
- Current Monitoring
- Power Monitoring
- Energy Consumption
- Bill Estimation
- Appliance Control
- Door Status
- Fire Status
- Gas Status
- Live Charts

---


# 🚀 Applications

- 🏠 Smart Homes
- 🏢 Smart Buildings
- 🏭 Industrial Monitoring
- 🏫 Educational Laboratories
- 🏢 Office Automation
- 🏫 Smart Classrooms
- ⚡ Energy Audit Systems
- 🏠 Home Automation
- 🏨 Hostel Energy Management
- 🎓 College Mini & Major Projects

---

# ✅ Advantages

- Real-Time Energy Monitoring
- Remote Appliance Control
- Low-Cost Implementation
- Easy Installation and Maintenance
- Improved Electrical Safety
- Secure Face Recognition Authentication
- Low Power Consumption
- User-Friendly Interface
- Scalable Architecture
- Reliable IoT Connectivity

---

# 🔮 Future Enhancements

- AI-Based Energy Consumption Prediction
- Machine Learning-Based Load Analysis
- Solar Energy Monitoring
- Smart Meter Integration
- MQTT Communication
- Google Assistant Integration
- Amazon Alexa Integration
- Mobile Push Notifications
- Cloud Database Integration
- Predictive Maintenance
- Power Theft Detection
- Smart Scheduling of Appliances
- Fingerprint Authentication
- Multi-User Authentication
- Dedicated Android Application


---

# 📸 Project Demonstration

The project demonstrates:

- ESP32-Based Hardware Prototype
- Real-Time Energy Monitoring
- Live Blynk IoT Dashboard
- OpenCV Face Recognition Authentication
- Automatic Servo Door Lock System
- Relay-Based Appliance Control
- Fire Detection and Alarm System
- Gas Leakage Detection
- Remote Appliance Monitoring and Control
- Energy Consumption & Bill Analysis

---

# 📚 Learning Outcomes

Through this project, I gained hands-on experience in:

- ESP32 Programming
- Embedded C Programming
- Embedded Systems Design
- Internet of Things (IoT)
- Blynk IoT Platform
- Sensor Interfacing
- Voltage & Current Measurement
- Relay Automation
- OpenCV Face Recognition
- Python Programming
- Wi-Fi Communication
- Real-Time Data Visualization
- Hardware Integration
- Electrical Energy Monitoring
- Smart Home Automation
- System Debugging and Testing

---

# 👨‍💻 Developer

**Monishraj K**

B.E. Electronics and Communication Engineering

Kongu Engineering College

Tamil Nadu, India


---

## ⭐ Support

If you found this project useful, please consider giving this repository a **⭐ Star** on GitHub. Your support is greatly appreciated!
