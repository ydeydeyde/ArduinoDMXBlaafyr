// NeoPixel library
#include <Adafruit_NeoPixel.h>

// CTC-DRA-10-R2 DMX shield library
#include <Conceptinetics.h>

// Digital data pin for WS2818b LED strip
#define NEOPIXEL_PIN 6

// Define number of pixels on LED strip
#define numPixels 75

// Number of DMX Channels (this be anything from 1-512)
#define DMX_SLAVE_CHANNELS 4

#define DMX_ADDRESS 1

Adafruit_NeoPixel strip = Adafruit_NeoPixel(numPixels, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

// Slave mode (not master)
DMX_Slave dmx_slave ( DMX_SLAVE_CHANNELS );

// Brightness
byte bright;

// Spread of flame
byte lowerBorder;
byte upperBorder;

void setup() {
  dmx_slave.enable ();
  dmx_slave.setStartAddress (DMX_ADDRESS);

  strip.begin();
  // Updates LED strip (now to off, since there is no value assigned yet)
  strip.show();
}

void loop() {
  // DMX address 1
  bright = dmx_slave.getChannelValue (DMX_ADDRESS);
  // DMX address 2
  lowerBorder = dmx_slave.getChannelValue (DMX_ADDRESS + 1);
  // DMX adress 3
  upperBorder = dmx_slave.getChannelValue (DMX_ADDRESS + 2);;
  
  // Mapping incoming DMX bytes to number of pixels on strip
  lowerBorder = map(lowerBorder, 1, 255, 1, numPixels);
  upperBorder = map(upperBorder, 1, 255, 1, numPixels);

  int bRandom = random(255);
  
  if (bright > 0) {
    flameSpread(strip.Color(bRandom, bRandom, bRandom));
    flameSpread(strip.Color(bright, bright, bright));

    flameOffSet(strip.Color(bRandom, bRandom, bRandom));

    outerBlue(strip.Color(0, 0, bright));
  }
  strip.show();
}

void flameSpread(uint32_t c) {
  for (int i = lowerBorder; i < upperBorder; i++) {
    strip.setPixelColor(i, c);
    strip.show();
  }
}
// Every 3rd iteration of the flame will be receiving a random variable, to simulate noise in the white flame
void flameOffSet(uint32_t c) {
  for (int i = lowerBorder; i < upperBorder; i = i + 3) {
    strip.setPixelColor(i, c);
    strip.show();
  }
}

void outerBlue(uint32_t c) {
  for (int i = 0; i < lowerBorder; i++) {
    strip.setPixelColor(i, c);
   // strip.show();
  }
  for (int j = upperBorder; j < numPixels; j++) {
    strip.setPixelColor(j, c);
   // strip.show();
  }
  for (int l = upperBorder; l < numPixels; l++) {
    // Trying to fade upperEnd with a sin wave (0-1)
    //float fade = sin(l / numPixels * PI);
    // Splitting up RGB in bytes using bitshifting
    //int red = (c & 0xFF0000) >> 16;
    //int green = (c & 0xFF00) >> 8;
    //int blue = c & 0xFF;
    //c = (int)(red * fade) << 16 + (int)(green * fade) << 8 + (int)(blue * fade);
    strip.setPixelColor(l, random(c));
    strip.show();
  }
  for (int m = 0; m < 15; m++) {
    // Trying to fade lowerEnd with a sin wave (0-1)
    //float fade = sin(m / numPixels * PI);
    // Splitting up RGB in bytes using bitshifting
    //int red = (c & 0xFF0000) >> 16;
    //int green = (c & 0xFF00) >> 8;
    //int blue = c & 0xFF;
    //c = (int)(red * fade) << 16 + (int)(green * fade) << 8 + (int)(blue * fade);
    strip.setPixelColor(m, c);
    strip.show();
  }
  // When DMX channel 1 is more than 100 then the blue noise appears
  if (bright > 100) {
    for (int k = 0; k < lowerBorder; k++) {
      strip.setPixelColor(k, random(c));
      strip.show();
    }
  }
}
