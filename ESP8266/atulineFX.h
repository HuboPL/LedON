uint8_t  thisfade = 8;                                        // How quickly does it fade? Lower = slower fade rate.
int       thishue = 50;                                       // Starting hue.
uint8_t   thisinc = 1;                                        // Incremental value for rotating hues
uint8_t   thissat = 100;                                      // The saturation, where 255 = brilliant colours.
uint8_t   thisbri = 255;                                      // Brightness of a sequence. Remember, max_bright is the overall limiter.
int       huediff = 256;                                      // Range of random #'s to use for hue








void confettino() {                                             // random colored speckles that blink in and fade smoothly
  fadeToBlackBy(leds, configured_leds, thisfade);                    // Low values = slower fade.
  int pos = random16(configured_leds);                               // Pick an LED at random.
  leds[pos] += CHSV((thishue + random16(huediff)) / 4 , thissat, thisbri); // I use 12 bits for hue so that the hue increment isn't too quick.
  thishue = thishue + thisinc;                                // It increments here.
} // confetti()


void ChangeMe() {                                             // A time (rather than loop) based demo sequencer. This gives us full control over the length of each sequence.
  uint8_t secondHand = (millis() / 1000) % 15;                // IMPORTANT!!! Change '15' to a different value to change duration of the loop.
  static uint8_t lastSecond = 99;                             // Static variable, means it's only defined once. This is our 'debounce' variable.
  if (lastSecond != secondHand) {                             // Debounce to make sure we're not repeating an assignment.
    lastSecond = secondHand;
    switch (secondHand) {
      case  0: thisinc = 1; thishue = 192; thissat = 255; thisfade = 2; huediff = 256; break; // You can change values here, one at a time , or altogether.
      case  5: thisinc = 2; thishue = 128; thisfade = 8; huediff = 64; break;
      case 10: thisinc = 1; thishue = random16(255); thisfade = 1; huediff = 16; break; // Only gets called once, and not continuously for the next several seconds. Therefore, no rainbows.
      case 15: break;                                                                // Here's the matching 15 for the other one.
    }
  }
} // ChangeMe()

void runConfetti() {
  ChangeMe();                                                 // Check the demo loop for changes to the variables.

  EVERY_N_MILLISECONDS(5) {                           // FastLED based non-blocking delay to update/display the sequence.
    confettino();
  }
  FastLED.show();
} // loop()


void confetti_pal() {                                         // random colored speckles that blink in and fade smoothly

  fadeToBlackBy(leds, configured_leds, thisfade);                    // Low values = slower fade.
  int pos = random16(configured_leds);                               // Pick an LED at random.
  leds[pos] = ColorFromPalette(currentPalette, thishue + random16(huediff) / 4 , thisbri, LINEARBLEND);
  thishue = thishue + thisinc;                                // It increments here.

}


void ChangeMe2() {                                             // A time (rather than loop) based demo sequencer. This gives us full control over the length of each sequence.

  uint8_t secondHand = (millis() / 1000) % 15;                // IMPORTANT!!! Change '15' to a different value to change duration of the loop.
  static uint8_t lastSecond = 99;                             // Static variable, means it's only defined once. This is our 'debounce' variable.
  if (lastSecond != secondHand) {                             // Debounce to make sure we're not repeating an assignment.
    lastSecond = secondHand;
    switch (secondHand) {
      case  0: targetPalette = OceanColors_p; thisinc = 1; thishue = 192; thissat = 255; thisfade = 2; huediff = 255; break; // You can change values here, one at a time , or altogether.
      case  5: targetPalette = LavaColors_p; thisinc = 2; thishue = 128; thisfade = 8; huediff = 64; break;
      case 10: targetPalette = ForestColors_p; thisinc = 1; thishue = random16(255); thisfade = 1; huediff = 16; break; // Only gets called once, and not continuously for the next several seconds. Therefore, no rainbows.
      case 15: break;                                         // Here's the matching 15 for the other one.
    }
  }

}

void runConfetti2() {

  ChangeMe2();                                                 // Check the demo loop for changes to the variables.

  EVERY_N_MILLISECONDS(100) {
    uint8_t maxChanges = 24;
    nblendPaletteTowardPalette(currentPalette, targetPalette, maxChanges);   // AWESOME palette blending capability.
  }

  EVERY_N_MILLISECONDS(5) {                           // FastLED based non-blocking delay to update/display the sequence.
    confetti_pal();
  }

  FastLED.show();

}



