/* Starfield Sketch */

#include <TTGO.h>


TTGOClass *ttgo;

unsigned long drawTime = 0;

// With 1024 stars the update rate is ~65 frames per second
#define NSTARS 1024
#define WIDTH 240
#define HEIGHT 240
uint8_t sx[NSTARS] = {};
uint8_t sy[NSTARS] = {};
uint8_t sz[NSTARS] = {};

uint8_t za, zb, zc, zx;

// Fast 0-255 random number generator from http://eternityforest.com/Projects/rng.php:
uint8_t __attribute__((always_inline)) rng()
{
  zx++;
  za = (za^zc^zx);
  zb = (zb+za);
  zc = (zc+(zb>>1)^za);
  return zc;
}

void setup(void)
{
    za = random(256);
    zb = random(256);
    zc = random(256);
    zx = random(256);
    Serial.begin(115200); // Used for messages
    ttgo = TTGOClass::getWatch();
    ttgo->begin();
    ttgo->openBL();
    ttgo->eTFT->fillScreen(TFT_BLACK);

}

void loop()
{
  
    unsigned long t0 = micros();
    uint8_t spawnDepthVariation = 255;
  
    for(int i = 0; i < NSTARS; ++i)
    {
      if (sz[i] <= 1)
      {
        sx[i] = (WIDTH/2) - (HEIGHT/2) + rng();
        sy[i] = rng();
        sz[i] = spawnDepthVariation--;
      }
      else
      {
        int old_screen_x = ((int)sx[i] - (WIDTH/2)) * 256 / sz[i] + (WIDTH/2);
        int old_screen_y = ((int)sy[i] - (HEIGHT/2)) * 256 / sz[i] + (HEIGHT/2);
  
        // This is a faster pixel drawing function for occassions where many single pixels must be drawn
        ttgo->eTFT->drawPixel(old_screen_x, old_screen_y,TFT_BLACK);
  
        sz[i] -= 2;
        if (sz[i] > 1)
        {
          int screen_x = ((int)sx[i] - (WIDTH/2)) * 256 / sz[i] + (WIDTH/2);
          int screen_y = ((int)sy[i] - (HEIGHT/2)) * 256 / sz[i] + (HEIGHT/2);
    
          if (screen_x >= 0 && screen_y >= 0 && screen_x < WIDTH && screen_y < HEIGHT)
          {
            uint8_t r, g, b;
            r = g = b = 255 - sz[i];
            ttgo->eTFT->drawPixel(screen_x, screen_y, ttgo->eTFT->color565(r,g,b));
          }
          else
            sz[i] = 0; // Out of screen, die.
        }
      }
    }
    unsigned long t1 = micros();
    //static char timeMicros[8] = {};
  
   // Calcualte frames per second
    Serial.println(1.0/((t1 - t0)/1000000.0));

}
