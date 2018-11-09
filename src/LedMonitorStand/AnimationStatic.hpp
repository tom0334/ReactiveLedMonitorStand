#include "Constants.hpp"
#include "Measurer.hpp"
#include "Animation.hpp"

#ifndef ANIMATION_STATIC
#define ANIMATION_STATIC

class AnimationStatic : public Animation {

  private:
    uint8_t staticHue = 5;
    uint8_t staticSaturation = 172;
    uint8_t staticBrightness = 140;

  public:

    ~AnimationStatic() {
      Serial.println("~StaticAnimaton");
    }


    void update(Measurer & measurer, int adjust, int potInput) {
      if (adjust == RED_MODE) {
        staticHue = potInput / 4;
      }
      else if (adjust == GREEN_MODE) {
        staticSaturation = potInput / 4;

      }
      else if ( adjust == BLUE_MODE) {
        staticBrightness = potInput / 4;
      }
      else if (adjust == YELLOW_MODE) {
        staticHue = 5;
        staticSaturation = 172;
        staticBrightness = 140;
      }

      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CHSV(staticHue, staticSaturation, staticBrightness);
      }
    }
};

#endif