void dot_beat() {
  int   thisdelay =   10;                                       // A delay value for the sequence(s)
  uint8_t   count =   0;                                        // Count up to 255 and then reverts to 0
  uint8_t fadeval = 224;                                        // Trail behind the LED's. Lower => faster fade.

  uint8_t bpm = 30;

  uint8_t inner = beatsin8(bpm, configured_leds / 4, configured_leds / 4 * 3); // Move 1/4 to 3/4
  uint8_t outer = beatsin8(bpm, 0, configured_leds - 1);             // Move entire length
  uint8_t middle = beatsin8(bpm, configured_leds / 3, configured_leds / 3 * 2); // Move 1/3 to 2/3

  leds[middle] = CRGB::Purple;
  leds[inner] = CRGB::Blue;
  leds[outer] = CRGB::Yellow;

  nscale8(leds, configured_leds, fadeval);                           // Fade the entire array. Or for just a few LED's, use  nscale8(&leds[2], 5, fadeval);

}

void runDotBeat () {
  dot_beat();
  FastLED.show();

}




uint8_t easeH = 0;

void ease() {

  static uint8_t easeOutVal = 0;
  static uint8_t easeInVal  = 0;
  static uint8_t lerpVal    = 0;

  easeOutVal = ease8InOutQuad(easeInVal);                     // Start with easeInVal at 0 and then go to 255 for the full easing.
  easeInVal++;

  lerpVal = lerp8by8(0, configured_leds, easeOutVal);               // Map it to the number of LED's you have.

  leds[lerpVal] = CHSV(easeH, 255, 255);

  fadeToBlackBy(leds, configured_leds, 16);                          // 8 bit, 1 = slow fade, 255 = fast fade

}

void runEase() {

  EVERY_N_MILLISECONDS(15) {                           // FastLED based non-blocking delay to update/display the sequence.
    easeH++;
    ease();
  }

  FastLED.show();

}




uint8_t frequency = 30;                                       // controls the interval between strikes
uint8_t flashes = 10;                                          //the upper limit of flashes per strike
unsigned int dimmer = 1;

uint8_t ledstart;                                             // Starting location of a flash
uint8_t ledlen;                                               // Length of a flash


void Lightning() {

  ledstart = random8(configured_leds);                               // Determine starting location of flash
  ledlen = random8(configured_leds - ledstart);                      // Determine length of flash (not to go beyond NUM_LEDS-1)

  for (int flashCounter = 0; flashCounter < random8(3, flashes); flashCounter++) {
    if (flashCounter == 0) dimmer = 5;                        // the brightness of the leader is scaled down by a factor of 5
    else dimmer = random8(1, 3);                              // return strokes are brighter than the leader

    fill_solid(leds + ledstart, ledlen, CHSV(255, 0, 255 / dimmer));
    FastLED.show();                       // Show a section of LED's
    delay(random8(4, 10));                                    // each flash only lasts 4-10 milliseconds
    fill_solid(leds + ledstart, ledlen, CHSV(255, 0, 0));     // Clear the section of LED's
    FastLED.show();

    if (flashCounter == 0) delay (150);                       // longer delay until next flash after the leader

    delay(50 + random8(100));                                 // shorter delay between strokes
  } // for()

  delay(random8(frequency) * 100);                            // delay between strikes

}








#define qsubd(x, b)  ((x>b)?b:0)                              // Digital unsigned subtraction macro. if result <0, then => 0. Otherwise, take on fixed value.
#define qsuba(x, b)  ((x>b)?x-b:0)


void plasma() {                                                 // This is the heart of this program. Sure is short. . . and fast.

  int thisPhase = beatsin8(6, -64, 64);                         // Setting phase change for a couple of waves.
  int thatPhase = beatsin8(7, -64, 64);

  for (int k = 0; k < configured_leds; k++) {                          // For each of the LED's in the strand, set a brightness based on a wave as follows:

    int colorIndex = cubicwave8((k * 23) + thisPhase) / 2 + cos8((k * 15) + thatPhase) / 2; // Create a wave and add a phase change and add another wave with its own phase change.. Hey, you can even change the frequencies if you wish.
    int thisBright = qsuba(colorIndex, beatsin8(7, 0, 96));                               // qsub gives it a bit of 'black' dead space by setting sets a minimum value. If colorIndex < current value of beatsin8(), then bright = 0. Otherwise, bright = colorIndex..

    leds[k] = ColorFromPalette(currentPalette, colorIndex, thisBright, LINEARBLEND);  // Let's now add the foreground colour.
  }

}


