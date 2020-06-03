
bool hasPsram = true;

#include <stdint.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <TTGO.h>
#include "plasma.h"

#define DISPLAY_WIDTH TFT_WIDTH
#define DISPLAY_HEIGHT TFT_HEIGHT

TTGOClass *ttgo;

uint16_t *palette;
uint8_t *plasma;

static const uint8_t SPEED = 6;
static const uint8_t STEP = 2;

void plasma_init()
{
    plasma = (uint8_t *)malloc(DISPLAY_WIDTH * DISPLAY_HEIGHT * sizeof(uint8_t));
    palette = (uint16_t *)malloc(256 * sizeof(uint16_t));

    /* Generate nice continous palette. */
    for(int i = 0; i < 256; i++) {
        uint8_t r, g, b;
        r = 128.0 + 128.0 * sin((M_PI * i / 128.0) + 1);
        g = 128.0 + 128.0 * sin((M_PI * i / 64.0) + 1);
        b = 64;
        palette[i] = ttgo->eTFT->color565(r, g, b);
    }

    for (uint16_t x = 0; x < DISPLAY_WIDTH; x = x + STEP) {
        for (uint16_t y = 0; y < DISPLAY_HEIGHT; y = y + STEP) {
                /* Generate three different sinusoids. */
                float v1 = 128.0 + (128.0 * sin(x / 32.0));
                float v2 = 128.0 + (128.0 * sin(y / 24.0));
                float v3 = 128.0 + (128.0 * sin(sqrt(x * x + y * y) / 24.0));
                /* Calculate average of the three sinusoids */
                /* and use it as color. */
                uint8_t color = (v1 + v2 + v3) / 3;
                uint8_t *ptr = (plasma + DISPLAY_WIDTH * y + x);
                 *ptr = color;
        }
    }
}

void plasma_render()
{
    for (uint16_t x = 0; x < DISPLAY_WIDTH; x = x + STEP) {
        for (uint16_t y = 0; y < DISPLAY_HEIGHT; y = y + STEP) {
            /* Get a pixel from the plasma buffer. */
            uint8_t *ptr = (plasma + x + DISPLAY_WIDTH * y);
            uint16_t color = palette[*ptr];
            /* Put a pixel to the display. */
            ttgo->eTFT->drawPixel(x, y, color);
            //hagl_put_pixel(x, y, color);
        }
    }
}

void plasma_animate()
{
    for (uint16_t x = 0; x < DISPLAY_WIDTH; x = x + STEP) {
        for (uint16_t y = 0; y < DISPLAY_HEIGHT; y = y + STEP) {
                /* Get a pixel from the plasma buffer. */
                uint8_t *ptr = (plasma + x + DISPLAY_WIDTH * y);
                uint8_t color = *ptr;
                /* Choose next color from the palette. */
                color += SPEED;
                color %= 256;
                /* Put a pixel to the plasma buffer. */
                *ptr = color;
        }
    }
}


void setup() {

  Serial.begin(115200);
  ttgo = TTGOClass::getWatch();
  ttgo->begin();
  ttgo->openBL();

  ttgo->eTFT->setTextDatum(MC_DATUM);
  ttgo->eTFT->setTextColor(TFT_GREEN, TFT_BLACK);
  ttgo->eTFT->fillScreen(TFT_BLACK);

  plasma_init();
}

bool rendered = false;

void loop() {
  plasma_animate();
  plasma_render();

}
