#include "Constants.hpp"
#include "Measurer.hpp"
#include "Animation.hpp"

#ifndef ANIMATION_STATIC
#define ANIMATION_STATIC

/**
  This 'Animation' shows just a basic, static color. The color can be adjusted using the different adjust buttons and the slider,
  using HSV, where the first button lets you adjust the hue, second saturation, third value/brightness.
*/
class AnimationStatic : public Animation {

  private:
    //a nice red-ish pink color to start with.
    uint8_t staticHue = 5;
    uint8_t staticSaturation = 172;
    uint8_t staticBrightness = 140;

  public:

    ~AnimationStatic() {
      Serial.println("~StaticAnimaton");
    }

    void update(Measurer & measurer, int adjust, int potInput) {
      //the potInput is a number between 0 and 1023, and the brightness should be 0-255
      if (adjust == RED_MODE) {
        staticHue = potInput / 4;
      }
      else if (adjust == GREEN_MODE) {
        staticSaturation = potInput / 4;
      }
      else if ( adjust == BLUE_MODE) {
        staticBrightness = potInput / 4;
      }
      //update all leds with the new color selected by the user.
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CHSV(staticHue, staticSaturation, staticBrightness);
      }
    }
};

#endif
