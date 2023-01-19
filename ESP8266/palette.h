uint8_t paletteIndex = 0;
uint8_t colorIndex[NUM_LEDS];
uint8_t whichPalette = 0;

DEFINE_GRADIENT_PALETTE (heatmap_gp) {
  0,   0,   0,   0,   //black
  128, 255,   0,   0,   //red
  200, 255, 255,   0,   //bright yellow
  255, 255, 255, 255    //full white
};

DEFINE_GRADIENT_PALETTE( greenblue_gp ) {
  0,    0,  194,  255,     //light blue
  46,    3,    0,  246,     //dark blue
  176,   55,  222,   70,     //bright green
  255,    0,  194,  255      //light blue
};

DEFINE_GRADIENT_PALETTE( orangepink_gp ) {
  0,  255,  100,    0,     //orange
  90,  255,    0,  255,     //magenta
  150,  255,  100,    0,     //orange
  255,  255,  100,    0      //orange
};

DEFINE_GRADIENT_PALETTE( browngreen_gp ) {
  0,    6,  255,    0,     //green
  71,    0,  255,  153,     //bluegreen
  122,  200,  200,  200,     //gray
  181,  110,   61,    6,     //brown
  255,    6,  255,    0      //green
};

DEFINE_GRADIENT_PALETTE( Sunset_Real_gp ) {
  0, 120,  0,  0,
  22, 179, 22,  0,
  51, 255, 104,  0,
  85, 167, 22, 18,
  135, 100,  0, 103,
  198,  16,  0, 130,
  255,   0,  0, 160
};


//juicy
DEFINE_GRADIENT_PALETTE( juicy_gp ) {
  0, 255,  0,  0,
  127, 255, 255,  0,
  255,   0, 255,  0
};

//grateful
DEFINE_GRADIENT_PALETTE( grateful_gp ) {
  0, 255,  0,  0,
  127, 255, 255,  0,
  255,   0,  0, 255
};

//pastelle
DEFINE_GRADIENT_PALETTE( pastelle_gp ) {
  0,  92, 53, 240,
  89, 224, 157, 11,
  124, 255, 255, 45,
  198,  65, 144, 230,
  255,  65, 144, 230
};

//blueorange
DEFINE_GRADIENT_PALETTE( blueorange_gp ) {
  0,  12, 80, 210,
  127, 255, 235, 19,
  255, 224, 66, 15
};

//pinkgreen
DEFINE_GRADIENT_PALETTE( pinkgreen_gp ) {
  0, 229, 30, 50,
  84, 100, 11, 12,
  168,   3, 28,  2,
  255,  35, 119, 10
};

//mango
DEFINE_GRADIENT_PALETTE( mango_gp ) {
  0,  24, 55,  1,
  127, 244, 122,  6,
  255, 222, 36, 22
};

//light limonee
DEFINE_GRADIENT_PALETTE( limonee_gp ) {
  0,  20, 54, 45,
  127,  74, 178, 23,
  255, 224, 244, 17
};

//dreams
DEFINE_GRADIENT_PALETTE( dreams_gp ) {
  0,   1,  7, 67,
  127,  47, 29, 103,
  255, 167, 130, 17
};

//love
DEFINE_GRADIENT_PALETTE( love_gp ) {
  0,   7,  1, 10,
  127,  87,  7, 13,
  255, 150, 88, 16
};

CRGBPalette16 purplePalette = CRGBPalette16 (
                                CRGB::DarkViolet,
                                CRGB::DarkViolet,
                                CRGB::DarkViolet,
                                CRGB::DarkViolet,

                                CRGB::Magenta,
                                CRGB::Magenta,
                                CRGB::Linen,
                                CRGB::Linen,

                                CRGB::Magenta,
                                CRGB::Magenta,
                                CRGB::DarkViolet,
                                CRGB::DarkViolet,

                                CRGB::DarkViolet,
                                CRGB::DarkViolet,
                                CRGB::Linen,
                                CRGB::Linen
                              );


                              

CRGBPalette16 heatPalette = heatmap_gp;
void heatMap()
{
  fill_palette(leds, configured_leds, paletteIndex, 255 / configured_leds, heatPalette, 255, LINEARBLEND);
  EVERY_N_MILLISECONDS(10) {
    paletteIndex++;
  }
  FastLED.show();
}





CRGBPalette16 currentPalette(greenblue_gp);
CRGBPalette16 targetPalette(orangepink_gp);
CRGBPalette16 greenblue = greenblue_gp;

void paletteBlendingIndex() {
  for (int i = 0; i < configured_leds; i++) {
    colorIndex[i] = random8();
  }
}

void paletteBlending() {
  fill_palette(leds, configured_leds, paletteIndex, 255 / configured_leds, currentPalette, 255, LINEARBLEND);
  // Color each pixel from the palette using the index from colorIndex[]
  for (int i = 0; i < configured_leds; i++) {
    leds[i] = ColorFromPalette(currentPalette, colorIndex[i]);
  }

  nblendPaletteTowardPalette( currentPalette, targetPalette, 10 );

  switch (whichPalette) {
    case 0:
      targetPalette = orangepink_gp;
      break;
    case 1:
      targetPalette = browngreen_gp;
      break;
    case 2:
      targetPalette = greenblue_gp;
      break;
  }

  EVERY_N_SECONDS(10) {
    whichPalette++;
    if (whichPalette > 2) whichPalette = 0;
  }

  EVERY_N_MILLISECONDS(5) {
    for (int i = 0; i < configured_leds; i++) {
      colorIndex[i]++;
    }
  }

  FastLED.show();
}






void seaGradient() {
  fill_palette(leds, configured_leds, paletteIndex, 255 / configured_leds, greenblue, 255, LINEARBLEND);
  // Color each pixel from the palette using the index from colorIndex[]
  for (int i = 0; i < configured_leds; i++) {
    leds[i] = ColorFromPalette(greenblue, colorIndex[i]);
  }

  EVERY_N_MILLISECONDS(5) {
    for (int i = 0; i < configured_leds; i++) {
      colorIndex[i]++;
    }
  }
  FastLED.show();
}





CRGBPalette16 knifePal = Sunset_Real_gp;

void paletteKnife() {
  fill_palette(leds, configured_leds, paletteIndex, 255 / configured_leds, knifePal, 255, LINEARBLEND);

  EVERY_N_MILLISECONDS(10) {
    paletteIndex++;
  }

  FastLED.show();
}






//BLACKENED



CRGBPalette16 blckndPalette = juicy_gp;


void blackened() {

  EVERY_N_MILLISECONDS(50) {
    //Switch on an LED at random, choosing a random color from the palette
    leds[random8(0, configured_leds - 1)] = ColorFromPalette(blckndPalette, random8(), 255, LINEARBLEND);
  }

  // Fade all LEDs down by 1 in brightness each time this is called
  fadeToBlackBy(leds, configured_leds, 1);

  FastLED.show();
}
