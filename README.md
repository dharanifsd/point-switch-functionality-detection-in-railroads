# point-switch-functionality-detection-in-railroads


A smart **railroad safety system** designed to detect railway point (track) alignment status in real time and alert the locomotive pilot **1 km before** reaching the switching point. This helps prevent derailments and accidents caused by improper track alignment.

---

## 📌 Problem Statement
Rail accidents occur when railway point switches fail to align properly or are unknowingly left in an incorrect position. These failures may go unnoticed until the train reaches the switch — by then, it's too late.

---

## 🎯 Objective
To design a **reliable, low-cost, and real-time detection system** that:
- Detects whether the track alignment is correct using **inductive proximity sensors**
- Transmits the status wirelessly using **LoRa module**
- Displays clear visual alerts to the locomotive pilot
- Ensures enhanced safety and operational awareness

---

## 🚀 Key Features
- ✔️ Detects correct / incorrect point switch alignment  
- ✔️ Wireless data transmission up to 1 km using **LoRa Communication**
- ✔️ Status indication via **LED + Display / Voice Alert**
- ✔️ Prevents derailments and improves safety
- ✔️ Prototype-friendly & scalable to real railway environments
- ✔️ Can support future integration (camera, AI analytics, IoT dashboard)

---

## 🏗️ System Architecture
**1️⃣ Trackside Unit**
- Inductive Proximity Sensors detect track alignment
- Microcontroller processes alignment state
- LoRa Transmitter sends data wirelessly

**2️⃣ Locomotive Unit**
- LoRa Receiver receives signal
- Status displayed to pilot:
  - 🟢 **Track Detected (Aligned Correctly)**
  - 🔴 **Track Not Detected (Misaligned)**

---

## 🧠 Working Principle
1. When a train approaches a switching point (~1 km away)  
2. Sensors detect whether the tracks are aligned in a safe position  
3. Signal transmitted wirelessly to train cabin  
4. Pilot receives real-time warning
5. Preventive action can be taken before reaching the track

---

## 🛠️ Hardware Components
- Inductive Proximity Sensors  
- LoRa Transmitter–Receiver Module  
- Microcontroller (Arduino / ESP32 / Similar)  
- Indicator LEDs  
- Optional: Display Module / Buzzer / Voice Module  
- Power Supply

---

## 💻 Software / Firmware
- Arduino IDE, Python
- Data framing for LoRa transmission
- Error handling & stable signal logic

---

## 📐 Applications
- Indian Railways
- Metro rail systems
- Private railway networks
- Industrial rail transport

---

## 🔮 Future Enhancements
- Integration with **camera module** for visual confirmation
- IoT cloud dashboard
- AI-based predictive maintenance
- GPS integration for automated zone-based alerts
- Railway control room integration
 --- 

## 👨‍💻 Team & Contribution
Project developed as part of **SIP (Student Innovation Project)** focusing on railway safety enhancement.

Contributions, suggestions, and improvements are welcome!

---

## 📄 License
Open-source for research and academic use.

---

## 🙏 Acknowledgements
Thanks to:
- Mentors & academic guidance

---

### ⭐ If you like this project, don’t forget to star the repo!
