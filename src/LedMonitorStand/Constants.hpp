#ifndef CONSTANTS
#define CONSTANTS
//This file contains constants like which pins to use, the amount of leds and where 
//the center of the led strip is.

//PINS
///////////////////////////////////////////////////////////////////////
//used for controlling leds
#define CLK_PIN 13
#define DATA_PIN 12

//buttons
#define MODE_BUTTON_PIN 11
#define ADJUST_RED_PIN 10
#define ADJUST_GREEN_PIN 9
#define ADJUST_BLUE_PIN 8
#define ADJUST_YELLOW_PIN 7

//MSGEQ7
#define pinReset 6
#define pinStrobe 3

//For the potentiometer that changes settings according to the adjust mode:
#define POT_PIN A1

//MSGEQ7
#define PIN_AUDIO_IN A0

///////////////////////////////////////////////////////////////////////
//LED CONTROL
#define NUM_LEDS 120
#define LED_TYPE APA102
#define COLOR_ORDER BGR

//the leds array. Change the CRGB values to set new led colors in the animations
CRGB leds[NUM_LEDS];

///////////////////////////////////////////////////////////////////////
//FOR THE AUDIO
#define MSGEQ7_INTERVAL ReadsPerSecond(1200)
#define MSGEQ7_SMOOTH 220 // Range: 0-255
CMSGEQ7<MSGEQ7_SMOOTH, pinReset, pinStrobe, PIN_AUDIO_IN> MSGEQ7;

///////////////////////////////////////////////////////////////////////
//CUSTOM LED INFO

//Since the leds are placed in a almost complete rectangle, some locations are defined here
//to make the animation code easier to understand. 

//The back sides is 17 leds long.
//The sides are 12 leds long.
//The front is the rest of the leds.

//59 and 60 are the center two leds. The edges are the first leds that have a color other than
// white in the animations that start from the center and shift outwards.
#define RIGHT_EDGE  58
#define LEFT_EDGE 61

//the first 17 and last 17 leds are unused in some of the animations, 
//since they are on the back. Led 17 is on the right side of the stand. 
#define RIGHT_END 17
#define LEFT_END  NUM_LEDS - 17

//The front leds are in the corner.
#define FRONT_LEFT  LEFT_END - 12
#define FRONT_RIGHT  RIGHT_END + 12

//MODES
///////////////////////////////////////////////////////////////////////
//These are just constants for the different adjust modes. The colors correspond
//to the different button colors.
#define NO_ADJUST -1
#define RED_MODE 0
#define GREEN_MODE 1
#define BLUE_MODE 2
#define YELLOW_MODE 3


#endif
