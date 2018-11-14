
# ReactiveLedMonitorStand
Arduino source code for a monitor stand with leds attached to it. The leds react to 3.5mm audio input with animations, using a MSGQ7 chip.

### Hardware setup
The stand itself is created using a IKEA wall shelf, and some IKEA capita kitchen legs. It has a Arduino UNO and some controls mounted to the bottom to control the LEDS. The Arduino is mounted on the right side, and LED 0 is located on the back right side of the stand. The type of LEDS used is the APA 102, 120 LEDS on a 2m strip. 

### Controls
The project uses a set of 5 buttons to adjust different options and switch between different LED modes. To adjust an option, a sliding potentiometer is used. To see to which pins the buttons are connected, see the constants.hpp file.

### Modes
Currently, the system supports 7 modes:
 -  A static mode, that shows a single color across all leds. The adjust buttons lets you adjust the Hue, Saturation and brightness of the color displayed.
 - Frequency respond #1: a mode where the color of the leds is dependent on the loudest frequency band. The previous value is shifted to the right each time the animation is updated. The first adjust button changes the speed/amount of shifts per second. The second adjust lets you adjust the beatfactor, or the boost that is given to brigthness when there is a bass tone. This makes the beat stand out more.
 - Frequency respond #2: Similar to frequency respond #1, but the lights start at the back instead of the front, meaning they go around the corner.
 - Frequency respond #3 Similar to the other frequency respond modes, but this time shifting happens in two directions starting from the center. The center LEDS are white, and their brightness changes according to the previous input values.
 - Rainbow shift : A classic RGB rainbow animation that responds to the beat/bass. It shifts from the center like Frequency respond #3, but the color is not dependent on the frequency.
 - Bands visualiser: shows the different frequency bands supported by the MSGQ7 in different colors. The brightness responds to the intensity of the corresponding band. The resulting brightness is the average of a certain amount of previous inputs, to smooth it out a bit. The amount of sampless to take can be changed with the first adjust button.
 - Glitter animation: turns on a random set of adjacent LEDSresponding to the beat. 
