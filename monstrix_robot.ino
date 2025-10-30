/*
 * MONSTRIX Emotional Robot
 * ESP32-C3 + OLED 0.96" + MPU6050 + FluxGarage_RoboEyes
 * 
 * Author: Igor Fedorov (@igor.fedorov)
 * Project: https://monstrix.ru
 * GitHub: https://github.com/Belyiiii/monstrix-cod
 * 
 * Description:
 * Emotional robot inspired by "Love, Death & Robots" series
 * Features auto emotion cycles every 6 seconds and shake reactions
 * 
 * Hardware:
 * - ESP32-C3 microcontroller
 * - OLED 0.96" SSD1306 display (I2C address 0x3C)
 * - MPU6050 gyroscope/accelerometer
 * - I2C connections: SDA=GPIO8, SCL=GPIO9
 * 
 * Dependencies:
 * - Adafruit_GFX
 * - Adafruit_SSD1306
 * - FluxGarage_RoboEyes
 * - MPU6050_light
 */

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <FluxGarage_RoboEyes.h>
#include <MPU6050_light.h>

// Display configuration
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDR 0x3C

// Create objects
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
roboEyes eyes;
MPU6050 mpu(Wire);

// Timing variables
unsigned long lastEmotionChange = 0;
unsigned long lastAngryTime = 0;
const int EMOTION_INTERVAL = 6000; // Change emotion every 6 seconds
const int ANGRY_DURATION = 3000;   // Stay angry for 3 seconds
bool isAngry = false;

void setup() {
  // Initialize I2C (ESP32-C3 uses GPIO8=SDA, GPIO9=SCL by default)
  Wire.begin();
  Serial.begin(115200);
  
  Serial.println("MONSTRIX Robot Starting...");

  // Initialize OLED display
  if(!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println("SSD1306 allocation failed");
    return;
  }
  
  display.setRotation(2);
  display.clearDisplay();
  display.display();
  Serial.println("Display initialized");

  // Initialize robot eyes
  eyes.begin(SCREEN_WIDTH, SCREEN_HEIGHT, 60);
  eyes.setAutoblinker(ON, 3, 1);  // Auto blink every 3 seconds
  eyes.setIdleMode(ON, 2, 1);     // Idle animations every 2 seconds
  eyes.setMood(DEFAULT);          // Start with default mood
  Serial.println("RoboEyes initialized");

  // Initialize MPU6050
  byte status = mpu.begin();
  if(status != 0) {
    Serial.print("MPU6050 connection failed. Status: ");
    Serial.println(status);
  } else {
    Serial.println("MPU6050 connected");
  }
  
  delay(1000);
  mpu.calcGyroOffsets(); // Calibrate gyroscope (keep robot still!)
  Serial.println("MPU6050 calibrated");
  
  Serial.println("MONSTRIX Robot Ready!");
  Serial.println("Shake me to see anger! 😠");
}

void loop() {
  // Update sensors and display
  mpu.update();
  eyes.update();
  delay(16); // ~60 FPS

  unsigned long now = millis();

  // Calculate total acceleration (shake detection)
  float acc = abs(mpu.getAccX()) + abs(mpu.getAccY()) + abs(mpu.getAccZ());

  // Check for shake (if not already angry)
  if (!isAngry && acc > 2.5) {
    Serial.println("Shake detected! Getting angry... 😠");
    eyes.setMood(ANGRY);
    isAngry = true;
    lastAngryTime = now;
    return;
  }

  // Check if anger duration expired
  if (isAngry && (now - lastAngryTime > ANGRY_DURATION)) {
    Serial.println("Calming down... 😌");
    isAngry = false;
    lastEmotionChange = now; // Reset emotion timer
    setRandomMood();
    return;
  }

  // Auto emotion change (only if not angry)
  if (!isAngry && (now - lastEmotionChange > EMOTION_INTERVAL)) {
    lastEmotionChange = now;
    setRandomMood();
  }
}

void setRandomMood() {
  int mood = random(0, 4);
  String moodName;
  
  switch (mood) {
    case 0: 
      eyes.setMood(DEFAULT); 
      moodName = "Default";
      break;
    case 1: 
      eyes.setMood(HAPPY); 
      moodName = "Happy";
      break;
    case 2: 
      eyes.setMood(TIRED); 
      moodName = "Tired";
      break;
    case 3: 
      eyes.anim_confused(); 
      moodName = "Confused";
      break;
  }
  
  Serial.print("New emotion: ");
  Serial.println(moodName);
}
