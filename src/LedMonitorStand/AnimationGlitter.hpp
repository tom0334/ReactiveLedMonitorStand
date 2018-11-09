#include "Constants.hpp"
#include "Measurer.hpp"
#include "Animation.hpp"

#ifndef ANIMATION_GLITTER
#define ANIMATION_GLITTER

class AnimationGlitter : public MusicAnimation {
#define GLITTER_SIZE 1
  private:
    bool showing = false;
    uint8_t start = 0;
    uint8_t end = 0;
    uint8_t hue = 0;

  public:
    void update(Measurer & measurer , int adjust, int potInput) {
      MusicAnimation::update(measurer, adjust, potInput);
      int bass  = (int)( (float)measurer.get(0) * 1.4f  + (float)measurer.get(1) * 0.3f);
      int high = (int)( (float)measurer.get(6) * 1.2f);
      //mid freqs also get some input from the other bands
      int mid = measurer.get(3);

      if (bass > mid && bass > high && bass > 150) {
        if (! showing) {
          uint8_t randomSpot = random8(FRONT_RIGHT, FRONT_LEFT);
          start = randomSpot;
          end = randomSpot + GLITTER_SIZE;
          hue = random8();
          showing = true;
        }
      } else {
        showing = false;
      }

      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB(0, 0, 0);
      }

      for (int i = start; i < end; i++) {
        leds[i] = CHSV(hue, 255, 255);
      }
    }
    ~AnimationGlitter() {
      Serial.println("~AnimationGlitter");
    }
};

#endif
