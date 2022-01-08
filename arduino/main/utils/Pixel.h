#ifndef PIXEL_H
#define PIXEL_H

#include "utils.h"

struct Pixel {
  int red, blue, green;
};

Pixel blackPixel = {.red = 0, .blue = 0, .green = 0};

Pixel getPixelFromSound(int microphonePin) {
      Pixel result = {.red = getSound(microphonePin), .blue = getSound(microphonePin), .green = getSound(microphonePin)};
      return result;
}

#endif