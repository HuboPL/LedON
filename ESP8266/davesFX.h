void comet()
{
  const byte fadeAmt = 128;
  const int cometSize = 5;
  const int deltaHue  = 4;

  static byte hue = HUE_RED;
  static int iDirection = 1;
  static int iPos = 0;

  hue += deltaHue;

  iPos += iDirection;
  if (iPos == (configured_leds - cometSize) || iPos == 0)
    iDirection *= -1;

  for (int i = 0; i < cometSize; i++)
    leds[iPos + i].setHue(hue);

  // Randomly fade the LEDs
  for (int j = 0; j < configured_leds; j++)
    if (random(10) > 5)
      leds[j] = leds[j].fadeToBlackBy(fadeAmt);

  FastLED.delay(30);
}







#include <sys/time.h>                   
#include <vector>
using namespace std;
#define ARRAYSIZE(x) (sizeof(x)/sizeof(x[0]))   


static const CRGB ballColors [] =
{
  CRGB::Green,
  CRGB::Red,
  CRGB::Blue,
  CRGB::Orange,
  CRGB::Indigo
};

class BouncingBallEffect
{
  private:

    double InitialBallSpeed(double height) const
    {
      return sqrt(-2 * Gravity * height);         // Because MATH!
    }

    size_t  _cLength;
    size_t  _cBalls;
    byte    _fadeRate;
    bool    _bMirrored;

    const double Gravity = -9.81;                   // Because PHYSICS!
    const double StartHeight = 1;                   // Drop balls from max height initially
    const double ImpactVelocity = InitialBallSpeed(StartHeight);
    const double SpeedKnob = 4.0;                   // Higher values will slow the effect

    vector<double> ClockTimeAtLastBounce, Height, BallSpeed, Dampening;
    vector<CRGB>   Colors;

    static double Time()
    {
      timeval tv = { 0 };
      gettimeofday(&tv, nullptr);
      return (double)(tv.tv_usec / 1000000.0 + (double) tv.tv_sec);
    }

  public:

    // BouncingBallEffect
    //
    // Caller specs strip length, number of balls, persistence level (255 is least), and whether the
    // balls should be drawn mirrored from each side.

    BouncingBallEffect(size_t cLength, size_t ballCount = 3, byte fade = 0, bool bMirrored = false)
      : _cLength(cLength - 1),
        _cBalls(ballCount),
        _fadeRate(fade),
        _bMirrored(bMirrored),
        ClockTimeAtLastBounce(ballCount),
        Height(ballCount),
        BallSpeed(ballCount),
        Dampening(ballCount),
        Colors(ballCount)
    {
      for (size_t i = 0; i < ballCount; i++)
      {
        Height[i]                = StartHeight;         // Current Ball Height
        ClockTimeAtLastBounce[i] = Time();              // When ball last hit ground state
        Dampening[i]             = 0.90 - i / pow(_cBalls, 2);  // Bounciness of this ball
        BallSpeed[i]             = InitialBallSpeed(Height[i]); // Don't dampen initial launch
        Colors[i]                = ballColors[i % ARRAYSIZE(ballColors) ];
      }
    }
   

    virtual void Draw()
    {
      if (_fadeRate != 0)
      {
        for (size_t j = 0; j <= _cLength; j++)
          leds[j].fadeToBlackBy(_fadeRate);
      }
      else
        FastLED.clear();

      // Draw each of the balls

      for (size_t i = 0; i < _cBalls; i++)
      {
        double TimeSinceLastBounce = (Time() - ClockTimeAtLastBounce[i]) / SpeedKnob;
        Height[i] = 0.5 * Gravity * pow(TimeSinceLastBounce, 2.0) + BallSpeed[i] * TimeSinceLastBounce;

        // Ball hits ground - bounce!
        if (Height[i] < 0)
        {
          Height[i] = 0;
          BallSpeed[i] = Dampening[i] * BallSpeed[i];
          ClockTimeAtLastBounce[i] = Time();

          if (BallSpeed[i] < 0.01)
            BallSpeed[i] = InitialBallSpeed(StartHeight) * Dampening[i];
        }

        size_t position = (size_t)(Height[i] * (_cLength - 1) / StartHeight);

        leds[position]   += Colors[i];
        leds[position + 1] += Colors[i];

        if (_bMirrored)
        {
          leds[_cLength - 1 - position] += Colors[i];
          leds[_cLength - position]     += Colors[i];
        }
      }
      FastLED.show();
      FastLED.delay(20);
    }
};




void DrawMarquee()
{
    static byte j = 0;
    j+=4;
    byte k = j;

    // Roughly equivalent to fill_rainbow(leds, NUM_LEDS, j, 8);

    CRGB c;
    for (int i = 0; i < configured_leds; i ++)
        leds[i] = c.setHue(k+=8);

    static int scroll = 0;
    scroll++;

    for (int i = scroll % 5; i < configured_leds - 1; i += 5)
    {
        leds[i] = CRGB::Black;
    }
    delay(50);
}

void DrawMarqueeMirrored()
{
    static byte j = 0;
    j+=4;
    byte k = j;

    // Roughly equivalent to fill_rainbow(leds, configured_leds, j, 8);

    CRGB c;
    for (int i = 0; i < (configured_leds + 1) / 2; i ++)
    {
        leds[i] = c.setHue(k);
        leds[configured_leds - 1 - i] = c.setHue(k);
        k+= 8;
    }


    static int scroll = 0;
    scroll++;

    for (int i = scroll % 5; i < configured_leds / 2; i += 5)
    {
        leds[i] = CRGB::Black;
        leds[configured_leds - 1 - i] = CRGB::Black;
    }   

    delay(50);
}
