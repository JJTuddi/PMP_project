#include <Adafruit_NeoPixel.h>

#include "animations/midAnimation.h"
#include "animations/frontAnimation.h"
#include "animations/heightAnimation.h"

#define LED_STRIP_PIN 3
#define MICROPHONE_PIN 6
#define NUMPIXELS 61 
#define ANIMATION_DELAY 15
#define INTERRUPTION_PIN 2
#define INTERRUPT_B0 10
#define INTERRUPT_B1 11

Adafruit_NeoPixel ledStripPixels;
Pixel pixels[NUMPIXELS];

int currentAnimation = 0;
void (*animations[])(Pixel*, int, int, int) = {playPixelsHeight, playPixelsMid, playPixelsFront};
int numberOfAnimations = sizeof(animations) / sizeof(&playPixelsMid);

void setup() {
  Serial.begin(9600);
  ledStripPixels = Adafruit_NeoPixel(NUMPIXELS, LED_STRIP_PIN, NEO_GRB + NEO_KHZ800);
  ledStripPixels.begin();
  initialize();
  pinMode(MICROPHONE_PIN, INPUT);
  pinMode(INTERRUPT_B0, INPUT);
  pinMode(INTERRUPT_B1, INPUT);
  pinMode(INTERRUPTION_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(INTERRUPTION_PIN), changeAnimation, HIGH);
}

void loop() {
      displayPixels();
}

void initialize() {
      for (int i = 0; i < NUMPIXELS; i++) {
            pixels[i].red = 0;
            pixels[i].green = 0;
            pixels[i].blue = 0;
      }
}

void displayPixels() {
  animations[currentAnimation](pixels, NUMPIXELS, MICROPHONE_PIN, ANIMATION_DELAY);
  for (int i=0; i < NUMPIXELS; i++) {
    ledStripPixels.setPixelColor(i, ledStripPixels.Color(pixels[i].red, pixels[i].green, pixels[i].blue));
  }
  ledStripPixels.show();
}

void changeAnimation() {
  // Actually, there are not only HIGH and LOW, there are many other values, also for FALLING_EDGE, CHANGE and so on with different code value
  currentAnimation = 0;
  if (digitalRead(INTERRUPT_B1)) {
    currentAnimation += 2;
  }
  if (digitalRead(INTERRUPT_B0)) {
    currentAnimation += 1;
  }
}
