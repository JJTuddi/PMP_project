#ifndef MID_ANIMATION_H
#define MID_ANIMATION_H

#include "../utils/Pixel.h"

#define MID_SPREAD_COEFFICIENT 2
#define MID_WIDTH 3

void midSpread(Pixel pixels[], int mid, int numberOfPixels) {
      for (int i = 0; i < mid; i++) {
            pixels[i] = pixels[i + 1];
      }
      for (int i = numberOfPixels - 1; i > mid; i--) {
            pixels[i] = pixels[i - 1];
      }
}

void playPixelsMid(Pixel pixels[], int numberOfPixels, int microphonePin, int animationDelay) {
      int mid = numberOfPixels / 2;
      pixels[mid] = getPixelFromSound(microphonePin);
      for (int i = 1; i < MID_WIDTH; i++) {
            pixels[mid - i] = pixels[mid];
      }
      for (int i = 0; i < MID_SPREAD_COEFFICIENT; i++) {
            midSpread(pixels, mid, numberOfPixels);
      }
      delay(animationDelay);
} 

#endif