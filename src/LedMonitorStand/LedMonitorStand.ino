#include <FastLED.h>
#include <LinkedList.h>
#include <MSGEQ7.h>
#include "Animation.hpp"
#include "Measurer.hpp"
#include "Constants.hpp"

#include "AnimationBands.hpp"
#include "AnimationShiftRainbow.hpp"
#include "AnimationFreqFromLeft.hpp"
#include "AnimationFreqMidleOut.hpp"
#include "AnimationFreqFromBack.hpp"
#include "AnimationGlitter.hpp"
#include "AnimationStatic.hpp"

///////////////////////////////////////////////////////////////////////
uint8_t masterBrightness = 255;
void setup() {
  MSGEQ7.begin();
  Serial.begin(9600);
  Serial.println("Welcome!");

  pinMode(MODE_BUTTON_PIN, INPUT_PULLUP);
  pinMode(ADJUST_RED_PIN, INPUT_PULLUP);
  pinMode(ADJUST_GREEN_PIN, INPUT_PULLUP);
  pinMode(ADJUST_BLUE_PIN, INPUT_PULLUP);
  pinMode(ADJUST_YELLOW_PIN, INPUT_PULLUP);

  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE, DATA_PIN, CLK_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(masterBrightness);
  //disable dithering, as that doesn't look nice with low brigthness settings in some animations.
  //it is better to just show a slightly wrong color instead.
  FastLED.setDither( 0 );
}
///////////////////////////////////////////////////////////////////////

/**
   Respond to button presses, and update the current animation.

   The mode button changes which animation is currently displayed.

   The yellow button is a global brightness setting.
   Brightness is changed with the slider.

   The other buttons are 'adjust' buttons, they adjust a specific setting within an animation.
   The actual value is changed by sliding the slider.

*/

uint8_t mode = 0;
uint8_t adjust = 0;
Measurer measurer = Measurer();
Animation * currentAnimation =  new AnimationStatic();

void loop() {
  //update the music measurer.
  measurer.measure();
  //read the current value from the potentioMeter. Value is between 0 and 1024.
  int potInput = analogRead(POT_PIN);

  if (digitalRead(ADJUST_RED_PIN) == HIGH) {
    adjustButtonPressed(RED_MODE);
  }
  else if (digitalRead(ADJUST_GREEN_PIN) == HIGH) {
    adjustButtonPressed(GREEN_MODE);
  }
  else if (digitalRead(ADJUST_BLUE_PIN) == HIGH) {
    adjustButtonPressed(BLUE_MODE);
  }
  else if (digitalRead(ADJUST_YELLOW_PIN) == HIGH) {
    adjustButtonPressed(YELLOW_MODE);
  }

  if (adjust == YELLOW_MODE) {
    masterBrightness = potInput / 4;
    FastLED.setBrightness(masterBrightness);
  }
  if (digitalRead(MODE_BUTTON_PIN) == HIGH) {
    Serial.println("Changing mode");
    modeButtonPressed();
  }

  currentAnimation->update(measurer, adjust, potInput);
  FastLED.show();
}


#define NUM_MODES 6
void modeButtonPressed() {
  mode++;
  if (mode >= NUM_MODES) {
    mode = 0;
  }
  adjust = NO_ADJUST;
  //clear all leds
  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV(0, 0, 0);
  }

  Serial.println("trying to delete...");
  delete currentAnimation;

  Serial.println("Deleted current animation!");

  //check which to display
  if (mode == 0) {
    currentAnimation = new AnimationStatic();
  }
  else if (mode == 1) {
    currentAnimation = new AnimationFreqFromLeft();
  }
  else if (mode == 2) {
    currentAnimation = new AnimationFreqFromBack();
  }
  else if (mode == 3) {
    currentAnimation = new AnimationFreqMidleOut();
  }
  else if (mode == 4) {
    currentAnimation = new AnimationShiftRainbow();
  }
  else if (mode == 5) {
    currentAnimation = new AnimationBands();
  }
  else if (mode == 6) {
    currentAnimation = new AnimationGlitter();
  }
  else {
    Serial.println("UNKNOWN ANIMATION ERROR. PROGRAM WILL CRASH!");
  }
  delay(500);
}

//Whenever a Adjust button has been pressed, this function sets the correct adjust mode
void adjustButtonPressed(uint8_t which) {
  adjust = which;
  Serial.print("Adjust button pressed:");
  Serial.println(which);
  delay(500);
}
