/*
Copyright (c) 2019 lewis he
This is just a demonstration. Most of the functions are not implemented.
The main implementation is low-power standby. 
The off-screen standby (not deep sleep) current is about 4mA.
Select standard motherboard and standard backplane for testing.
Created by Lewis he on October 10, 2019.
*/

#ifndef __GUI_H
#define __GUI_H

#include <TTGO.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"
#include "freertos/queue.h"
#include <soc/rtc.h>
#include "esp_wifi.h"
#include <WiFi.h>
#include "AudioFileSourcePROGMEM.h"
#include "AudioGeneratorMOD.h"
#include "AudioOutputI2S.h"
#include "elysium.h"
#include "chaos.h"
#include "pxloader.h"

//extern AudioFileSourcePROGMEM *file;
extern uint8_t song_index;
extern uint8_t mod_mode; // Modplayer mode: 0 = Stopped, 1 = Initialise, 2 = Playing
extern uint32_t timer_left;
extern bool timer_active;
extern bool alarm_active;
extern bool speech_active;
extern bool anim_active;
extern uint8_t anim_frame;
extern unsigned char songs[3];
extern char saytext[64];
//extern const unsigned char *songs[3] = {ELYSIUM_MOD, Chaos_Engine_k8_mod, Project_X_RE_pxloader_mod};
//extern bool timer_active = false;
//extern uint8_t timer_left;
//extern uint8_t timer_min;
//static AudioGeneratorMOD *mod;
//static AudioFileSourcePROGMEM *file;
//static AudioOutputI2S *out;

typedef enum {
    LV_ICON_BAT_EMPTY,
    LV_ICON_BAT_1,
    LV_ICON_BAT_2,
    LV_ICON_BAT_3,
    LV_ICON_BAT_FULL,
    LV_ICON_CHARGE,
    LV_ICON_CALCULATION
} lv_icon_battery_t;


typedef enum {
    LV_STATUS_BAR_BATTERY_LEVEL = 0,
    LV_STATUS_BAR_BATTERY_ICON = 1,
    LV_STATUS_BAR_WIFI = 2,
    LV_STATUS_BAR_BLUETOOTH = 3,
    LV_STATUS_BAR_BELL=4,
} lv_icon_status_bar_t;

void setupGui();
void updateStepCounter(uint32_t counter);
void updateBatteryIcon(lv_icon_battery_t index);
void wifi_list_add(const char *ssid);
void wifi_connect_status(bool result);
void updateBatteryLevel();

#endif /*__GUI_H */
