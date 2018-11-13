#include "Constants.hpp"
#include "Measurer.hpp"
#include "Animation.hpp"
#include "AnimationFreq.hpp"

#ifndef ANIMATION_FREQ_FROM_BACK
#define ANIMATION_FREQ_FROM_BACK

/**
   A AnimationFreq that moves from the back left to the right back side. 
*/
class AnimationFreqFromBack: public AnimationFreq {

  public:
    void setColors(CRGB newColor) {
      leds[LEFT_END] =  newColor;
      shiftRight(LEFT_END, RIGHT_END);
    }
};

#endif
