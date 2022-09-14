#include <TFT.h>  
#include <SPI.h>

#define cs   10
#define dc   9
#define rst  8

TFT TFTscreen = TFT(cs, dc, rst);

void setup() {
  TFTscreen.begin();
  TFTscreen.background(0, 0, 0);
  TFTscreen.setTextSize(2);
}

void loop() {
  int redRandom = random(0, 255);
  int greenRandom = random (0, 255);
  int blueRandom = random (0, 255);
  TFTscreen.stroke(redRandom, greenRandom, blueRandom);
  TFTscreen.text("Hello, World!", 6, 57);
  delay(200);
}
