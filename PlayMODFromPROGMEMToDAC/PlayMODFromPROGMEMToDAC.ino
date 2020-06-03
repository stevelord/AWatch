#include <TTGO.h>
#include "AudioFileSourcePROGMEM.h"
#include "AudioGeneratorMOD.h"
#include "AudioOutputI2S.h"
#ifdef ESP32
    #include <WiFi.h>
#else
    #include <ESP8266WiFi.h>
#endif

// enigma.mod sample from the mod archive: https://modarchive.org/index.php?request=view_by_moduleid&query=42146
#include "enigma.h"

TTGOClass *ttgo;
AudioGeneratorMOD *mod;
AudioFileSourcePROGMEM *file;
AudioOutputI2S *out;

void setup()
{
  WiFi.mode(WIFI_OFF); //WiFi.forceSleepBegin();
  Serial.begin(115200);
  delay(1000);

  ttgo = TTGOClass::getWatch();
  ttgo->begin();
  ttgo->openBL();
  ttgo->eTFT->fillScreen(TFT_BLACK);
  ttgo->eTFT->setTextFont(2);

  ttgo->eTFT->setCursor(0, 0);
  ttgo->eTFT->fillScreen(TFT_BLACK);
  ttgo->eTFT->println("Sample MOD playback begins");

  // pno_cs from https://ccrma.stanford.edu/~jos/pasp/Sound_Examples.html
  //!Turn on the audio power
  ttgo->enableLDO3();

  audioLogger = &Serial;
  file = new AudioFileSourcePROGMEM( enigma_mod, sizeof(enigma_mod) );
  out = new AudioOutputI2S(0, 1); // Uncomment this line, comment the next one to use the internal DAC channel 1 (pin25) on ESP32
  //out = new AudioOutputI2S();
  mod = new AudioGeneratorMOD();
  mod->SetBufferSize(3*1024);
  mod->SetSampleRate(44100);
  mod->SetStereoSeparation(32);
  mod->begin(file, out);
}

void loop()
{
  if (mod->isRunning()) {
    if (!mod->loop()) mod->stop();
  } else {
    Serial.printf("MOD done\n");
    delay(1000);
  }
}
