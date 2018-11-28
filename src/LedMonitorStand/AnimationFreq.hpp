#include "Constants.hpp"
#include "Measurer.hpp"
#include "Animation.hpp"

#ifndef ANIMATION_FREQ_RAINBOW
#define ANIMATION_FREQ_RAINBOW


/**
   ABSTRACT class that provides common functionality for animations that
   respond to multiple frequencies with different colors,
   and have a bonus for the bass to show the beat more.

   It handles updating all the parameters, shifting and figuring out the correct color + intensity

   It has a raw and a enhanced mode, which changes the way the colors are mapped. 

   NOTE: THE BLUE BUTTON IS RESERVED FOR TOGLING THE CLEAN MODE. DO NOT USE IT FOR THE ANIMATION.

*/
class AnimationFreq : public MusicAnimation {


  public:
    void update(Measurer & measurer , int adjust, int potInput) {
      MusicAnimation::update(measurer, adjust, potInput);

      if (adjust == BLUE_MODE) {
        this->enhancedMode = potInput >= 512;
      }

      if (adjust == GREEN_MODE) {
        beatFactor = 1 + potInput / 64;
      }
      CRGB newColor = getColor(measurer);
      setColors(newColor);
    }

    /*
       This should show the actual colors on the ledstrip.
    */
    virtual void setColors(CRGB newColor) = 0;

  protected:
    uint8_t beatFactor = 12;


    CRGB getColor(Measurer & measurer) {
      if (this->enhancedMode) {
        return getEnhancedColor(measurer);
      }
      else return getRawColor(measurer);
    }

    /**
       Shifts all the leds to the left once, from te origin. The leds after end are unchanged.
    */
    void shiftLeft(uint8_t origin, uint8_t end) {
      for ( int i = end; i > origin; i--) {
        leds[i].setRGB(leds[i - 1].r, leds[i - 1].g, leds[i - 1].b);
      }
    }

    /**
       Same, but for shifting to the right.
    */
    void shiftRight(uint8_t origin, uint8_t end) {
      for ( int i = end; i < origin; i++) {
        leds[i].setRGB(leds[i + 1].r, leds[i + 1].g, leds[i + 1].b);
      }
    }

  private:
  //controls if the raw or the enhanced colors are used.
    boolean enhancedMode = true;

    /**
        Raw colors. This simply maps the input from the bass, mid and highs to RGB, without any attempt to bring out the beat more
        Returns the new color after this input.
    */
    CRGB getRawColor(Measurer & measurer) {
      //Bass has a boosted inputs to bring out the beat a bit more.
      uint8_t red  = measurer.get(0);
      int green = measurer.get(3);
      uint8_t blue = measurer.get(6);
      return CRGB(red, green, blue);
    }

    /**
      Gets a color for the current measured values. It does that by combining 2 colors out of RGB,
      corresponding to which frequency band has the highest signal currently. The lowest is put at zero,
      to make the result look less white.

      It also has a changeable beatFactor, which makes the brightness lower if there is no bass, to bring out the beat more
    */
    CRGB getEnhancedColor(Measurer & measurer) {
      //Bass has a boosted inputs to bring out the beat a bit more.
      int red  = (int)( (float)measurer.get(0) * 1.4f  + (float)measurer.get(1) * 0.3f);
      //highs have a boosted input because the higs and lows bleed into the mids a bit.( without this there would be very litle blue)
      int blue = (int)( (float)measurer.get(6) * 1.2f);
      //mid freqs also get some input from the other bands
      int green = measurer.get(3);

      //find the lowest and put that at zero
      if (red < green  && red < blue) {
        red = 0;
        green /= beatFactor;
        blue /= beatFactor;
      }
      else if (green < red && green < blue) {
        green = 0;
      }
      else {
        blue = 0;
      }
      return CRGB(min(255, red), min(255 / beatFactor, green), min(255 / beatFactor, blue));
    }

};

#endif
