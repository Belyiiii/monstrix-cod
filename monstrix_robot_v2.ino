/*
 * MONSTRIX Emotional Robot v2.0 - New Library v1.1.1
 * ESP32-C3 + OLED 0.96" + MPU6050 + FluxGarage_RoboEyes v1.1.1
 * 
 * Author: Igor Fedorov (@igor.fedorov)
 * Updated for new library syntax and features
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

// Create display object first
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// NEW v1.1.1 syntax - pass display reference to constructor
RoboEyes<Adafruit_SSD1306> eyes(display);

MPU6050 mpu(Wire);

// Timing variables
unsigned long lastEmotionChange = 0;
unsigned long lastAngryTime = 0;
unsigned long lastSweatTime = 0;
const int EMOTION_INTERVAL = 6000;
const int ANGRY_DURATION = 3000;
const int SWEAT_DURATION = 5000;
bool isAngry = false;
bool isSweating = false;

void setup() {
  Wire.begin();
  Serial.begin(115200);
  
  Serial.println("MONSTRIX Robot v2.0 Starting...");
  Serial.println("Using FluxGarage_RoboEyes v1.1.1");

  if(!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println("SSD1306 allocation failed");
    return;
  }
  
  display.setRotation(2);
  display.clearDisplay();
  display.display();
  Serial.println("Display initialized");

  // Initialize with new v1.1.1 features
  eyes.begin(SCREEN_WIDTH, SCREEN_HEIGHT, 60);
  eyes.setAutoblinker(ON, 3, 1);
  eyes.setIdleMode(ON, 2, 1);
  eyes.setMood(DEFAULT);
  
  // NEW v1.1.1 feature - optimize display colors
  eyes.setDisplayColors(0, 1);
  
  Serial.println("RoboEyes v1.1.1 initialized with new features!");

  byte status = mpu.begin();
  if(status != 0) {
    Serial.print("MPU6050 connection failed. Status: ");
    Serial.println(status);
  } else {
    Serial.println("MPU6050 connected");
  }
  
  delay(1000);
  mpu.calcGyroOffsets();
  Serial.println("MPU6050 calibrated");
  
  Serial.println("MONSTRIX Robot v2.0 Ready!");
  Serial.println("NEW: Sweat animations when angry! 💦");
  Serial.println("Shake me to see anger! 😠");
}

void loop() {
  mpu.update();
  eyes.update();
  delay(16);

  unsigned long now = millis();
  float acc = abs(mpu.getAccX()) + abs(mpu.getAccY()) + abs(mpu.getAccZ());

  // Shake detection
  if (!isAngry && acc > 2.5) {
    Serial.println("Shake detected! Getting angry... 😠");
    eyes.setMood(ANGRY);
    
    // NEW v1.1.1 feature - sweat when angry!
    eyes.setSweat(ON);
    isSweating = true;
    lastSweatTime = now;
    Serial.println("Sweating from anger! 💦");
    
    isAngry = true;
    lastAngryTime = now;
    return;
  }

  // Stop sweating after timeout
  if (isSweating && (now - lastSweatTime > SWEAT_DURATION)) {
    eyes.setSweat(OFF);
    isSweating = false;
    Serial.println("Stopped sweating");
  }

  // Anger timeout
  if (isAngry && (now - lastAngryTime > ANGRY_DURATION)) {
    Serial.println("Calming down... 😌");
    isAngry = false;
    lastEmotionChange = now;
    setRandomMood();
    return;
  }

  // Auto emotion change
  if (!isAngry && (now - lastEmotionChange > EMOTION_INTERVAL)) {
    lastEmotionChange = now;
    setRandomMood();
  }
}

void setRandomMood() {
  int mood = random(0, 6);  // More variety
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
    case 4:
      // Sometimes sweat during normal emotions (stress)
      eyes.setMood(DEFAULT);
      if (random(0, 4) == 0) { // 25% chance
        eyes.setSweat(ON);
        isSweating = true;
        lastSweatTime = millis();
        moodName = "Stressed (sweating)";
      } else {
        moodName = "Calm";
      }
      break;
    case 5:
      eyes.anim_laugh();
      moodName = "Laughing";
      break;
  }
  
  Serial.print("New emotion: ");
  Serial.println(moodName);
}
