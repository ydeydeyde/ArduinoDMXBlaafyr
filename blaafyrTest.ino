#include <Conceptinetics.h>
#include <Adafruit_NeoPixel.h>
#define PIN 7

Adafruit_NeoPixel strip = Adafruit_NeoPixel(144, PIN, NEO_GRB + NEO_KHZ800);

// Flame
int lowerOffSet = 15;
int upperOffSet = 15;
int flame = 1;

// General brightness
int bright = 50;

// Spread of inner color
int upperBorder = 60;
int lowerBorder = 40;

// Noise level 
int flckr = random(20);

// White Power
int wp = 50;

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  wp = random(89,95);
  // Some example procedures showing how to display to the pixels:
  midArea(strip.Color(wp,wp, wp));
  
  // Upper and lower area are blue right now 
  upperArea(strip.Color(100,0, 0));
  lowerArea(strip.Color(100,0,0));
  //strip.setBrightness(50); 
}

// Fill the dots one after the other with a color
void midArea(uint32_t c) {
  for(uint16_t i=lowerBorder-random(0,lowerOffSet); i<upperBorder+random(0,upperOffSet); i++) {
    strip.setPixelColor(i, c);
    strip.setPixelColor(random(lowerBorder,upperBorder), c);
    strip.show();
  }
}

// Fill the dots one after the other with a color
void upperArea(uint32_t c) {
  for(uint16_t i=0; i<lowerBorder; i++) {
    strip.setPixelColor(i, c);
    strip.show();
  }
}

// Fill the dots one after the other with a color
void lowerArea(uint32_t c) {
  for(uint16_t i=upperBorder+1; i<144; i++) {
    strip.setPixelColor(i, c);
    strip.show();
  }
}
