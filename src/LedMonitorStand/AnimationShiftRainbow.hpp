#include "Constants.hpp"
#include "Measurer.hpp"
#include "Animation.hpp"

#ifndef SHIFT_RAINBOW_ANIMATION
#define SHIFT_RAINBOW_ANIMATION


//this stores a previous input value
struct PreviousValue {
  uint8_t input;
  bool thresHoldHit;
};

class AnimationShiftRainbow : public MusicAnimation {

#define HUESPEED 1 //amount to increase hue with
#define ITERATION_PER_HUE 6 //after how many iterations to increase the hue with HUESPEED


  public:
    void update(Measurer & measurer, int adjust, int potInput) {
      MusicAnimation::update(measurer, adjust, potInput);
      if (adjust == GREEN_MODE) {
        this->minBrightness = potInput / 4;
      }

      uint8_t input = measurer.get(0);
      showColor(input);
    }

  private:
    //the sum of all items in the previousItems
    int sum = 0;

    //min brightness of the shifted items in the animation
    //changable with the slider.
    uint8_t minBrightness = 50;
    LinkedList<PreviousValue>  previousValues = LinkedList<PreviousValue>();

    uint8_t hueBias = 0;
    int hueCounter = 0;


    void showColor(uint8_t input) {
      if (previousValues.size() > 100) {
        PreviousValue toLongAgo = previousValues.shift();
        sum -= toLongAgo.input;
      }
      sum += input;
      float avg = (float) sum / (float) previousValues.size();

      uint8_t shiftInput =  input;

      boolean madeThreshold = input < avg || input < 30 || input < 200;
      if ( ! madeThreshold ) {
        shiftInput = minBrightness;
      }
      PreviousValue value = {input, true};
      previousValues.add(value);


      for (int i = RIGHT_EDGE + 1; i < LEFT_EDGE; i++) {
        leds[i] =  CHSV( getHue(i), 255, 255);
      }

      leds[RIGHT_EDGE] =  CHSV( getHue(RIGHT_EDGE), 255, shiftInput);
      leds[LEFT_EDGE] =  CHSV(getHue(LEFT_EDGE), 255, shiftInput);

      shiftRainbow();

      if (hueCounter == ITERATION_PER_HUE) {
        hueBias += HUESPEED;
        hueCounter = 0;
      }
      hueCounter++;

    }


    void shiftRainbow() {
      //start at the left side
      for ( int i = RIGHT_END; i < RIGHT_EDGE; i++) {
        int distanceToCenter = RIGHT_EDGE - i;

        PreviousValue previous = previousValues.get( previousValues.size() - distanceToCenter);

        uint8_t brightness = previous.input;
        if ( ! previous.thresHoldHit) {
          brightness = minBrightness;
        }

        leds[i] =  CHSV( getHue(i), 255, brightness);
      }

      //shift to the other side, but skip the ones at the back.
      for ( int i = LEFT_END; i >= LEFT_EDGE; i--) {
        int distanceToCenter = i - LEFT_EDGE;

        PreviousValue previous = previousValues.get( previousValues.size() - distanceToCenter);

        uint8_t brightness = previous.input;
        if ( ! previous.thresHoldHit) {
          brightness = minBrightness;
        }

        leds[i] =  CHSV( getHue(i), 255, brightness);
      }
    }

    uint8_t getHue(int index) {
      return index + hueBias;
    }
};

#endif
