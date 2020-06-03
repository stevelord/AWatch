
// #define LILYGO_TWATCH_2020_V1        // If you are using T-Watch-2020 version, please open this macro definition
#include <TTGO.h>
#include "gui.h"

#define LV_COLOR_WBLUE LV_COLOR_MAKE(0x00, 0x50, 0xA0)
#define LV_COLOR_WBORA LV_COLOR_MAKE(0xF6, 0x92, 0x00)

#define swap_coord(a,b) a^=b^=a^=b;

TTGOClass *ttgo;

//swap any type
//template <typename T> static inline void
//swap_coord(T& a, T& b) { T t = a; a = b; b = t; }

static void event_handler(lv_obj_t *obj, lv_event_t event)
{
    if (event == LV_EVENT_CLICKED) {
        Serial.printf("Clicked\n");
    } else if (event == LV_EVENT_VALUE_CHANGED) {
        Serial.printf("Toggled\n");
    }
}


void setup()
{
    Serial.begin(115200);
    ttgo = TTGOClass::getWatch();
    ttgo->begin();
    ttgo->openBL();
    ttgo->eTFT->fillScreen(TFT_BLACK);
    ttgo->lvgl_begin();

    setupGui();

}

void loop()
{
    lv_task_handler();
    delay(5);
}
