#include "Constants.hpp"
#include "Measurer.hpp"

#ifndef ANIMATION
#define ANIMATION


/**
* A basic Animation class that has an update function. The update function will be called very often,
* so the logic inside it should be as fast as possible. In it, the colors of the leds should be updated.
* This is done by using the global leds array. FastLed.update() does NOT need to be called, that is done in
* the main program.
*/
class Animation {
  public:
    virtual void update(Measurer & measurer, int adjust, int potInput) = 0;
    virtual ~Animation() {
      Serial.println("~baseAnimation");
    }
};

/**
 * MusicAnimation class that also updates the Measurer when the red Adjust button is selected.
 */
class MusicAnimation : public Animation {
  public:
    void update(Measurer & measurer, int adjust, int potInput) {
      if (adjust == RED_MODE) {
        measurer.setSamples(1+ potInput / 32);
      }
    }
    virtual ~MusicAnimation() {
      Serial.println("~MusicAnimation");
    }
};

#endif
