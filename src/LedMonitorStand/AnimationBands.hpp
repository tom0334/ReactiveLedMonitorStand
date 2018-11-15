#include "Constants.hpp"
#include "Measurer.hpp"
#include "Animation.hpp"
#include "Region.hpp"

#ifndef ANIMATION_BANDS
#define ANIMATION_BANDS

/**
   Shows a classic visualizer animation with the different bands available on the MSGEQ7. Each band
   has its own color, where the brightness corresponds to the input of the band, with some smoothing.
*/
class AnimationBands : public MusicAnimation {

  //Each band is its own region. Note the double star!
  Region ** regions = new Region*[7];

  public:
    //The constructor divides the ledstrip into regions.
    AnimationBands() {
      Serial.println("Start creating animation");
      //go from left to right, because the right led is led zero 
      int startLed = FRONT_RIGHT;
      int endLed = FRONT_LEFT;

      int amountOfLeds =   endLed - startLed;

      //all regions should be this size, but there is some extra. The extra is added to the last one, which is the bass
      //why? I think a larger bass region looks nice.
      int smallRegionSize = amountOfLeds / 7;
      int remainder = amountOfLeds % 7;

      //create the first one outside the loop. The first paramter is the start of the region, the second the end.
      this->regions[0] = new Region(startLed, startLed + smallRegionSize);

      //create the regions. Note that the last one has the remainder added to it, so it is a little larger than the others.
      for (int i = 1; i < 7; i++) {
        //the start of the next region is the end of the previous one.
        int start = regions[i - 1]->getEnd();
        int end = start + smallRegionSize;
        //the last one is larger.
        if (i == 6)end  += remainder;
        this->regions[i] = new Region(start, end );
      }

    }

    ~AnimationBands() {
      Serial.println("~AnimationBands");
      //because it is an array of pointers, we need to delete both the array and the values.
      for (int i = 0; i < 7; i++) {
        delete this->regions[i];
      }
      delete[] regions;
    }


    void update(Measurer & measurer, int adjust, int potInput) {
      MusicAnimation::update(measurer, adjust, potInput);
      //since the leds are from right to left and we want the bass band at the left,
      //the freq needs to be reversed.
      for (int i = 0; i < 7; i++) {
        int reverseFreg = 6 - i;
        CHSV color = CHSV(reverseFreg * 36, 255, measurer.get(reverseFreg));
        this->regions[i]->show(color);
      }
    }

};

#endif
