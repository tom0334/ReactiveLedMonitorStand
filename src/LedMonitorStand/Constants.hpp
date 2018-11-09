#ifndef CONSTANTS
#define CONSTANTS

//PINS
///////////////////////////////////////////////////////////////////////
//used for controlling leds
#define CLK_PIN   13
#define DATA_PIN    12

//buttons
#define MODE_BUTTON_PIN 11
#define ADJUST_RED_PIN 10
#define ADJUST_GREEN_PIN 9
#define ADJUST_BLUE_PIN 8
#define ADJUST_YELLOW_PIN 7

#define NO_ADJUST -1
#define RED_MODE 0
#define GREEN_MODE 1
#define BLUE_MODE 2
#define YELLOW_MODE 3

//MSGEQ7
#define pinReset 6
#define pinStrobe 3

//For the potentiometer
#define POT_PIN A1

//MSGEQ7
#define PIN_AUDIO_IN A0


///////////////////////////////////////////////////////////////////////
//LED CONTROLL
#define NUM_LEDS    120
#define LED_TYPE    APA102
#define COLOR_ORDER BGR
CRGB leds[NUM_LEDS];

///////////////////////////////////////////////////////////////////////
//FOR THE AUDIO
#define MSGEQ7_INTERVAL ReadsPerSecond(1200)
#define MSGEQ7_SMOOTH 220 // Range: 0-255
CMSGEQ7<MSGEQ7_SMOOTH, pinReset, pinStrobe, PIN_AUDIO_IN> MSGEQ7;

///////////////////////////////////////////////////////////////////////
//CUSTOM LED INFO
//59 and 60 are the center two
#define RIGHT_EDGE  58
#define LEFT_EDGE 61

//the first 17 and last 17 leds are unused, since they are on the back. They are only used for the solid colors.
#define RIGHT_END 17
#define LEFT_END  NUM_LEDS - 17

#define FRONT_LEFT  LEFT_END - 12
#define FRONT_RIGHT  RIGHT_END + 12


#endif
