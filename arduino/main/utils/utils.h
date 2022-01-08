#ifndef UTILS_H
#define UTILS_H

#define MAX_SAMPLING_SOUND 128
#define ACTUAL_PERCENT 50


const int aplifier = 256 / MAX_SAMPLING_SOUND;
int previous = 0;

int normalize(int value) {
      return aplifier * value;
}

int applyFilter(int actualSound) {
      return (actualSound * ACTUAL_PERCENT + previous * (100 - ACTUAL_PERCENT)) / 100;
}

int getSound(int microphonePin) {
      int sampleResult = 0;
      for (int i = 0; i < MAX_SAMPLING_SOUND; i++) {
            sampleResult += digitalRead(microphonePin);
      }
      return normalize(applyFilter(MAX_SAMPLING_SOUND - sampleResult));
}

#endif