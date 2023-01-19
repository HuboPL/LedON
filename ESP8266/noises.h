uint8_t   noiseData[NUM_LEDS];
CRGB background[NUM_LEDS];

CRGBPalette16 party = PartyColors_p;

uint8_t   octaveVal   = 2;
uint16_t  xVal        = 0;
int       scaleVal    = 50;
uint16_t  timeVal     = 0;

void fillRawNoise8() {

  timeVal = millis() / 4;

  memset(noiseData, 0, configured_leds);
  fill_raw_noise8(noiseData, configured_leds, octaveVal, xVal, scaleVal, timeVal);

  for (int i = 0; i < configured_leds; i++) {
    leds[i] = ColorFromPalette(party, noiseData[i], noiseData[configured_leds - i - 1]);
  }

  FastLED.show();
}







CRGBPalette16 firePalette = HeatColors_p;
void runFire() {
  int  a = millis();

  for (int i = 0; i < configured_leds; i++) {

    // 3D noise, x is constant, we move through time on y and z axis
    // The 60 here will change the scale of the effect, lower is smoother
    // higher is more flickery. The time value for z was in the original code
    // as that was a 2D matrix version. I've left it in here as it looks
    // nice in 1D too!
    uint8_t noise = inoise8 (0 , i * 60 + a , a / 3);

    // Divides 255 by (configured_leds - 1) and subtracts that amount away from 255 to return
    // a decreasing number each time e.g. for configured_leds = 18, difference between
    // each point is 15, so:
    // i = 0, math = 255
    // i = 1, math = 240
    // i = 2, math = 225
    // ...
    // i = configured_leds, math =  0
    uint8_t math = abs8(i - (configured_leds - 1)) * 255 / (configured_leds - 1);

    // Take the noise function from earlier and subtract math from it,
    // so the further along the strip you are, the higher palette index you
    // are likely to get. This results in the base of the fire (white, yellow)
    // being at the far end of the strip
    uint8_t index = qsub8 (noise, math);

    // Set the LED color from the palette
    leds[i] = ColorFromPalette (firePalette, index, 255);

  }
}
void fire() {
  EVERY_N_MILLISECONDS(5) {
    runFire();
  }
  FastLED.show();
}




void inoiseEight() {
  for (int i = 0; i < configured_leds; i++) {
    uint8_t hue = inoise8(i * 10 + 3 * h, 1);
    leds[i] = CHSV(hue, 255, 255);
  }

  FastLED.show();
}








void inoiseEightMoving() {
  uint16_t  x = 0;
  int       scale;
  uint16_t  t; 
  t = millis() / 5;
  scale = beatsin8(10, 10, 30);

  for (int i = 0; i < configured_leds; i++) {
    uint8_t noise = inoise8(i * scale + x, t);
    uint8_t hue = map(noise, 50, 190, 0, 255);
    leds[i] = CHSV(hue, s , 255);
  }

  FastLED.show();
}







CRGBPalette16  lavaPalette = CRGBPalette16(
                               CRGB::DarkRed,  CRGB::Maroon,   CRGB::DarkRed,  CRGB::Maroon,
                               CRGB::DarkRed,  CRGB::Maroon,   CRGB::DarkRed,  CRGB::DarkRed,
                               CRGB::DarkRed,  CRGB::DarkRed,  CRGB::Red,      CRGB::Orange,
                               CRGB::White,    CRGB::Orange,   CRGB::Red,      CRGB::DarkRed
                             );

uint16_t brightnessScale = 150;
uint16_t indexScale = 100;



void lava() {

  for (int i = 0; i < configured_leds; i++) {
    uint8_t brightness = inoise8(i * brightnessScale, millis() / 5);
    uint8_t index = inoise8(i * indexScale, millis() / 10);
    leds[i] = ColorFromPalette(lavaPalette, index, brightness);
    //leds[i] = CHSV(0, 255, brightness);
  }

  FastLED.show();
}






void drawBackground() {
  // A simple plasma effect
  fill_noise16 (background, configured_leds, 1, millis(), 30, 1, 0, 50, millis() / 3, 10);
}

void drawMovingPixel() {
  // A pixel that moves back and forth using noise
  uint16_t pos = inoise16(millis() * 100);
  pos = constrain(pos, 13000, 51000);
  pos = map(pos, 13000, 51000, 0, configured_leds - 1);
  leds[pos] = CRGB::Red;
}

void movingPixel() {
  drawBackground();
  drawMovingPixel();
  EVERY_N_MILLISECONDS(20) {
    fadeToBlackBy(leds, configured_leds, 10);
    nblend(leds, background, configured_leds, 30);
  }
  FastLED.show();
}






void prettyFill() {

  uint8_t octaves = 1;
  uint16_t x = 0;
  int scale = 100;
  uint8_t hue_octaves = 1;
  uint16_t hue_x = 1;
  int hue_scale = 50;
  uint16_t ntime = millis() / 3;
  uint8_t hue_shift = 5;
  fill_noise16 (leds, configured_leds, octaves, x, scale, hue_octaves, hue_x, hue_scale, ntime, hue_shift);
  FastLED.show();
}
