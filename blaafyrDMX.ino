#include <Adafruit_NeoPixel.h>
#include <Conceptinetics.h>

#define NEOPIXEL_PIN 7

// Define number of pixels on LED strip
#define numPixels 75
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
  strip.show();
}

void loop() {
  bright = dmx_slave.getChannelValue (DMX_ADDRESS);
  lowerBorder = dmx_slave.getChannelValue (DMX_ADDRESS + 1);
  upperBorder = dmx_slave.getChannelValue (DMX_ADDRESS + 2);;
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
    //float fade = sin(l / numPixels * PI);
    //int red = (c & 0xFF0000) >> 16;
    //int green = (c & 0xFF00) >> 8;
    //int blue = c & 0xFF;
    //c = (int)(red * fade) << 16 + (int)(green * fade) << 8 + (int)(blue * fade);
    strip.setPixelColor(l, random(c));
    strip.show();
  }
  for (int m = 0; m < 15; m++) {
    //float fade = sin(m / numPixels * PI);
    //int red = (c & 0xFF0000) >> 16;
    //int green = (c & 0xFF00) >> 8;
    //int blue = c & 0xFF;
    //c = (int)(red * fade) << 16 + (int)(green * fade) << 8 + (int)(blue * fade);
    strip.setPixelColor(m, c);
    strip.show();
  }
  if (bright > 100) {
    for (int k = 0; k < lowerBorder; k++) {
      strip.setPixelColor(k, random(c));
      strip.show();
    }
  }
}
