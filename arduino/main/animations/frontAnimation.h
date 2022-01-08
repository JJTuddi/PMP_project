#ifndef FRONT_ANIMATION_H
#define FRONT_ANIMATION_H

#include "../utils/Pixel.h"

void playPixelsFront(Pixel pixels[], int numberOfPixels, int microphonePin, int animationDelay) {
      int getSound(int microphonePin);
      for(int i = numberOfPixels - 1; i > 0; i--) {
            pixels[i] = pixels[i - 1];
      }
      pixels[0] = getPixelFromSound(microphonePin);
      delay(animationDelay);
} 

#endif