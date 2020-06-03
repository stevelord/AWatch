
#include <TTGO.h>

TTGOClass *ttgo;

char buf[128];
bool rtcIrq = false;
RTC_Date date;

void setup()
{
    Serial.begin(115200);
    ttgo = TTGOClass::getWatch();
    ttgo->begin();
    ttgo->openBL();
    
    ttgo->eTFT->fillScreen(TFT_BLACK);
    Serial.println("Setting IRQ trigger");
    pinMode(RTC_INT, INPUT_PULLUP);
    attachInterrupt(RTC_INT, [] {
        rtcIrq = 1;
        Serial.println("RTC ISR");
    }, FALLING);

    ttgo->rtc->disableAlarm();

    /*Serial.println("Checking RTC. Time at get point:");
    ttgo->rtc->check();
    date = ttgo->rtc->getDateTime();
    Serial.println(ttgo->rtc->formatDateTime());
    ttgo->rtc->setDateTime(date);
    Serial.println("Time at set point:");
    Serial.println(ttgo->rtc->formatDateTime());*/

    //ttgo->rtc->setDateTime(2019, 8, 12, 15, 0, 53);
    date = ttgo->rtc->getDateTime();
    ttgo->rtc->setDateTime(date);
    
    Serial.print("Setting alarm for one minute as of ");
    Serial.println(ttgo->rtc->formatDateTime());
    ttgo->rtc->setAlarmByMinutes(1);

    ttgo->rtc->enableAlarm();
}

void loop()
{
    ttgo->eTFT->setTextColor(random(0xFFFF));
    ttgo->eTFT->drawString("T-Watch RTC",  50, 50, 4);

    ttgo->eTFT->setTextColor(TFT_YELLOW, TFT_BLACK);
    snprintf(buf, sizeof(buf), "%s", ttgo->rtc->formatDateTime());
    ttgo->eTFT->drawString(buf, 5, 118, 7);
    if (rtcIrq) {
        Serial.println("rtcIrq fired");
        rtcIrq = 0;
        detachInterrupt(RTC_INT);
        Serial.println("Interrupt detached, resetting alarm and going into loop");
        ttgo->rtc->resetAlarm();
        int i = 3;
        while (i--) {
            ttgo->eTFT->fillScreen(TFT_RED);
            ttgo->eTFT->setTextColor(TFT_WHITE, TFT_RED);
            ttgo->eTFT->drawString("RTC Alarm", 60, 118, 4);
            delay(500);
            ttgo->eTFT->fillScreen(TFT_BLACK);
            ttgo->eTFT->setTextColor(TFT_WHITE, TFT_BLACK);
            ttgo->eTFT->drawString("RTC Alarm", 60, 118, 4);
            delay(500);
        }
    }
    delay(1000);
}
