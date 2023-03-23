/* Encoder Library - TwoKnobs Example
 * http://www.pjrc.com/teensy/td_libs_Encoder.html
 *
 * This example code is in the public domain.
 */

#include <Encoder.h>

// Change these pin numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability
/*Interrupt Pins: 
Arduino Due	All Digital Pins	13
Arduino Uno	2, 3	13
Arduino Leonardo	0, 1, 2, 3	13
Arduino Mega	2, 3, 18, 19, 20, 21	13
*/
Encoder knobLeft(7, A0);
double revs = 0.0;
const int pointsPerRev = 1296;


void setup() {
  Serial.begin(9600);
  delay(1000);
  Serial.println("Encoder Test:");
}

long positionLeft  = -999;

void loop() {
  long newLeft;
  newLeft = knobLeft.read();
  if (newLeft != positionLeft) {
    revs = newLeft;
    revs /= pointsPerRev;
    Serial.print(revs);
    Serial.println();
    positionLeft = newLeft;
  }
  // if a character is sent from the serial monitor,
  // reset both back to zero.
  if (Serial.available()) {
    Serial.read();
    Serial.println("Reset knob to zero");
    knobLeft.write(0);
  }
}