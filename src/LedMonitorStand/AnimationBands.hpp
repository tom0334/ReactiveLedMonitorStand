#include "Constants.hpp"
#include "Measurer.hpp"
#include "Animation.hpp"

#ifndef ANIMATION_BANDS
#define ANIMATION_BANDS

/**
   Shows a classic visualizer animation.

   The color and the intensity correspond to the sound.
*/

class Region {
  private:
    uint8_t start;
    uint8_t end;
    LinkedList<uint8_t> previousInputs = LinkedList<uint8_t>();
    float sum = 0;

  public:
    //empty constructor for in use of arrays
    Region() {}

    ~Region() {
      Serial.println("~Region");
      previousInputs.clear();
      //since previousInputs is on the stack, the integers should be deleted.
    }

    Region(uint8_t start, uint8_t end) {
      this->start = start;
      this->end = end;

      Serial.print("Created region:");
      Serial.print(start);
      Serial.print(",");
      Serial.println(end);
    }

    void show(CHSV color) {
      if (previousInputs.size() > 12) {
        float toLongAgo = this->previousInputs.shift();
        this->sum -= toLongAgo;
      }
      sum += color.v;
      float avg = this->sum / (float) previousInputs.size();
      this->previousInputs.add(color.v);

      for (int i = start ; i <= end; i++) {
        uint8_t brightness =  floor(avg);
        leds[i] = CHSV( color.h, 255, brightness);
      }
    }

    uint8_t getStart() {
      return start;
    }
    uint8_t getEnd() {
      return end;
    }

};


class AnimationBands : public MusicAnimation {

    Region ** regions = new Region*[7];

  public:
    AnimationBands() {
      Serial.println("Start creating animation");
      int startLed = FRONT_RIGHT;
      int endLed = FRONT_LEFT;

      int amountOfLeds =   endLed - startLed;

      int smallRegionSize = amountOfLeds / 7;
      int remainder = amountOfLeds % 7;

      this->regions[0] = new Region(startLed, startLed + smallRegionSize);

      //create the regions. Note that the last one has the remainder added to it, so it is a little larger than the others.
      for (int i = 1; i < 7; i++) {
        int start = regions[i - 1]->getEnd();
        int end = start + smallRegionSize;
        if (i == 6)end  += remainder;
        this->regions[i] = new Region(start, end );
      }

    }

    ~AnimationBands() {
      Serial.println("~AnimationBands");
      for (int i = 0; i < 7; i++) {
        delete this->regions[i];
      }
      delete[] regions;
    }


    void update(Measurer & measurer, int adjust, int potInput) {
      MusicAnimation::update(measurer, adjust, potInput);
      for (int i = 0; i < 7; i++) {
        int reverseFreg = 6 - i;
        CHSV color = CHSV(reverseFreg * 36, 255, measurer.get(reverseFreg));
        this->regions[i]->show(color);
      }
    }

};

#endif