void runPlasma() {

  EVERY_N_MILLISECONDS(50) {                                  // FastLED based non-blocking delay to update/display the sequence.
    plasma();
  }

  EVERY_N_MILLISECONDS(100) {
    uint8_t maxChanges = 24;
    nblendPaletteTowardPalette(currentPalette, targetPalette, maxChanges);   // AWESOME palette blending capability.
  }


  EVERY_N_SECONDS(5) {                                 // Change the target palette to a random one every 5 seconds.
    uint8_t baseC = random8();                         // You can use this as a baseline colour if you want similar hues in the next line.
    targetPalette = CRGBPalette16(CHSV(baseC + random8(32), 192, random8(128, 255)), CHSV(baseC + random8(32), 255, random8(128, 255)), CHSV(baseC + random8(32), 192, random8(128, 255)), CHSV(baseC + random8(32), 255, random8(128, 255)));
  }

  FastLED.show();

}







void rainbow_march(uint8_t thisdelay, uint8_t deltahue) {     // The fill_rainbow call doesn't support brightness levels.

  uint8_t thishue = millis() * (255 - thisdelay) / 255;       // To change the rate, add a beat or something to the result. 'thisdelay' must be a fixed value.

  // thishue = beat8(50);                                       // This uses a FastLED sawtooth generator. Again, the '50' should not change on the fly.
  // thishue = beatsin8(50,0,255);                              // This can change speeds on the fly. You can also add these to each other.

  fill_rainbow(leds, configured_leds, thishue, deltahue);            // Use FastLED's fill_rainbow routine.

}

void RainbowMarch() {

  rainbow_march(200, 10);
  FastLED.show();

}







uint8_t thishueRM = 0;                                          // Starting hue value.
int8_t thisrotRM = 1;                                           // Hue rotation speed. Includes direction.
uint8_t deltahueRM = 1;                                         // Hue change between pixels.
bool thisdirRM = 0;


void rainbow_march() {                                        // The fill_rainbow call doesn't support brightness levels. You would need to change the max_bright value.

  if (thisdirRM == 0) thishueRM += thisrotRM; else thishueRM -= thisrotRM; // I could use signed math, but 'thisdir' works with other routines.
  fill_rainbow(leds, configured_leds, thishueRM, deltahueRM);            // I don't change deltahue on the fly as it's too fast near the end of the strip.

} // rainbow_march()


void ChangeMeRM() {
  // A time (rather than loop) based demo sequencer. This gives us full control over the length of each sequence.

  uint8_t secondHand = (millis() / 1000) % 60;                // Change '60' to a different value to change length of the loop.
  static uint8_t lastSecond = 99;                             // Static variable, means it's only defined once. This is our 'debounce' variable.

  if (lastSecond != secondHand) {                             // Debounce to make sure we're not repeating an assignment.
    lastSecond = secondHand;
    switch (secondHand) {
      case  0: thisrotRM = 1; deltahueRM = 5; break;
      case  5: thisdirRM = -1; deltahueRM = 10; break;
      case 10: thisrotRM = 5; break;
      case 15: thisrotRM = 5; thisdirRM = -1; deltahueRM = 20; break;
      case 20: deltahueRM = 30; break;
      case 25: deltahueRM = 2; thisrotRM = 5; break;
      case 30: break;
    }
  }

}

void RainbowMarch2() {

  ChangeMeRM();

  EVERY_N_MILLISECONDS(40) {                           // FastLED based non-blocking delay to update/display the sequence.
    rainbow_march();
  }

  FastLED.show();
}







uint16_t Xorig = 0x012;
uint16_t Yorig = 0x015;
uint16_t X;
uint16_t Y;
uint16_t Xn;
uint16_t Yn;
uint8_t indexS;

