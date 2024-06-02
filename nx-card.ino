#include <Adafruit_NeoPixel.h>
#include <MPU9255.h>

#define g 9.81
#define PIN 1
#define NUMPIXELS 2
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800); 

MPU9255 mpu;

int LED_MAX_VALUE = 252;
int LED_MIN_VALUE = 3;

void setup() {
  Serial.begin(115200);
  pixels.begin();

  if(mpu.init()) {
    Serial.println(F("initialization failed"));
  } else {
    Serial.println(F("initialization successful!"));
  }
}

void loop() {
  pixels.clear();
  mpu.read_acc();

  double AY = 1;
  AY = mpu.ay;
  AY = AY/16384;
  AY = AY*g;

  serColor(AY);
  delay(500);
}

void serColor(double AY) {
  int LED_A_RED = 252;
  int LED_A_GREEN = 3;
  int LED_A_BLUE = 0;

  int defaultPositionY = 100;
  int currentAy = abs(AY*10);

  if (currentAy < defaultPositionY) {
    int variation = currentAy - defaultPositionY;
    int decreaseColor = LED_MAX_VALUE + ((LED_MAX_VALUE/defaultPositionY) * variation);
    int increaseColor = LED_MIN_VALUE - ((LED_MAX_VALUE/defaultPositionY) * variation);
 
    pixels.setPixelColor(0, pixels.Color(decreaseColor, LED_A_GREEN, increaseColor));
    pixels.setPixelColor(1, pixels.Color(increaseColor, LED_A_GREEN, decreaseColor));
    pixels.show();
  }
  
}
