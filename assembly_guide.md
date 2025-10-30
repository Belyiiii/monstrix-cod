# 🔧 Assembly Guide

## Step-by-Step Assembly Instructions

### 📦 What's in the Kit

- [ ] Robot head (3D printed)
- [ ] Robot body (3D printed)
- [ ] ESP32-C3 microcontroller
- [ ] OLED 0.96" display
- [ ] MPU6050 gyroscope sensor
- [ ] 10x jumper wires
- [ ] This instruction manual

### 🛠️ Tools Needed

- Small screwdriver
- Soldering iron (optional, for permanent connections)
- Multimeter (for testing)

### 📐 Assembly Steps

#### Step 1: Prepare the Housing
1. Check that both head and body parts fit together smoothly
2. Remove any support material from 3D printed parts
3. Test-fit all electronic components in the housing

#### Step 2: Wire the Components

**Power Connections:**
- ESP32-C3 `3V3` → OLED `VCC`
- ESP32-C3 `3V3` → MPU6050 `VCC`
- ESP32-C3 `GND` → OLED `GND`
- ESP32-C3 `GND` → MPU6050 `GND`

**I2C Data Bus:**
- ESP32-C3 `GPIO8` → OLED `SDA` → MPU6050 `SDA`
- ESP32-C3 `GPIO9` → OLED `SCL` → MPU6050 `SCL`

#### Step 3: Test Connections

1. Connect ESP32-C3 to computer via USB-C
2. Upload the test sketch from `/examples/basic_emotions.ino`
3. Open Serial Monitor (115200 baud)
4. Verify all devices are detected

**Expected output:**
```
MONSTRIX Basic Robot Starting...
Ready! Watch the emotions change every 3 seconds
Emotion: Default
Emotion: Happy
Emotion: Tired
```

#### Step 4: Upload Main Firmware

1. Upload `monstrix_robot.ino` to the ESP32-C3
2. Place robot on flat surface for gyroscope calibration
3. Wait 5 seconds for initialization

#### Step 5: Final Assembly

1. Carefully place all components in the body housing
2. Ensure display is visible through the head opening
3. Connect head and body pieces
4. Secure with screws if needed

### ⚡ Power Options

**USB Powered (Recommended for testing):**
- Connect USB-C cable to ESP32-C3
- Provides stable 5V power

**Battery Powered (Advanced):**
- Add Li-Ion 18650 battery
- Include TP4056 charging circuit
- Connect to ESP32-C3 VIN pin

### 🔍 Troubleshooting

**Display not working:**
- Check I2C connections (SDA/SCL)
- Verify 3.3V power supply
- Test with I2C scanner sketch

**Gyroscope not responding:**
- Ensure MPU6050 is properly connected
- Check I2C address (should be 0x68)
- Keep robot still during calibration

**No emotions showing:**
- Verify FluxGarage_RoboEyes library is installed
- Check Serial Monitor for error messages
- Test with basic_emotions.ino first

### 📱 Testing Shake Detection

1. Gently shake the robot side to side
2. Eyes should turn angry (red/annoyed expression)
3. After 3 seconds, should return to normal emotions
4. If not working, check MPU6050 connections

### 🎯 Calibration Tips

- Keep robot completely still during startup
- Place on level surface for best results
- Avoid vibrations during first 5 seconds
- Recalibrate by pressing reset button

### 🔄 Updating Firmware

1. Connect robot to computer via USB-C
2. Open Arduino IDE
3. Select "ESP32C3 Dev Module" board
4. Upload new firmware
5. Robot will restart automatically

---

**Need help?** Check our [troubleshooting guide](../README.md#troubleshooting) or contact support!
