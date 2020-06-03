
#include <TTGO.h>

TTGOClass *ttgo;

char buf[128];
bool rtcIrq = false;

void setup()
{
    Serial.begin(115200);
    ttgo = TTGOClass::getWatch();
    ttgo->begin();
    ttgo->openBL();
    
    ttgo->eTFT->fillScreen(TFT_BLACK);
    ttgo->rtc->clearTimer();

    pinMode(RTC_INT, INPUT_PULLUP);
    attachInterrupt(RTC_INT, [] {
        Serial.printf("Interrupt attached at %s\n", ttgo->rtc->formatDateTime());
        ttgo->rtc->disableTimer();
        ttgo->rtc->clearTimer();
        rtcIrq = 1;
        Serial.println("End of ISR");
    }, FALLING);
    
    

    Serial.printf("Setting timer for 1 minute\n");// at %s\n", ttgo->rtc->formatDateTime());
    ttgo->rtc->disableTimer();
    ttgo->rtc->setTimer(5,2,false);

    ttgo->rtc->enableTimer();
}

void loop()
{
    ttgo->eTFT->setTextColor(random(0xFFFF));
    ttgo->eTFT->drawString("T-Watch RTC",  50, 50, 4);

    ttgo->eTFT->setTextColor(TFT_YELLOW, TFT_BLACK);
    Serial.printf("It's %s\n", ttgo->rtc->formatDateTime());
    snprintf(buf, sizeof(buf), "%s", ttgo->rtc->formatDateTime());
    ttgo->eTFT->drawString(buf, 5, 118, 7);
    if (rtcIrq) {
        Serial.printf("rtcIrq ready at %s. Detaching and clearing.\n", ttgo->rtc->formatDateTime());
        rtcIrq = 0;
        //detachInterrupt(RTC_INT);
        //ttgo->rtc->clearTimer();
        //ttgo->rtc->disableTimer();
        int i = 3;
        while (i--) {
            ttgo->eTFT->fillScreen(TFT_RED);
            ttgo->eTFT->setTextColor(TFT_WHITE, TFT_RED);
            ttgo->eTFT->drawString("RTC Timer", 60, 118, 4);
            delay(500);
            ttgo->eTFT->fillScreen(TFT_BLACK);
            ttgo->eTFT->setTextColor(TFT_WHITE, TFT_BLACK);
            ttgo->eTFT->drawString("RTC Timer", 60, 118, 4);
            delay(500);
        }
    }
    delay(1000);
}
