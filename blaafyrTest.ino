#include <Conceptinetics.h>
#include <Adafruit_NeoPixel.h>

#define PIN 7

// Number of Pixels on the strip
int numPixels = 144;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(numPixels, PIN, NEO_GRB + NEO_KHZ800);

// Flame
int lowerOffSet = 15;
int upperOffSet = 15;
// Flame density/iteration number
int flame = 1;

// General brightness
int bright = 80;

// Spread of inner color/flame
int upperBorder = 25;
int lowerBorder = 20;

// White Power
int wp = 40;

int flameMover = 0;

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  strip.setBrightness(bright);
  mover();
  // Flame like effect
  wp = random(89,95);
  
  // Some example procedures showing how to display to the pixels:
  midArea(strip.Color(wp,wp, wp));
  // Upper and lower area are blue right now 
  upperArea(strip.Color(bright,0,0));
  lowerArea(strip.Color(bright,0,0));
}

// Fill the dots one after the other with a color
void midArea(uint32_t c) {
  for(uint16_t i=lowerBorder-random(0,lowerOffSet); i<upperBorder+random(0,upperOffSet); i=i+flame) {
    strip.setPixelColor(i, c);
    strip.setPixelColor(random(lowerBorder,upperBorder), c);
    strip.show();
  }
}

// Fill the dots one after the other with a color
void upperArea(uint32_t c) {
  for(uint16_t i=0; i<lowerBorder; i++) {
    strip.setPixelColor(i, c+random(1));
    strip.show();
  }
}

// Fill the dots one after the other with a color
void lowerArea(uint32_t c) {
  for(uint16_t i=upperBorder+1; i<numPixels; i++) {
    strip.setPixelColor(i, c+random(1));
    strip.show();
  }
}

void mover() {
  lowerBorder = lowerBorder + flameMover;
  upperBorder = lowerBorder + flameMover;
}
