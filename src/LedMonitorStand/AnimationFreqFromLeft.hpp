#include "Constants.hpp"
#include "Measurer.hpp"
#include "Animation.hpp"
#include "AnimationFreqRainbow.hpp"

#ifndef ANIMATION_FREQ_FROM_LEFT
#define ANIMATION_FREQ_FROM_LEFT

class AnimationFreqFromLeft: public AnimationFreqRainbow {

  public:
    void setColor(CRGB newColor) {
      leds[FRONT_LEFT] =  newColor;
      shiftRight(FRONT_LEFT, FRONT_RIGHT);
    }
};

#endif
