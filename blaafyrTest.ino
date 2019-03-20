#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 7

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(144, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code


  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  // Some example procedures showing how to display to the pixels:
  white(strip.Color(40,40, 40), 50); 
  upperBlue(strip.Color(20,20, 50),50);
  lowerBlue(strip.Color(20,20,50),50);
}

// Fill the dots one after the other with a color
void white(uint32_t c, uint8_t wait) {
  for(uint16_t i=40; i<86; i++) {
    strip.setPixelColor(i, c);
    strip.show();
  }
}

// Fill the dots one after the other with a color
void upperBlue(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<40; i++) {
    strip.setPixelColor(i, c);
    strip.show();
   // delay(wait);
  }
}

// Fill the dots one after the other with a color
void lowerBlue(uint32_t c, uint8_t wait) {
  for(uint16_t i=85; i<145; i++) {
    for (int c = 0; c<100; c+5) {
    strip.setPixelColor(i, c);
    strip.show();
    }
   // delay(wait);
  }
}