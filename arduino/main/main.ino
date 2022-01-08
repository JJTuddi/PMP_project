#include <Adafruit_NeoPixel.h>

#include "animations/midAnimation.h"
#include "animations/frontAnimation.h"
#include "animations/heightAnimation.h"

#define LED_STRIP_PIN 3
#define MICROPHONE_PIN 6
#define NUMPIXELS 61 
#define ANIMATION_DELAY 15

Adafruit_NeoPixel ledStripPixels;
Pixel pixels[NUMPIXELS];

void setup() {
  Serial.begin(9600);
  ledStripPixels = Adafruit_NeoPixel(NUMPIXELS, LED_STRIP_PIN, NEO_GRB + NEO_KHZ800);
  ledStripPixels.begin();
  initialize();
  pinMode(MICROPHONE_PIN, INPUT);
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
  playPixelsHeight(pixels, NUMPIXELS, MICROPHONE_PIN, ANIMATION_DELAY);
  for (int i=0; i < NUMPIXELS; i++) {
    ledStripPixels.setPixelColor(i, ledStripPixels.Color(pixels[i].red, pixels[i].green, pixels[i].blue));
  }
  ledStripPixels.show();
}
