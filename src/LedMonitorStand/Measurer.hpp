#include "Constants.hpp"

#ifndef MEASURER
#define MEASURER


//TODO; move the measurerer to the MusicAnimation
/**
  Measueres input from the MSGEQ7, and keeps it in its internal data structure.
  This class does smoothing by using the average from a number of samples,set this using the setSamples function.
  Call the measure function in loop().
*/
class Measurer {
  private:
    uint8_t samples = 10;
    uint8_t data[7];

  public:
    void  measure() {
      long sum[7] = {};

      int sample = 0;
      while (sample < this->samples) {
        bool newReading = MSGEQ7.read(MSGEQ7_INTERVAL);
        if ( ! newReading) {
          continue;
        }

        sample++;
        for (int i = 0; i < 7; i++) {
          uint8_t result = MSGEQ7.get(i);
          result = mapNoise(result);

          //hacky corretion for the fact that the 4th band is a little broken, it has a noise of around 120.
          if (i == 4) {
            if (result > 120) {
              result -= 120;
              result *= 2;
            }
            else {
              result = 0;
            }
          }
          sum[i] += result;
        }
      }
      //set the new data to the average from the number of samples
      for (int i = 0; i < 7; i++) {
        uint8_t result = sum[i] / this->samples;
        this->data[i] = result;
        //Serial.println();
        //Serial.print(result);
        //Serial.print(" , ");
      }
    }

    uint8_t get(uint8_t band) {
      return data[band];
    }

    void setSamples(uint8_t samples) {
      this->samples = samples;
    }
};

#endif
