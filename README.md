# 🤖 MONSTRIX Robot - Emotional AI Companion

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Platform: ESP32](https://img.shields.io/badge/Platform-ESP32-blue.svg)](https://www.espressif.com/en/products/socs/esp32)
[![Made with Love](https://img.shields.io/badge/Made%20with-❤️-red.svg)]()

> *Inspired by "Love, Death & Robots" series*

An emotional robot companion that reacts to the world around it with beautiful animated eyes and personality. Built with ESP32-C3, OLED display, and gyroscope sensor.

![MONSTRIX Robot](docs/images/robot_preview.jpg)

## ✨ Features

- 🎭 **Emotional AI** - Multiple personality states with smooth animations
- 👁️ **Beautiful Eyes** - Realistic eye movements and blinking using FluxGarage_RoboEyes
- 🔄 **Auto Emotions** - Changes mood every 6 seconds automatically
- 😠 **Shake Reaction** - Gets angry when shaken or moved abruptly
- ⚡ **Low Power** - Optimized for battery operation
- 🛠️ **Open Source** - Fully customizable and hackable

## 🎯 Emotions

| Emotion | Trigger | Duration |
|---------|---------|----------|
| 😊 **Happy** | Random cycle | 6 seconds |
| 😴 **Tired** | Random cycle | 6 seconds |
| 🤔 **Confused** | Random cycle | 6 seconds |
| 😐 **Default** | Random cycle | 6 seconds |
| 😠 **Angry** | Shake detection | 3 seconds |

## 🔧 Hardware Requirements

### Core Components
- **ESP32-C3** microcontroller (main brain)
- **OLED 0.96" SSD1306** display (I2C, address 0x3C)
- **MPU6050** gyroscope/accelerometer (I2C, address 0x68)
- **Jumper wires** for connections

### 3D Printed Parts
- Robot head housing
- Robot body housing
- *STL files available in `/hardware` folder*

### Optional Upgrades
- Li-Ion 18650 battery + TP4056 charging module
- WS2812B RGB LED strips
- DFPlayer Mini sound module
- Micro speaker

## 📐 Wiring Diagram

```
ESP32-C3 Pin | Component      | Purpose
-------------|----------------|----------------
3V3          | OLED VCC       | Power
3V3          | MPU6050 VCC    | Power  
GND          | OLED GND       | Ground
GND          | MPU6050 GND    | Ground
GPIO8        | OLED SDA       | I2C Data
GPIO8        | MPU6050 SDA    | I2C Data
GPIO9        | OLED SCL       | I2C Clock
GPIO9        | MPU6050 SCL    | I2C Clock
```

![Wiring Diagram](docs/wiring_diagram.png)

## 📚 Library Dependencies

Install these libraries through Arduino IDE Library Manager:

```cpp
// Required libraries
#include <Wire.h>                 // I2C communication
#include <Adafruit_GFX.h>         // Graphics library
#include <Adafruit_SSD1306.h>     // OLED display driver
#include <FluxGarage_RoboEyes.h>  // Animated robot eyes
#include <MPU6050_light.h>        // MPU6050 sensor library
```

### Installation Links:
- [Adafruit GFX Library](https://github.com/adafruit/Adafruit-GFX-Library)
- [Adafruit SSD1306](https://github.com/adafruit/Adafruit_SSD1306)
- [FluxGarage RoboEyes](https://github.com/FluxGarage/RoboEyes)
- [MPU6050_light](https://github.com/rfetick/MPU6050_light)

## 🚀 Quick Start

### 1. Hardware Assembly
1. 3D print the robot housing parts
2. Connect components according to wiring diagram
3. Secure everything in the printed housing

### 2. Software Setup
1. Install [Arduino IDE](https://www.arduino.cc/en/software)
2. Install ESP32 board package
3. Install required libraries (see dependencies above)
4. Upload `monstrix_robot.ino` to your ESP32-C3

### 3. Calibration
1. Place robot on flat surface
2. Power on and wait 5 seconds for gyroscope calibration
3. Robot is ready when eyes appear!

## 🎮 Usage

- **Normal Operation**: Robot cycles through emotions every 6 seconds
- **Shake Detection**: Gently shake or move the robot to trigger anger
- **Reset**: Press ESP32 reset button to restart
- **Serial Monitor**: Connect at 115200 baud for debug info

## 🛠️ Customization

### Emotion Timing
```cpp
const int EMOTION_INTERVAL = 6000; // Change to adjust emotion cycle time
const int ANGRY_DURATION = 3000;   // Change angry duration
```

### Shake Sensitivity
```cpp
if (!isAngry && acc > 2.5) {       // Increase value = less sensitive
```

### Add New Emotions
```cpp
// In setRandomMood() function, add:
case 4: 
  eyes.setMood(LOVE); 
  moodName = "Love";
  break;
```

## 📁 Project Structure

```
monstrix-cod/
├── monstrix_robot.ino          # Main Arduino sketch
├── README.md                   # This file
├── LICENSE                     # MIT License
├── docs/                       # Documentation
│   ├── images/                 # Photos and diagrams
│   ├── wiring_diagram.png      # Connection diagram
│   └── assembly_guide.md       # Step-by-step assembly
├── hardware/                   # 3D models and schematics
│   ├── robot_head.stl          # 3D printable head
│   └── schematic.pdf           # Electronic schematic
└── examples/                   # Additional code examples
    ├── basic_emotions.ino      # Simplified version
    ├── advanced_features.ino   # With sound and RGB
    └── battery_optimized.ino   # Low power version
```

## 🔋 Power Consumption

| Mode | Current Draw | Battery Life (2000mAh) |
|------|-------------|------------------------|
| Active | ~100mA | ~20 hours |
| Sleep | ~10mA | ~200 hours |

## 🎯 Roadmap

- [ ] Voice recognition commands
- [ ] Wi-Fi remote control app
- [ ] Bluetooth LE connectivity  
- [ ] Sound effects integration
- [ ] RGB mood lighting
- [ ] Multiple robot interaction
- [ ] Machine learning emotions

## 🤝 Contributing

Contributions are welcome! Please read our [Contributing Guide](CONTRIBUTING.md) first.

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## 📝 License

[![License: CC BY-NC 4.0](https://img.shields.io/badge/License-CC%20BY--NC%204.0-lightgrey.svg)](https://creativecommons.org/licenses/by-nc/4.0/)

## 📚 Library Compatibility

### FluxGarage_RoboEyes Library Versions:

**🟢 Compatible with ALL versions:**
- ✅ **v1.0.x** - Use old constructor syntax: `roboEyes eyes;`
- ✅ **v1.1.x** - Use new constructor syntax: `RoboEyes<Adafruit_SSD1306> eyes(display);`

**📝 Code automatically detects library version:**
- If compilation fails with `'RoboEyes' does not name a type` → Use `roboEyes eyes;`
- If compilation fails with `'roboEyes' does not name a type` → Use `RoboEyes<Adafruit_SSD1306> eyes(display);`

**🎯 Features by version:**
- **v1.0.x**: Basic emotions (Default, Happy, Tired, Angry, Confused)
- **v1.1.x**: Enhanced with sweat animations (`setSweat()` function)

**⚙️ Installation:**
1. Arduino IDE → Tools → Manage Libraries
2. Search "FluxGarage RoboEyes" 
3. Install any version (code is universal)
4. Upload sketch to ESP32-C3

**🔧 If you get compilation errors:**
- Check library version in error message
- Try the alternative constructor syntax
- Ensure all dependencies are installed
## 🙏 Acknowledgments

- Inspired by Netflix's "Love, Death & Robots" series
- Thanks to FluxGarage for the amazing RoboEyes library
- ESP32 community for continuous support
- All makers and contributors who help improve this project

---

⭐ **If you like this project, please give it a star!** ⭐

Made with ❤️ in Russia 🇷🇺
