#include "Constants.hpp"
#include "Measurer.hpp"
#include "Animation.hpp"
#include "AnimationFreq.hpp"

#ifndef ANIMATION_FREQ_MIDLE_OUT
#define ANIMATION_FREQ_MIDLE_OUT

#define CENTER_LED_BRIGHTNESS_HISTORY 20
#define CENTER_LED_MIN_BRIGHTNESS 128

/**
 * A freq animation that moves from the midle out, and shows white leds in the center. 
 * The brightness of the white leds is dependent on the prevous inputs.
 */
class AnimationFreqMidleOut: public AnimationFreq {

  public:
    //OVERRIDE
    void setColors(CRGB newColor) {
      leds[RIGHT_EDGE] =  newColor;
      leds[LEFT_EDGE] =  newColor;
      shiftLeft(LEFT_EDGE, LEFT_END);
      shiftRight(RIGHT_EDGE, RIGHT_END);
      updateCenterLeds();
    }


  private:
    /**
      aproximation of the brightness of a a led, accurate enough for these purposes.
      see the wikipedia page on relative luminance for more info
    */
    uint8_t brightness(CRGB & c) {
      return floor(0.299f * (float) c.r + 0.587 * (float) c.g  + 0.114 * (float) c.b);
    }

    /**
      this updates the brightness of the center leds, by computing the brightness of leds further from the center,
      and then calucalting the average brightness of those, plus some constant factor.
      
      The amount of leds to consider is determined by the CENTER_LED_BRIGHTNESS_HISTORY
    */
    void updateCenterLeds() {
      int sum = 0;
      for (int i = LEFT_EDGE; i < LEFT_EDGE + CENTER_LED_BRIGHTNESS_HISTORY; i++) {
        sum += brightness( leds[i]);
      }
      uint8_t avg = sum / CENTER_LED_BRIGHTNESS_HISTORY;

      //min brightness is 128
      uint8_t result = min( avg / 2 + CENTER_LED_MIN_BRIGHTNESS , 255);
      for (int i = RIGHT_EDGE + 1; i < LEFT_EDGE; i++) {
        leds[i] = CHSV(0, 0, result);
      }
    }

};

#endif
