/**
 * Simple clock display interface, power consumption is about 20mA
 * Written by lewishe
 * */

// #define LILYGO_TWATCH_2020_V1        // If you are using T-Watch-2020 version, please open this macro definition
#include <TTGO.h>

#define LV_COLOR_WBLUE LV_COLOR_MAKE(0x00, 0x50, 0xA0)
#define LV_COLOR_WBORA LV_COLOR_MAKE(0xF6, 0x92, 0x00)

typedef struct {
    lv_obj_t *year;
    lv_obj_t *month;
    lv_obj_t *day;
    lv_obj_t *hour;
    lv_obj_t *minute;
    lv_obj_t *second;
} str_datetime_t;


static str_datetime_t g_data;
TTGOClass *watch = nullptr;
PCF8563_Class *rtc;
LV_IMG_DECLARE(watchface);
LV_IMG_DECLARE(kickstart);
LV_FONT_DECLARE(Topaz_16);
uint8_t ticks = 0; // internal 8-bit counter
int stats = 1;

float sx = 0, sy = 1, mx = 1, my = 0, hx = -1, hy = 0;    // Saved H, M, S x & y multipliers
float sdeg = 0, mdeg = 0, hdeg = 0;
uint16_t osx = 120, osy = 120, omx = 120, omy = 120, ohx = 120, ohy = 120; // Saved H, M, S x & y coords
uint16_t x0 = 0, x1 = 0, yy0 = 0, yy1 = 0;

void setup()
{
    Serial.begin(115200);
    watch = TTGOClass::getWatch();
    watch->begin();
    watch->eTFT->fillScreen(TFT_LIGHTGREY);
    watch->lvgl_begin();
    rtc = watch->rtc;

    // Use compile time
    rtc->check();

    watch->openBL();

    //Lower the brightness
    //watch->bl->adjust(150);

    lv_obj_t *img1 = lv_img_create(lv_scr_act(), NULL);
    //lv_img_set_src(img1, &kickstart);
    //lv_obj_align(img1, NULL, LV_ALIGN_CENTER, 0, 0);
    //delay(1000);
    lv_img_set_src(img1, &watchface);
    lv_obj_align(img1, NULL, LV_ALIGN_CENTER, 0, 0);

    static lv_style_t hstyle; // header (screen bar) style
    lv_style_copy(&hstyle, &lv_style_pretty_color);
    hstyle.text.font  = &Topaz_16;
    hstyle.text.color = LV_COLOR_WBLUE;

    static lv_style_t style;
    lv_style_copy(&style, &lv_style_pretty_color);
    style.text.font  = &Topaz_16;
    style.text.color = LV_COLOR_WBLUE;

    lv_obj_t * stitle = lv_label_create(img1, nullptr); // WB Screen Title Bar
    lv_label_set_style(stitle, LV_LABEL_STYLE_MAIN, &hstyle);
    lv_label_set_text(stitle, "Workbench release.");
    lv_obj_align(stitle, img1, LV_ALIGN_IN_TOP_LEFT, 2, 2);  

    lv_obj_t * atitle = lv_label_create(img1, nullptr); // WB App Title Bar
    lv_label_set_style(atitle, LV_LABEL_STYLE_MAIN, &hstyle);
    lv_label_set_text(atitle, "Clock V0.1");
    lv_obj_align(atitle, img1, LV_ALIGN_IN_TOP_LEFT, 32, 24);  

    style.text.color = LV_COLOR_WHITE;
    g_data.year = lv_label_create(img1, nullptr);
    lv_label_set_style(g_data.year, LV_LABEL_STYLE_MAIN, &style);
    lv_label_set_text(g_data.year, "00");
    lv_obj_align(g_data.year, img1, LV_ALIGN_IN_TOP_LEFT, 48, 220);

    g_data.month = lv_label_create(img1, nullptr);
    lv_label_set_style(g_data.month, LV_LABEL_STYLE_MAIN, &style);
    lv_label_set_text(g_data.month, "00");
    lv_obj_align(g_data.month, g_data.year, LV_ALIGN_OUT_RIGHT_MID, 8, 0);

    g_data.day = lv_label_create(img1, nullptr);
    lv_label_set_style(g_data.day, LV_LABEL_STYLE_MAIN, &style);
    lv_label_set_text(g_data.day, "00");
    lv_obj_align(g_data.day, g_data.month, LV_ALIGN_OUT_RIGHT_MID, 8, 0);

    g_data.hour = lv_label_create(img1, nullptr);
    lv_label_set_style(g_data.hour, LV_LABEL_STYLE_MAIN, &style);
    lv_label_set_text(g_data.hour, "00");
    lv_obj_align(g_data.hour, g_data.day, LV_ALIGN_OUT_RIGHT_MID, 16, 0);

    g_data.minute = lv_label_create(img1, nullptr);
    lv_label_set_style(g_data.minute, LV_LABEL_STYLE_MAIN, &style);
    lv_label_set_text(g_data.minute, "00");
    lv_obj_align(g_data.minute, g_data.hour, LV_ALIGN_OUT_RIGHT_MID, 8, 0);

    g_data.second = lv_label_create(img1, nullptr);
    lv_label_set_style(g_data.second, LV_LABEL_STYLE_MAIN, &style);
    lv_label_set_text(g_data.second, "00");
    lv_obj_align(g_data.second, g_data.minute, LV_ALIGN_OUT_RIGHT_MID, 8, 0);

    // Clock face


    lv_task_create([](lv_task_t *t) {        
      RTC_Date curr_datetime = rtc->getDateTime();
      lv_label_set_text_fmt(g_data.second, "%02u", curr_datetime.second);
      lv_label_set_text_fmt(g_data.minute, "%02u:", curr_datetime.minute);
      lv_label_set_text_fmt(g_data.hour, "%02u:", curr_datetime.hour);
      lv_label_set_text_fmt(g_data.day, "%02u", curr_datetime.day);
      lv_label_set_text_fmt(g_data.month, "%02u/", curr_datetime.month);
      lv_label_set_text_fmt(g_data.year, "%02d/", curr_datetime.year % 100);


    }, 1000, LV_TASK_PRIO_MID, nullptr);

    // Set 20MHz operating speed to reduce power consumption
    setCpuFrequencyMhz(20);

}

void loop()
{
    lv_task_handler();
}
