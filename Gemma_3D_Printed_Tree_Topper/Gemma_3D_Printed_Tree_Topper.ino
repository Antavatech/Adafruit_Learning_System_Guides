// SPDX-FileCopyrightText: 2017 Phillip Burgess for Adafruit Industries
//
// SPDX-License-Identifier: MIT

#include <Adafruit_NeoPixel.h>

#define PIN       1
#define NUM_LEDS 36

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_LEDS, PIN);

uint8_t  mode   = 0,        // Current animation effect
         offset = 0;        // Position of spinner animation
uint32_t color  = 0xA000A0; // Purple
uint32_t prevTime;          // Time of last animation mode switch

void setup() {
  pixels.begin();
  pixels.setBrightness(255); // Full brightness
  prevTime = millis();       // Starting time
}

void loop() {
  uint8_t  i;
  uint32_t t;

  switch(mode) {

   case 0: // Random sparkles - just one LED on at a time!
    i = random(NUM_LEDS);           // Choose a random pixel
    pixels.setPixelColor(i, color); // Set it to current color
    pixels.show();                  // Refresh LED states
    // Set same pixel to "off" color now but DON'T refresh...
    // it stays on for now...both this and the next random
    // pixel will be refreshed on the next pass.
    pixels.setPixelColor(i, 0);
    delay(10);                      // 10 millisecond delay
    break;
 
   case 1: // Spinny wheel
    for(i=0; i<NUM_LEDS; i++) {    // For each LED...
      uint32_t c = 0;              // Assume pixel will be "off" color
      if(((offset + i) & 7) < 2) { // For each 8 pixels, 2 will be...
        c = color;                 // ...assigned the current color
      }
      pixels.setPixelColor(i, c);  // Set color of pixel 'i'
    }
    pixels.show();                 // Refresh LED states
    delay(90);                     // 90 millisecond delay
    offset++;                      // Shift animation by 1 pixel on next frame
    break;

    // More animation modes could be added here!
  }

  t = millis();                    // Current time in milliseconds
  if((t - prevTime) > 8000) {      // Every 8 seconds...
    mode++;                        // Advance to next animation mode
    if(mode > 1) {                 // End of modes?
      mode = 0;                    // Start over from beginning
    }
    pixels.clear();                // Set all pixels to 'off' state
    prevTime = t;                  // Record the time of the last mode change
  }
}
