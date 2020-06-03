#pragma mark - Depend ESP8266Audio and ESP8266_Spiram libraries
/*
cd ~/Arduino/libraries
git clone https://github.com/earlephilhower/ESP8266Audio
git clone https://github.com/Gianbacchio/ESP8266_Spiram
*/

#include <TTGO.h>
#include <WiFi.h>
#include "AudioFileSourcePROGMEM.h"
#include "AudioFileSourceID3.h"
#include "AudioGeneratorWAV.h"
#include "AudioOutputI2S.h"

// VIOLA sample taken from https://ccrma.stanford.edu/~jos/pasp/Sound_Examples.html
#include "viola.h"

//! set 1 to external decoder playback,  set 0 to internal decoder
#define EXTERNAL_DAC_PLAY   0

TTGOClass *ttgo;
AudioGeneratorWAV *wav;
AudioFileSourcePROGMEM *file;
AudioOutputI2S *out;

void setup(void)
{
    WiFi.mode(WIFI_OFF);
    Serial.begin(115200);
    delay(1000);
    Serial.printf("WAV start\n");


    ttgo = TTGOClass::getWatch();
    ttgo->begin();
    ttgo->openBL();

    ttgo->eTFT->fillScreen(TFT_BLACK);
    ttgo->eTFT->setTextFont(2);

    ttgo->eTFT->setCursor(0, 0);
    ttgo->eTFT->fillScreen(TFT_BLACK);
    ttgo->eTFT->println("Setup()");

    file = new AudioFileSourcePROGMEM( viola, sizeof(viola) );

#if EXTERNAL_DAC_PLAY
    out = new AudioOutputI2S();
    out->SetPinout(TWATCH_DAC_IIS_BCK, TWATCH_DAC_IIS_WS, TWATCH_DAC_IIS_DOUT);
#else
    out = new AudioOutputI2S(0, 1);
#endif

    wav = new AudioGeneratorWAV();
    wav->begin(file, out);

    //!Turn on the audio power
    ttgo->enableLDO3();
}


void loop(void)
{
  if (wav->isRunning()) {
    if (!wav->loop()) wav->stop();
    } else {

        ttgo->eTFT->fillScreen(TFT_BLUE);
        ttgo->eTFT->setCursor(0, 0);
        ttgo->eTFT->println("wav play done , starting again ..");
        file = new AudioFileSourcePROGMEM( viola, sizeof(viola) );
        wav->begin(file, out);

        //delay(1000);
    }
}
