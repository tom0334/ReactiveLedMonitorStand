#ifndef REGION
#define REGION

/**
   A Region represents a part of the led strip, that can display a certain color. The region class also
   does smoothing of previous inputs. It is used by the bandsAnimation.
*/
#define REGION_SMOOTH_SAMPLES 12

class Region {
  private:
    uint8_t start;
    uint8_t end;
    LinkedList<uint8_t> previousInputs = LinkedList<uint8_t>();
    float sum = 0;

  public:
    //empty constructor for in use of arrays, these regions will be deleted anyyway.
    Region() {}

    ~Region() {
      Serial.println("~Region");
      previousInputs.clear();
      //since previousInputs is on the stack, the integers should be deleted.
    }

    /**
     * Constructor that is used when you want to create an actual region.
     * The start and end are inclusive, they are also contained in the region.
     */
    Region(uint8_t start, uint8_t end) {
      this->start = start;
      this->end = end;

      Serial.print("Created region:");
      Serial.print(start);
      Serial.print(",");
      Serial.println(end);
    }

    /**
     * Shows a HSV color on all leds in the region, with smoothing!
     * The smoothing means that it just shows the average of the last 12 inputs.
     */
    void show(CHSV color) {
      if (previousInputs.size() > REGION_SMOOTH_SAMPLES) {
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

#endif
