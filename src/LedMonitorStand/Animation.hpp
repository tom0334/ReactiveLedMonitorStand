#include "Constants.hpp"
#include "Measurer.hpp"

#ifndef ANIMATION
#define ANIMATION


//Base animation class
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