void serendipitous () {

  EVERY_N_SECONDS(5) {
    uint8_t baseC = random8();
    targetPalette = CRGBPalette16(CHSV(baseC - 3, 255, random8(192, 255)), CHSV(baseC + 2, 255, random8(192, 255)), CHSV(baseC + 5, 192, random8(192, 255)), CHSV(random8(), 255, random8(192, 255)));

    X = Xorig;
    Y = Yorig;
  }

  //  Xn = X-(Y/2); Yn = Y+(Xn/2);
  //  Xn = X-Y/2;   Yn = Y+Xn/2;
  //  Xn = X-(Y/2); Yn = Y+(X/2.1);
  Xn = X - (Y / 3); Yn = Y + (X / 1.5);
  //  Xn = X-(2*Y); Yn = Y+(X/1.1);

  X = Xn;
  Y = Yn;

  indexS = (sin8(X) + cos8(Y)) / 2;                      // Guarantees maximum value of 255

  CRGB newcolor = ColorFromPalette(currentPalette, indexS, 255, LINEARBLEND);

  //  nblend(leds[X%NUM_LEDS-1], newcolor, 224);          // Try and smooth it out a bit. Higher # means less smoothing.
  nblend(leds[map(X, 0, 65535, 0, configured_leds)], newcolor, 224); // Try and smooth it out a bit. Higher # means less smoothing.

  fadeToBlackBy(leds, configured_leds, 16);                    // 8 bit, 1 = slow, 255 = fast

} // serendipitous()

void runSerendipitous() {

  EVERY_N_MILLISECONDS(60) {
    nblendPaletteTowardPalette(currentPalette, targetPalette, 24);  // Blend towards the target palette
  }

  EVERY_N_MILLISECONDS(50) {
    serendipitous();
  }

  LEDS.show();

}






uint8_t sindelay = 50;
int wave1 = 0;                                                // Current phase is calculated.
int wave2 = 0;
int wave3 = 0;

uint8_t inc1 = 2;                                             // Phase shift. Keep it low, as this is the speed at which the waves move.
uint8_t inc2 = 1;
uint8_t inc3 = -2;

uint8_t lvl1 = 80;                                            // Any result below this value is displayed as 0.
uint8_t lvl2 = 80;
uint8_t lvl3 = 80;

uint8_t mul1 = 20;                                            // Frequency, thus the distance between waves
uint8_t mul2 = 25;
uint8_t mul3 = 22;



void ChangeMeSin() {
  uint8_t secondHand = (millis() / 800) % 30;                // Increase this and add more options below if you want a longer demo.
  static uint8_t lastSecond = 99;                             // Static variable, means it's only defined once. This is our 'debounce' variable.


  if (lastSecond != secondHand) {                             // You can change variables, but remember to set them back in the next demo, or they will stay as is.
    lastSecond = secondHand;
    switch (secondHand) {
      case 0: sindelay = 25; mul1 = 20; mul2 = 25; mul3 = 22; lvl1 = 80; lvl2 = 80; lvl3 = 80; inc1 = 1; inc2 = 1; inc3 = -1; break;
      case 20: mul1 = 5; mul2 = 8; mul3 = 7; break;
      case 40: sindelay = 40; lvl1 = 220; lvl2 = 220; lvl3 = 220; break;
      case 60: break;
    }
  }
}

void three_sin() {
  wave1 += inc1;
  wave2 += inc2;
  wave3 += inc3;
  for (int k = 0; k < configured_leds; k++) {
    leds[k].r = qsub8(sin8(mul1 * k + wave1 / 128), lvl1);    // Another fixed frequency, variable phase sine wave with lowered level
    leds[k].g = qsub8(sin8(mul2 * k + wave2 / 128), lvl2);    // A fixed frequency, variable phase sine wave with lowered level
    leds[k].b = qsub8(sin8(mul3 * k + wave3 / 128), lvl3);    // A fixed frequency, variable phase sine wave with lowered level
  }
}


void ThreeSinDemo() {
  ChangeMeSin();
  EVERY_N_MILLISECONDS(50) {                           // FastLED based non-blocking delay to update/display the sequence.
    three_sin();                                              // Improved method of using non-blocking delay
  }
}







