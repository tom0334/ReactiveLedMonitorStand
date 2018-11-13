#include "Constants.hpp"
#include "Measurer.hpp"
#include "Animation.hpp"
#include "AnimationFreq.hpp"

#ifndef ANIMATION_FREQ_FROM_LEFT
#define ANIMATION_FREQ_FROM_LEFT

/**
   A AnimationFreq that moves from the left side to the right side. 
*/
class AnimationFreqFromLeft: public AnimationFreq {

  public:
    void setColors(CRGB newColor) {
      leds[FRONT_LEFT] =  newColor;
      shiftRight(FRONT_LEFT, FRONT_RIGHT);
    }
};

#endif
