#include "Constants.hpp"
#include "Measurer.hpp"
#include "Animation.hpp"
#include "AnimationFreqRainbow.hpp"

#ifndef ANIMATION_FREQ_MIDLE_OUT
#define ANIMATION_FREQ_MIDLE_OUT

class AnimationFreqMidleOut: public AnimationFreqRainbow {

  public:
    void setColors(CRGB newColor) {
      leds[RIGHT_EDGE] =  newColor;
      leds[LEFT_EDGE] =  newColor;
      shiftLeft(LEFT_EDGE,LEFT_END);
      shiftRight(RIGHT_EDGE,RIGHT_END);
      updateCenterLeds();
    }


  private:
    //aproximation of the brightness of a led, not very accurate but it works well enough for these purposes.
    //It's an aproximation of this: Y = 0.2126 R + 0.7152 G + 0.0722 B
    uint8_t brightness(CRGB & c) {
      return floor(0.299f * (float) c.r + 0.587 * (float) c.g  + 0.114 * (float) c.b);
    }

    //this updates the brightness of the center leds.
    //it is dependent on the brightness of the last few leds, determined by the
    // CENTER_LED_BRIGHTNESS_HISTORY
    void updateCenterLeds() {
      int sum = 0;
      for (int i = LEFT_EDGE; i < LEFT_EDGE + CENTER_LED_BRIGHTNESS_HISTORY; i++) {
        sum += brightness( leds[i]);
      }
      uint8_t avg = sum / CENTER_LED_BRIGHTNESS_HISTORY;

      //min brightness is 128
      uint8_t result = min( avg / 2 + 128 , 255);
      for (int i = RIGHT_EDGE + 1; i < LEFT_EDGE; i++) {
        leds[i] = CHSV(0, 0, result);
      }
    }

};

#endif
