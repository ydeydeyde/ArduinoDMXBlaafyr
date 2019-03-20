#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 7

// Spread of inner color
int upperBorder = 80;
int lowerBorder = 30;

// Noise level 
int flckr = random(20);

Adafruit_NeoPixel strip = Adafruit_NeoPixel(144, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  // Some example procedures showing how to display to the pixels:
  midArea(strip.Color(40,40, flckr), 50); 
  upperArea(strip.Color(20,20, 50),50);
  lowerArea(strip.Color(20,20,50),50);
}

// Fill the dots one after the other with a color
void midArea(uint32_t c, uint8_t wait) {
  for(uint16_t i=lowerBorder; i<upperBorder; i++) {
    strip.setPixelColor(i, c);
    strip.show();
  }
}

// Fill the dots one after the other with a color
void upperArea(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<40; i++) {
    strip.setPixelColor(i, c);
    strip.show();
   // delay(wait);
  }
}

// Fill the dots one after the other with a color
void lowerArea(uint32_t c, uint8_t wait) {
  for(uint16_t i=85; i<=144; i++) {
    for (int c = 0; c<100; c+5) {
    strip.setPixelColor(i, c);
    strip.show();
    }
   // delay(wait);
  }
}
