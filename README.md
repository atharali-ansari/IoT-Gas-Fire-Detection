# 🚨 IoT-Based Gas Leakage & Fire Detection and Prevention System

This project is a real-time **IoT safety system** built using **ESP32**, designed to **detect gas leaks and fire**, take immediate preventive actions, and notify the user — ensuring timely response and improved safety for residential or small industrial environments.

---

## 🎯 Features

- 🧪 Gas detection using **MQ-2 sensor**
- 🔥 Fire detection using **IR flame sensor**
- 🌬️ **Exhaust fan** activation when gas is detected
- 🔒 **Servo motor** to automatically shut off the gas regulator
- 🔊 Audible and visual alert: **Buzzer + Red LED**
- 💦 **Water pump** activation on fire detection
- 📧 **Email alert** sent to the user when gas or fire is detected
- 📟 **LCD Display** shows live gas values and system status
- ☁️ Powered by **ESP32 microcontroller**

---

## 🛠️ Components Used

| Component             | Description                          |
|-----------------------|--------------------------------------|
| ESP32                 | Microcontroller with Wi-Fi           |
| MQ-2 Sensor           | Detects LPG, methane, etc.           |
| IR Flame Sensor       | Detects flames/fire                  |
| Relay Module (2-Ch)   | Controls exhaust fan & water pump    |
| Servo Motor           | Closes gas regulator                 |
| Buzzer & Red LED      | Alerts on gas detection              |
| LCD 16x2 (I2C)        | Displays current gas value and status|
| Water Pump            | Activates during fire                |
| Exhaust Fan           | Turns on during gas detection        |

---

## 🧾 How It Works

1. **Gas Detected:**
   - Activates exhaust fan via relay
   - Closes gas valve using servo motor
   - Triggers buzzer and red LED
   - Sends email notification to the user
   - LCD displays "Gas Detected"

2. **Fire Detected:**
   - Activates water pump to extinguish flames
   - Sends email notification
   - LCD displays "Fire Detected"

3. **Normal Condition:**
   - System resets alarm
   - Turns off fan and water pump
   - LCD shows "No Gas / No Fire"

---

## 📦 Required Libraries

Install the following libraries in Arduino IDE:

| Library Name            | How to Install                                         |
|-------------------------|--------------------------------------------------------|
| `LiquidCrystal_I2C`     | Library Manager (`by Frank de Brabander` or similar)  |
| `ESP32Servo`            | Library Manager                                        |
| `WiFi.h`                | Built-in with ESP32 core                               |
| `ESP Mail Client`       | [GitHub](https://github.com/mobizt/ESP-Mail-Client) or Library Manager |

---

## 🧪 Circuit Overview

> *(Add a Fritzing diagram or real setup photo here if available)*

---

## 🔐 Email Setup (Important)

To use the email feature:
- Enable **2-Step Verification** on your Gmail account
- Create an **App Password** and use it in `sender_password`
- Make sure **less secure apps access is OFF**

Replace the following fields in your code:
```cpp
#define WIFI_SSID "your_wifi_name"
#define WIFI_PASSWORD "your_wifi_password"
#define sender_email "your_email@gmail.com"
#define sender_password "your_app_password"
#define Recipient_email "receiver_email@gmail.com"
