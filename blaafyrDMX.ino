#include <Adafruit_NeoPixel.h>
#include <Conceptinetics.h>

#define NEOPIXEL_PIN 7

// Define number of pixels on LED strip
#define numPixels 4
#define DMX_SLAVE_CHANNELS 4

#define DMX_ADDRESS 1

Adafruit_NeoPixel strip = Adafruit_NeoPixel(numPixels, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

// Slave mode (not master)
DMX_Slave dmx_slave ( DMX_SLAVE_CHANNELS );

int lowMap = 0;
int highMap = 0;

// Universal color / brightness
byte color;

// Spread of flame
byte lowerBorder;
byte upperBorder;

void setup() {
  dmx_slave.enable ();
  // Set start address to 1, this is also the default setting
  // You can change this address at any time during the program
  dmx_slave.setStartAddress (DMX_ADDRESS);
  // Initialize the NeoPixels.
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  //delay (1000);
  lowMap = map(lowerBorder,1,255,1,4);
  highMap = map(upperBorder,1,255,1,4);
}

void loop() {
  color = dmx_slave.getChannelValue (DMX_ADDRESS);
  lowerBorder = dmx_slave.getChannelValue (DMX_ADDRESS + 1);
  upperBorder = dmx_slave.getChannelValue (DMX_ADDRESS + 2);;

  lowMap = lowerBorder;
  highMap = upperBorder;
  
  flameSpread(strip.Color(color,color,color));
  outerBlue(strip.Color(0,0,color));
  
  strip.show();
}

void flameSpread(uint32_t c) {
  for (int i = lowerBorder; i<upperBorder; i++) {
    strip.setPixelColor(i, c);
    strip.show();
  }
}

void outerBlue(uint32_t c) {
  for (int i = 0; i<lowerBorder; i++) {
     strip.setPixelColor(i,c);
     strip.show();
  }
    for (int j = upperBorder+1; j<numPixels; j++) {
     strip.setPixelColor(j,c);
     strip.show();
  }
}
