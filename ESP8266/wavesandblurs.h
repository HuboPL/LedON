void addingWaves() {

  uint8_t posBeat  = beatsin8(30, 0, configured_leds - 1, 0, 0);
  uint8_t posBeat2 = beatsin8(60, 0, configured_leds - 1, 0, 0);
  uint8_t posBeat3 = beatsin16(30, 0, configured_leds - 1, 0, 127);
  uint8_t posBeat4 = beatsin16(60, 0, configured_leds - 1, 0, 127);

  uint8_t colBeat  = beatsin8(45, 0, 255, 0, 0);

  leds[(posBeat + posBeat2) / 2]  = CHSV(colBeat, s, 255);
  leds[(posBeat3 + posBeat4) / 2]  = CHSV(colBeat, s, 255);

  fadeToBlackBy(leds, configured_leds, 10);
  FastLED.show();
}



//BLURPHASEBEAT

void blurPhaseBeat() {

  uint8_t sinBeat   = beatsin8(30, 0, configured_leds - 1, 0, 0);
  uint8_t sinBeat2  = beatsin8(30, 0, configured_leds - 1, 0, 85);
  uint8_t sinBeat3  = beatsin8(30, 0, configured_leds - 1, 0, 170);

  // If you notice that your pattern is missing out certain LEDs, you
  // will need to use the higher resolution beatsin16 instead. In this
  // case remove the 3 lines above and replace them with the following:
  // uint16_t sinBeat   = beatsin16(30, 0, configured_leds - 1, 0, 0);
  // uint16_t sinBeat2  = beatsin16(30, 0, configured_leds - 1, 0, 21845);
  // uint16_t sinBeat3  = beatsin16(30, 0, configured_leds - 1, 0, 43690);

  leds[sinBeat]   = CRGB::Green;
  leds[sinBeat2]  = CRGB::Blue;
  leds[sinBeat3]  = CRGB::Red;

  EVERY_N_MILLISECONDS(1) {
    for (int i = 0; i < 4; i++) {
      blur1d(leds, configured_leds, 50);
    }
  }

  //fadeToBlackBy(leds, configured_leds, 10);

  FastLED.show();
}




//BRIGHTNESSWAVES

void brightnessWaves() {

  //Creat a sin wave with period of 2 seconds (30bpm) to change the brightness of the strip
  uint8_t sinBeat = beatsin8(30, 50, 255, 0, 0);

  // Color each pixel from the palette using the index from colorIndex[]
  for (int i = 0; i < configured_leds; i++) {
    leds[i] = ColorFromPalette(greenblue, colorIndex[i], sinBeat);
  }

  EVERY_N_MILLISECONDS(5) {
    for (int i = 0; i < configured_leds; i++) {
      colorIndex[i]++;
    }
  }
  FastLED.show();
}


//GRADIENTBEAT

CRGBPalette16 orangePink = browngreen_gp;
void gradientBeat() {
  uint16_t beatA = beatsin16(30, 0, 255);
  uint16_t beatB = beatsin16(20, 0, 255);
  fill_palette(leds, configured_leds, (beatA + beatB) / 2, 10, orangePink, 255, LINEARBLEND);

  FastLED.show();
}



//MOVINGDOT

void movingDot() {

  uint16_t sinBeat = beatsin16(30, 0, configured_leds - 1, 0, 0);

  //leds[sinBeat] = CRGB::Blue;
  leds[sinBeat] = CHSV(h, s, 255);;

  fadeToBlackBy(leds, configured_leds, 10);

  EVERY_N_MILLISECONDS(10) {
    Serial.println(sinBeat);
  }

  FastLED.show();
}



//MOVINGDOTS

void movingDots() {
  uint16_t posBeat  = beatsin16(30, 0, configured_leds - 1, 0, 0);
  uint16_t posBeat2 = beatsin16(60, 0, configured_leds - 1, 0, 0);

  uint16_t posBeat3 = beatsin16(30, 0, configured_leds - 1, 0, 32767);
  uint16_t posBeat4 = beatsin16(60, 0, configured_leds - 1, 0, 32767);

  // Wave for LED color
  uint8_t colBeat  = beatsin8(45, 0, 255, 0, 0);

  leds[(posBeat + posBeat2) / 2]  = CHSV(colBeat, s, 255);
  leds[(posBeat3 + posBeat4) / 2]  = CHSV(colBeat, s, 255);

  fadeToBlackBy(leds, configured_leds, 10);
}




//PHASEBEAT

void phaseBeat() {

  uint8_t sinBeat   = beatsin8(30, 0, configured_leds - 1, 0, 0);
  uint8_t sinBeat2  = beatsin8(30, 0, configured_leds - 1, 0, 85);
  uint8_t sinBeat3  = beatsin8(30, 0, configured_leds - 1, 0, 170);


  leds[sinBeat]   = CHSV(h, s, 255);
  leds[sinBeat2]  = CHSV(168 + h, s, 255);
  leds[sinBeat3]  = CRGB::White;

  fadeToBlackBy(leds, configured_leds, 10);

  EVERY_N_MILLISECONDS(10) {
    Serial.print(sinBeat);
    Serial.print(",");
    Serial.print(sinBeat2);
    Serial.print(",");
    Serial.println(sinBeat3);
  }

  FastLED.show();
}


//RAINBOWBEAT

void rainbowBeat() {

  uint16_t beatA = beatsin16(30, 0, 255);
  uint16_t beatB = beatsin16(20, 0, 255);
  fill_rainbow(leds, configured_leds, (beatA + beatB) / 2, 8);
}


//SAWTOOTH

uint8_t hue = 0;
void sawTooth() {
  uint8_t pos = map(beat16(40, 0), 0, 65535, 0, configured_leds - 1);
  leds[pos] = CHSV( hue, s, 255);

  fadeToBlackBy(leds, configured_leds, 3);

  EVERY_N_MILLISECONDS( 10 ) {
    hue++;
  }

  EVERY_N_MILLISECONDS(10) {
    Serial.println(pos);
  }

  FastLED.show();

}






//RIPPLE



uint32_t currentBg = random(256);
uint32_t nextBg = currentBg;
int color2;
int center = 0;
int step = -1;
const int maxSteps = 16;
const float fadeRate2 = 0.8;
int diff;


int wrap(int step) {
  if (step < 0) return configured_leds + step;
  if (step > configured_leds - 1) return step - configured_leds;
  return step;
}


void ripple() {

  if (currentBg == nextBg) {
    nextBg = random(256);
  }
  else if (nextBg > currentBg) {
    currentBg++;
  } else {
    currentBg--;
  }
  for (uint16_t l = 0; l < configured_leds; l++) {
    leds[l] = CHSV(currentBg, s, 110);
  }

  if (step == -1) {
    center = random(configured_leds);
    color2 = random(256);
    step = 0;
  }

  if (step == 0) {
    leds[center] = CHSV(color2, s, 255);
    step ++;
  }
  else {
    if (step < maxSteps) {

      leds[wrap(center + step)] = CHSV(color2, s, pow(fadeRate2, step) * 255);
      leds[wrap(center - step)] = CHSV(color2, s, pow(fadeRate2, step) * 255);
      if (step > 3) {
        leds[wrap(center + step - 3)] = CHSV(color2, s, pow(fadeRate2, step - 2) * 255);
        leds[wrap(center - step + 3)] = CHSV(color2, s, pow(fadeRate2, step - 2) * 255);
      }
      step ++;
    }
    else {
      step = -1;
    }
  }

 LEDS.show();
 FastLED.delay(50);
}
