/*
 * MONSTRIX Robot - Basic Emotions Example
 * Simplified version for beginners
 * 
 * This example shows basic emotion cycling without shake detection
 * Good for learning and testing the display and eyes library
 */

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <FluxGarage_RoboEyes.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDR 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
roboEyes eyes;

unsigned long lastEmotionChange = 0;
const int EMOTION_INTERVAL = 3000; // Change emotion every 3 seconds

void setup() {
  Wire.begin();
  Serial.begin(115200);
  
  Serial.println("MONSTRIX Basic Robot Starting...");

  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.setRotation(2);
  display.clearDisplay();
  display.display();

  eyes.begin(SCREEN_WIDTH, SCREEN_HEIGHT, 60);
  eyes.setAutoblinker(ON, 2, 1);
  eyes.setIdleMode(ON, 1, 1);
  eyes.setMood(DEFAULT);
  
  Serial.println("Ready! Watch the emotions change every 3 seconds");
}

void loop() {
  eyes.update();
  delay(16);

  if (millis() - lastEmotionChange > EMOTION_INTERVAL) {
    lastEmotionChange = millis();
    changeEmotion();
  }
}

void changeEmotion() {
  int emotion = random(0, 3);
  
  switch(emotion) {
    case 0:
      eyes.setMood(DEFAULT);
      Serial.println("Emotion: Default");
      break;
    case 1:
      eyes.setMood(HAPPY);
      Serial.println("Emotion: Happy");
      break;
    case 2:
      eyes.setMood(TIRED);
      Serial.println("Emotion: Tired");
      break;
  }
}
