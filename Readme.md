# 🛡 HomeSec – IoT Home Security System

**ESP32 + PIR + Door Sensor + DHT22, simulated online on Wokwi, with a live multi-page web dashboard over MQTT.**

## 🎯 Problem
Break-ins often go unnoticed when nobody is home, and commercial security systems are expensive.

## 💡 Solution
A low-cost ESP32 node monitors motion, door status and temperature. It sends data over MQTT to a web dashboard, where the owner can see live status, get alerts and arm/disarm the system remotely.

```
Sensors → ESP32 (Wokwi) → MQTT broker (HiveMQ) → Web dashboard
                                   ↑                    │
                                   └──── ARM / DISARM ──┘
```

## ✨ Features
- Live motion, door, temperature and humidity monitoring
- Remote Arm / Disarm / Silence siren / Test alarm
- Buzzer + LED alarm on the ESP32 when armed and triggered
- Multi-page dashboard: Dashboard, Sensors, Event Log, Settings, About
- Event history saved in the browser
- Demo mode (works without hardware)

## 🛠️ Tech Stack
- **Hardware (simulated):** ESP32, PIR sensor, door switch, DHT22, buzzer, LED
- **Firmware:** C++ (Arduino framework), PubSubClient, DHT library
- **Protocol:** MQTT (public broker `broker.hivemq.com`)
- **Frontend:** HTML, CSS, JavaScript (mqtt.js)

## 📂 Project Structure
```
├── dashboard/
│   └── index.html        # multi-page web app
├── wokwi/
│   ├── sketch.ino        # ESP32 code
│   ├── diagram.json      # circuit
│   └── libraries.txt
└── README.md
```

## ▶️ How to Run
1. Create a new ESP32 project on [wokwi.com](https://wokwi.com) and paste the files from `wokwi/`.
2. Change `DEVICE_ID` in `sketch.ino` to a unique value and press ▶ Play.
3. Open `dashboard/index.html` in a browser → **Settings** → enter the same Device ID → Save.
4. Click **Arm**, then trigger the PIR sensor or hold the door button in Wokwi. The alarm shows on the dashboard.

> No hardware? Tick **Demo mode** in Settings to see the dashboard with fake data.

## 📸 Screenshots
### Dashboard
![Dashboard safe](dashboard-safe.png)
![Dashboard alarm](dashboard-alarm.png)

### Wokwi Circuit
![Wokwi circuit](wokwi-circuit.png)

**Live simulation:** [Open in wokwi](https://wokwi.com/projects/477334440456700929)

## ⚠️ Note
The public MQTT broker has no authentication, so this is for learning and demos only.

---
Made by **Adishree Chavan**
