#include "Constants.hpp"
#include "Measurer.hpp"
#include "Animation.hpp"

#ifndef SHIFT_RAINBOW_ANIMATION
#define SHIFT_RAINBOW_ANIMATION


//this stores a previous input value, used to determine if the brightness should be boosted.
struct PreviousValue {
  uint8_t input;
  bool thresHoldHit;
};

/**
A classic RGB rainbow animation that responds to the beat. It does so by keeping an average of the last 100 input values.
If the input is larger than the average, then it is probably a beat, so the brightness should be upped for this input.
*/
class AnimationShiftRainbow : public MusicAnimation {

#define HUESPEED 1 //amount to increase hue with every update
#define ITERATION_PER_HUE 6 //after how many iterations to increase the hue with HUESPEED


  public:
    void update(Measurer & measurer, int adjust, int potInput) {
      MusicAnimation::update(measurer, adjust, potInput);

      if (adjust == GREEN_MODE) {
        //potInput is an int from 0 to 1023, brightness should be from 0 to 255
        this->minBrightness = potInput / 4;
      }

      //0 is the bass
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
    //the amount of updates that were done after the hue was changed.
    int hueCounter = 0;

    /**
    Shows a color according to an input, and then shifts it to the sides.
    */
    void showColor(uint8_t input) {
      //the list size is capped at 100
      if (previousValues.size() > 100) {
        PreviousValue toLongAgo = previousValues.shift();
        //removes the first value and subtract it from the sub
        sum -= toLongAgo.input;
      }
      sum += input;
      float avg = (float) sum / (float) previousValues.size();

      boolean madeThreshold = input > avg ||  input > 200;
      
      //add the new value
      PreviousValue value = {input, madeThreshold};
      previousValues.add(value);

      //If the ThresHold was not reached, the minBrightness is shown
      //the MinBrightness is choosable by the user.
      if ( ! madeThreshold ) {
        input = minBrightness;
      }

      //set the center leds to the hue at max brightness.
      for (int i = RIGHT_EDGE + 1; i < LEFT_EDGE; i++) {
        leds[i] =  CHSV( getHue(i), 255, 255);
      }

      //set the brightness of the edges to the input given.
      leds[RIGHT_EDGE] =  CHSV( getHue(RIGHT_EDGE), 255, input);
      leds[LEFT_EDGE] =  CHSV(getHue(LEFT_EDGE), 255, input);

      //shifts to both sides
      shiftRainbow();

      //adjust the hue
      if (hueCounter == ITERATION_PER_HUE) {
        hueBias += HUESPEED;
        hueCounter = 0;
      }
      hueCounter++;

    }


    // Shifts the rainbow animation one to the left and one to the right from the center.
    // Does so through the previousValues list, because there is no conversion from RGB to HSV in FastLed.
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
