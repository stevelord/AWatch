#pragma mark - Depend ESP8266Audio and ESP8266_Spiram libraries
/*
cd ~/Arduino/libraries
git clone https://github.com/earlephilhower/ESP8266Audio
git clone https://github.com/Gianbacchio/ESP8266_Spiram
*/

#include <TTGO.h>
#include <WiFi.h>
#include "AudioFileSourcePROGMEM.h"
#include "AudioGeneratorMOD.h"
#include "AudioOutputI2S.h"

#include "elysium.h"

TTGOClass *ttgo;
AudioGeneratorMOD *mod;
AudioFileSourcePROGMEM *file;
AudioOutputI2S *out;

void setup()
{
    WiFi.mode(WIFI_OFF);
    delay(500);

    Serial.begin(115200);
    ttgo = TTGOClass::getWatch();
    ttgo->begin();
    ttgo->openBL();
    ttgo->eTFT->fillScreen(TFT_BLACK);
    ttgo->eTFT->setTextFont(2);
   
    ttgo->eTFT->setCursor(0, 0);
    ttgo->eTFT->fillScreen(TFT_BLACK);
    ttgo->eTFT->println("Playing Elysium.mod");
    
    // pno_cs from https://ccrma.stanford.edu/~jos/pasp/Sound_Examples.html
    //!Turn on the audio power
    ttgo->enableLDO3();

    file = new AudioFileSourcePROGMEM( ELYSIUM_MOD, sizeof(ELYSIUM_MOD) );
    // out = new AudioOutputI2S(0, 1); Uncomment this line, comment the next one to use the internal DAC channel 1 (pin25) on ESP32
    out = new AudioOutputI2S(0,1);
    mod = new AudioGeneratorMOD();
    mod->SetBufferSize(3*1024);
    mod->SetSampleRate(44100);
    mod->SetStereoSeparation(32);
    mod->begin(file, out);
}

void loop()
{
  Serial.println("In loop");
  /*if (mod->isRunning()) {
    Serial.println("Mod running");
    if (!mod->loop()) mod->stop();
  } else {
    ttgo->eTFT->println("MOD playback done");
    Serial.printf("MOD done\n");*/
    delay(1000);
  //}
}
