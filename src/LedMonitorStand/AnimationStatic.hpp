#include "Constants.hpp"
#include "Measurer.hpp"
#include "Animation.hpp"

#ifndef ANIMATION_STATIC
#define ANIMATION_STATIC

/**
*This 'Animation' is shows just a basic color. The Color can be adjusted using different modes, 
*using HSV, where the first button lets you adjust the hue.
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
