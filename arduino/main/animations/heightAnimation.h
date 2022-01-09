#ifndef HEIGHT_ANIMATION_H
#define HEIGHT_ANIMATION_H

#include "../utils/Pixel.h"

#define CHANGE_PERCENT 70

int animate = 0;
int maxHeight;
int currentHeight = 0;
Pixel pixel;
int increment = 1;

int normalizeToNumberOfPins(int pixelSum, int numberOfPixels) {
      return numberOfPixels * pixelSum / (3 * 256);
}

int tryGetAPixel(int microphonePin) {
      int pixelSum = 0;
      Pixel searchedPixel;
      while (pixelSum < 100) {
            searchedPixel = getPixelFromSound(microphonePin);
            pixelSum = searchedPixel.red + searchedPixel.green + searchedPixel.blue;
      }
      pixel = { .red = (searchedPixel.red * CHANGE_PERCENT + (100 - CHANGE_PERCENT) * pixel.red) / 100,
            .blue = (searchedPixel.blue * CHANGE_PERCENT + (100 - CHANGE_PERCENT) * pixel.blue) / 100,
            .green = (searchedPixel.green * CHANGE_PERCENT + (100 - CHANGE_PERCENT) * pixel.green) / 100
      };
      return pixelSum;
}

int makeHeightLonger(int height, int numberOfPixels) {
      int result = 7 * height / 3;
      if (result < numberOfPixels) {
            return result;
      }
      return numberOfPixels;
}

void resetLeds(Pixel pixels[], int numberOfPixels) {
      for (int i = 0; i < numberOfPixels; i++) {
            pixels[i] = blackPixel;
      }
}

void playPixelsHeight(Pixel pixels[], int numberOfPixels, int microphonePin, int animationDelay) {
      //resetLeds(pixels, numberOfPixels);
      if (animate == 0) {
            int pixelSum = tryGetAPixel(microphonePin);
            maxHeight = makeHeightLonger(normalizeToNumberOfPins(pixelSum, numberOfPixels), numberOfPixels);
            increment = 1;
            animate = 1;
            currentHeight = 0;
      }
      pixels[currentHeight] = pixel;
      currentHeight += increment;
      if (currentHeight == maxHeight) {
            resetLeds(pixels, numberOfPixels);
            animate = 0;
      }
      delay(animationDelay / 5);
} 

#endif