void noise16_1() {                                            // moves a noise up and down while slowly shifting to the side

  uint16_t scale = 1000;                                      // the "zoom factor" for the noise

  for (uint16_t i = 0; i < configured_leds; i++) {

    uint16_t shift_x = beatsin8(5);                           // the x position of the noise field swings @ 17 bpm
    uint16_t shift_y = millis() / 100;                        // the y position becomes slowly incremented


    uint16_t real_x = (i + shift_x) * scale;                  // the x position of the noise field swings @ 17 bpm
    uint16_t real_y = (i + shift_y) * scale;                  // the y position becomes slowly incremented
    uint32_t real_z = millis() * 20;                          // the z position becomes quickly incremented

    uint8_t noise = inoise16(real_x, real_y, real_z) >> 8;   // get the noise data and scale it down

    uint8_t index = sin8(noise * 3);                         // map LED color based on noise data
    uint8_t bri   = noise;

    leds[i] = ColorFromPalette(currentPalette, index, bri, LINEARBLEND);   // With that value, look up the 8 bit colour palette value and assign it to the current LED.
  }

}

void runNoise16_1() {

  EVERY_N_MILLISECONDS(50) {
    nblendPaletteTowardPalette(currentPalette, targetPalette, 24);  // Blend towards the target palette
  }

  EVERY_N_SECONDS(5) {             // Change the target palette to a random one every 5 seconds.
    targetPalette = CRGBPalette16(CHSV(random8(), 255, random8(128, 255)), CHSV(random8(), 255, random8(128, 255)), CHSV(random8(), 192, random8(128, 255)), CHSV(random8(), 255, random8(128, 255)));
  }

  noise16_1();

  FastLED.show();

}







void noise16_2() {                                            // just moving along one axis = "lavalamp effect"

  uint8_t scale = 1000;                                       // the "zoom factor" for the noise

  for (uint16_t i = 0; i < configured_leds; i++) {

    uint16_t shift_x = millis() / 10;                         // x as a function of time
    uint16_t shift_y = 0;

    uint32_t real_x = (i + shift_x) * scale;                  // calculate the coordinates within the noise field
    uint32_t real_y = (i + shift_y) * scale;                  // based on the precalculated positions
    uint32_t real_z = 4223;

    uint8_t noise = inoise16(real_x, real_y, real_z) >> 8;    // get the noise data and scale it down

    uint8_t index = sin8(noise * 3);                          // map led color based on noise data
    uint8_t bri   = noise;

    leds[i] = ColorFromPalette(currentPalette, index, bri, LINEARBLEND);   // With that value, look up the 8 bit colour palette value and assign it to the current LED.

  }

}
void runNoise16_2() {

  EVERY_N_MILLISECONDS(50) {
    nblendPaletteTowardPalette(currentPalette, targetPalette, 24);  // Blend towards the target palette
  }

  EVERY_N_SECONDS(5) {             // Change the target palette to a random one every 5 seconds.
    targetPalette = CRGBPalette16(CHSV(random8(), 255, random8(128, 255)), CHSV(random8(), 255, random8(128, 255)), CHSV(random8(), 192, random8(128, 255)), CHSV(random8(), 255, random8(128, 255)));
  }

  noise16_2();

  FastLED.show();

}









void noise16_3() {                                            // no x/y shifting but scrolling along

  uint8_t scale = 1000;                                       // the "zoom factor" for the noise

  for (uint16_t i = 0; i < configured_leds; i++) {

    uint16_t shift_x = 4223;                                  // no movement along x and y
    uint16_t shift_y = 1234;

    uint32_t real_x = (i + shift_x) * scale;                  // calculate the coordinates within the noise field
    uint32_t real_y = (i + shift_y) * scale;                  // based on the precalculated positions
    uint32_t real_z = millis() * 2;                           // increment z linear

    uint8_t noise = inoise16(real_x, real_y, real_z) >> 7;    // get the noise data and scale it down

    uint8_t index = sin8(noise * 3);                          // map led color based on noise data
    uint8_t bri   = noise;

    leds[i] = ColorFromPalette(currentPalette, index, bri, LINEARBLEND);   // With that value, look up the 8 bit colour palette value and assign it to the current LED.
  }

}


void runNoise16_3() {

  EVERY_N_MILLISECONDS(50) {
    nblendPaletteTowardPalette(currentPalette, targetPalette, 24);  // Blend towards the target palette
  }

  EVERY_N_SECONDS(5) {             // Change the target palette to a random one every 5 seconds.
    targetPalette = CRGBPalette16(CHSV(random8(), 255, random8(128, 255)), CHSV(random8(), 255, random8(128, 255)), CHSV(random8(), 192, random8(128, 255)), CHSV(random8(), 255, random8(128, 255)));
  }

  noise16_3();

  FastLED.show();

}
