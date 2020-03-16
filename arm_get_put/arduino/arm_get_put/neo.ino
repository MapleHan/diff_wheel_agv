#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
#define LED1_PIN    A5
#define LED2_PIN    A7
#define LED_COUNT 11
Adafruit_NeoPixel strip1(LED_COUNT, LED1_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2(LED_COUNT, LED2_PIN, NEO_GRB + NEO_KHZ800);


void neoSetup() 
{
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
    clock_prescale_set(clock_div_1);
  #endif
  strip1.begin();
  strip1.show();
  strip1.setBrightness(255); // Set BRIGHTNESS to about 1/5 (max = 255)
  strip2.begin();
  strip2.show();
  strip2.setBrightness(255); // Set BRIGHTNESS to about 1/5 (max = 255)
  for(int i=0; i<strip1.numPixels(); i++) 
  {
    strip1.setPixelColor(i, strip1.Color(0,0,255));
    strip2.setPixelColor(i, strip2.Color(0,0,255));
    strip1.show();
    strip2.show();
    delay(30);
  }
  strip1.clear();
  strip2.clear();
  delay(100);
  for(int i=strip1.numPixels()-1; i>=0;i--) 
  {
    strip1.setPixelColor(i, strip1.Color(0,0,255));
    strip2.setPixelColor(i, strip2.Color(0,0,255));
    strip1.show();
    strip2.show();
    delay(30);
  }
}
