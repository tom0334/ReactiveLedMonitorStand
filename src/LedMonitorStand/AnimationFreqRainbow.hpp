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
      CRGB shiftColor = getColor(measurer);

      leds[RIGHT_EDGE] =  shiftColor;
      leds[LEFT_EDGE] =  shiftColor;
      shift();
      updateCenterLeds();
    }

  private:
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
        sum+= brightness( leds[i]);
      }
      uint8_t avg = sum / CENTER_LED_BRIGHTNESS_HISTORY;

      //min brightness is 128
      uint8_t result = min( avg/2 + 128 ,255);
      for (int i = RIGHT_EDGE + 1; i < LEFT_EDGE; i++) {
        leds[i] = CHSV(0, 0, result);
      }
    }

    //Shifts the center color to the sides.
    //Note that the back items are skipped, because they are at the back of the stand
    void shift() {
      // at the right end. Copy that
      for ( int i = RIGHT_END; i < RIGHT_EDGE; i++) {
        leds[i].setRGB(leds[i + 1].r, leds[i + 1].g, leds[i + 1].b);
      }
      //shift to the other side, but skip the ones at the back.
      for ( int i = LEFT_END; i > LEFT_EDGE; i--) {
        leds[i].setRGB(leds[i - 1].r, leds[i - 1].g, leds[i - 1].b);
      }
    }
};

#endif
