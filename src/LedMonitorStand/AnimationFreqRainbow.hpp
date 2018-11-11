#include "Constants.hpp"
#include "Measurer.hpp"
#include "Animation.hpp"

#ifndef ANIMATION_FREQ_RAINBOW
#define ANIMATION_FREQ_RAINBOW

#define CENTER_LED_BRIGHTNESS_HISTORY 20

class AnimationFreqRainbow : public MusicAnimation {

  public:
    void update(Measurer & measurer , int adjust, int potInput) {
      MusicAnimation::update(measurer, adjust, potInput);

      if (adjust == GREEN_MODE) {
        beatFactor = 1 + potInput / 64;
      }
      CRGB newColor = getColor(measurer);
      setColors(newColor);
    }

    virtual void setColors(CRGB newColor)= 0;

  protected:
    uint8_t beatFactor = 12;

    CRGB getColor(Measurer & measurer) {
      int red  = (int)( (float)measurer.get(0) * 1.4f  + (float)measurer.get(1) * 0.3f);
      int blue = (int)( (float)measurer.get(6) * 1.2f);
      //mid freqs also get some input from the other bands
      int green = measurer.get(3);

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

    void shiftLeft(uint8_t origin, uint8_t end) {
      for ( int i = end; i > origin; i--) {
        leds[i].setRGB(leds[i - 1].r, leds[i - 1].g, leds[i - 1].b);
      }
    }

    void shiftRight(uint8_t origin, uint8_t end) {
      for ( int i = end; i < origin; i++) {
        leds[i].setRGB(leds[i + 1].r, leds[i + 1].g, leds[i + 1].b);
      }
    }
};

#endif
