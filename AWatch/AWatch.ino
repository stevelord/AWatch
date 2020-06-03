/*
  Copyright (c) 2019 lewis he
  This is just a demonstration. Most of the functions are not implemented.
  The main implementation is low-power standby.
  The off-screen standby (not deep sleep) current is about 4mA.
  Select standard motherboard and standard backplane for testing.
  Created by Lewis he on October 10, 2019.
*/

#pragma mark - Depend ArduinoJson ibraries
/*
  cd ~/Arduino/libraries
  git clone https://github.com/bblanchon/ArduinoJson.git
*/

// #define LILYGO_TWATCH_2020_V1        // If you are using T-Watch-2020 version, please open this macro definition

#include <TTGO.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"
#include "freertos/queue.h"
#include <soc/rtc.h>
#include "esp_wifi.h"
#include <WiFi.h>
#include <time.h>
#include "gui.h"
//#include "elysium.h"
//#include "chaos.h"
//#include "pxloader.h"
#include "SPIFFS.h"
//#include "AudioFileSourcePROGMEM.h"
#include "AudioFileSourceSPIFFS.h"
#include "AudioGeneratorMOD.h"
#include "AudioOutputI2S.h"
#include <ESP8266SAM.h>

bool timer_active = false;
bool alarm_active = false;
bool speech_active = false;
uint8_t song_index = 2;
uint8_t mod_mode; // Modplayer mode: 0 = Stopped, 1 = Initialise, 2 = Playing
uint32_t timer_left = 0; // Time left on timer
uint8_t pwr_mode = 0; // Power mode: 0 = full power, 1 = low energy (no audio), 2 = medium energy (no lv_event processing, audio enabled)
uint8_t last_sec = 0;
unsigned char songs[3];
char saytext[64];
AudioGeneratorMOD *mod;
//AudioFileSourceSPIFFS *file;
AudioFileSourcePROGMEM *file;
//AudioFileSourcePROGMEM *s1;
//AudioFileSourcePROGMEM *s2;
AudioOutputI2S *out;
ESP8266SAM *sam = new ESP8266SAM;

#define G_EVENT_VBUS_PLUGIN         _BV(0)
#define G_EVENT_VBUS_REMOVE         _BV(1)
#define G_EVENT_CHARGE_DONE         _BV(2)

#define G_EVENT_WIFI_SCAN_START     _BV(3)
#define G_EVENT_WIFI_SCAN_DONE      _BV(4)
#define G_EVENT_WIFI_CONNECTED      _BV(5)
#define G_EVENT_WIFI_BEGIN          _BV(6)
#define G_EVENT_WIFI_OFF            _BV(7)

enum {
  Q_EVENT_WIFI_SCAN_DONE,
  Q_EVENT_WIFI_CONNECT,
  Q_EVENT_BMA_INT,
  Q_EVENT_AXP_INT,
} ;

#define DEFAULT_SCREEN_TIMEOUT  30*1000

#define WATCH_FLAG_SLEEP_MODE   _BV(1)
#define WATCH_FLAG_SLEEP_EXIT   _BV(2)
#define WATCH_FLAG_BMA_IRQ      _BV(3)
#define WATCH_FLAG_AXP_IRQ      _BV(4)

QueueHandle_t g_event_queue_handle = NULL;
EventGroupHandle_t g_event_group = NULL;
EventGroupHandle_t isr_group = NULL;
bool lenergy = false;
bool lemode = false;
TTGOClass *ttgo;

void setupNetwork()
{
  WiFi.mode(WIFI_STA);
  WiFi.onEvent([](WiFiEvent_t event, WiFiEventInfo_t info) {
    xEventGroupClearBits(g_event_group, G_EVENT_WIFI_CONNECTED);
  }, WiFiEvent_t::SYSTEM_EVENT_STA_DISCONNECTED);

  WiFi.onEvent([](WiFiEvent_t event, WiFiEventInfo_t info) {
    uint8_t data = Q_EVENT_WIFI_SCAN_DONE;
    xQueueSend(g_event_queue_handle, &data, portMAX_DELAY);
  }, WiFiEvent_t::SYSTEM_EVENT_SCAN_DONE);

  WiFi.onEvent([](WiFiEvent_t event, WiFiEventInfo_t info) {
    xEventGroupSetBits(g_event_group, G_EVENT_WIFI_CONNECTED);
  }, WiFiEvent_t::SYSTEM_EVENT_STA_CONNECTED);

  WiFi.onEvent([](WiFiEvent_t event, WiFiEventInfo_t info) {
    wifi_connect_status(true);
  }, WiFiEvent_t::SYSTEM_EVENT_STA_GOT_IP);
}



void low_energy()
{
  if (ttgo->bl->isOn()) {
    //Serial.printf("low_energy() power down. Current Power Mode %u, timer_active %u, timer_left %u, mod_mode %u\n", pwr_mode, timer_active, timer_left, mod_mode);
    //delay(500);
    pwr_mode = 1;
    if (mod_mode > 0 || timer_active || timer_left > 0) pwr_mode++; // This allows us to keep audio and timer running at the cost of some power saving
    if (pwr_mode == 1) {
      Serial.println("Setting group bits");
      xEventGroupSetBits(isr_group, WATCH_FLAG_SLEEP_MODE);
    }
    ttgo->closeBL();
    ttgo->stopLvglTick();
    ttgo->bma->enableStepCountInterrupt(false);
    ttgo->displaySleep();
    if (pwr_mode == 1) {
      if (!WiFi.isConnected()) {
        lenergy = true;
        WiFi.mode(WIFI_OFF);
        Serial.println("Scaling down CPU freq.");
        rtc_clk_cpu_freq_set(RTC_CPU_FREQ_2M);
      }
    }
    Serial.printf("Pwr Mode reached: %u", pwr_mode);
    lemode = true;
  } else {
    ttgo->startLvglTick();
    ttgo->displayWakeup();
    ttgo->rtc->syncToSystem();
    updateStepCounter(ttgo->bma->getCounter());
    updateBatteryLevel();
    updateBatteryIcon(LV_ICON_CALCULATION);
    lv_disp_trig_activity(NULL);
    ttgo->openBL();
    ttgo->bma->enableStepCountInterrupt();
    Serial.println("Leaving low energy mode.");
    pwr_mode = 0;
  }
}

void setup()
{
  Serial.begin(115200);
  Serial.println("Kickstart");

  //Initialize SPIFFS
  SPIFFS.begin();

  //Initialize songs and audio
  mod_mode = 0; // Modplayer mode: 0 = Stopped, 1 = Initialise, 2 = Playing
  mod = new AudioGeneratorMOD();
  //s0 = new AudioFileSourcePROGMEM( ELYSIUM_MOD, sizeof(ELYSIUM_MOD) );
  //s1 = new AudioFileSourcePROGMEM( Chaos_Engine_k8_mod, sizeof(Chaos_Engine_k8_mod) );
  //s2 = new AudioFileSourcePROGMEM( Project_X_RE_pxloader_mod, sizeof(Project_X_RE_pxloader_mod) );  

  out = new AudioOutputI2S(0, 1);
  out->begin();
  
  //out->SetGain((70.0)/100.0);
  //out->SetGain(((float)40)/100.0);

  //Create a program that allows the required message objects and group flags
  g_event_queue_handle = xQueueCreate(20, sizeof(uint8_t));
  g_event_group = xEventGroupCreate();
  isr_group = xEventGroupCreate();

  //Instantiate ttgo watch object
  ttgo = TTGOClass::getWatch();

  //Initialize TWatch
  ttgo->begin();

  Serial.println("Setting power management.");
  // Turn on the IRQ used
  ttgo->power->adc1Enable(AXP202_BATT_VOL_ADC1 | AXP202_BATT_CUR_ADC1 | AXP202_VBUS_VOL_ADC1 | AXP202_VBUS_CUR_ADC1, AXP202_ON);
  ttgo->power->enableIRQ(AXP202_VBUS_REMOVED_IRQ | AXP202_VBUS_CONNECT_IRQ | AXP202_CHARGING_FINISHED_IRQ , AXP202_ON );
  ttgo->power->clearIRQ();

  // Turn off unused power
  ttgo->power->setPowerOutPut(AXP202_EXTEN, AXP202_OFF);
  ttgo->power->setPowerOutPut(AXP202_DCDC2, AXP202_OFF);
  ttgo->power->setPowerOutPut(AXP202_LDO3, AXP202_OFF);
  ttgo->power->setPowerOutPut(AXP202_LDO4, AXP202_OFF);

  Serial.println("Sound init.");
  //Initialize sound
  ttgo->enableLDO3();
  mod->SetBufferSize(3 * 1024);
  mod->SetSampleRate(44100);
  mod->SetStereoSeparation(32);

  Serial.println("GUI Init");
  //Initialize lvgl
  ttgo->lvgl_begin();

  //Initialize bma423
  ttgo->bma->begin();

  //Enable BMA423 interrupt
  ttgo->bma->attachInterrupt();


  // Connection interrupted to the specified pin
  pinMode(BMA423_INT1, INPUT);
  attachInterrupt(BMA423_INT1, [] {
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    EventBits_t  bits = xEventGroupGetBitsFromISR(isr_group);
    if (bits & WATCH_FLAG_SLEEP_MODE)
    {
      Serial.println("WATCH_FLAG_SLEEP_MODE in BMA423");
      //! For quick wake up, use the group flag
      xEventGroupSetBitsFromISR(isr_group, WATCH_FLAG_SLEEP_EXIT | WATCH_FLAG_BMA_IRQ, &xHigherPriorityTaskWoken);
    } else
    {
      Serial.println("Sending ISR Data Q_EVENT_BMA_INT in BMA423");
      uint8_t data = Q_EVENT_BMA_INT;
      xQueueSendFromISR(g_event_queue_handle, &data, &xHigherPriorityTaskWoken);
    }

    if (xHigherPriorityTaskWoken)
    {
      Serial.println("Higher priority task woken in BMA423");
      portYIELD_FROM_ISR ();
    }
  }, RISING);

  // Connection interrupted to the specified pin
  pinMode(AXP202_INT, INPUT);
  attachInterrupt(AXP202_INT, [] {
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    EventBits_t  bits = xEventGroupGetBitsFromISR(isr_group);
    if (bits & WATCH_FLAG_SLEEP_MODE)
    {
      Serial.println("WATCH_FLAG_SLEEP_MODE in AXP");
      //! For quick wake up, use the group flag
      xEventGroupSetBitsFromISR(isr_group, WATCH_FLAG_SLEEP_EXIT | WATCH_FLAG_AXP_IRQ, &xHigherPriorityTaskWoken);
    } else
    {
      Serial.println("Sending ISR Data Q_EVENT_AXP_INT in AXP");
      uint8_t data = Q_EVENT_AXP_INT;
      xQueueSendFromISR(g_event_queue_handle, &data, &xHigherPriorityTaskWoken);
    }
    if (xHigherPriorityTaskWoken)
    {
      Serial.println("Higher priority task woken in BMA423");
      portYIELD_FROM_ISR ();
    }
  }, FALLING);
  //ttgo->power->setTimer(1); // Set AXP Timer
  //Check if the RTC clock matches, if not, use compile time
  ttgo->rtc->check();

  //Synchronize time to system time
  ttgo->rtc->syncToSystem();

  /*
      ttgo->button->setClickHandler([]() {
          Serial.println("Button2 Pressed");
      });
  */

  //Set the user button long press to restart
  ttgo->button->setLongClickHandler([]() {
    Serial.println("Pressed Restart Button,Restart now ...");
    delay(1000);
    esp_restart();
  });

  //Setting up the network
  setupNetwork();

  //Execute your own GUI interface
  setupGui();

  //Clear lvgl counter
  lv_disp_trig_activity(NULL);

  //In lvgl we call the button processing regularly
  lv_task_create([](lv_task_t *args) {
    ttgo->button->loop();
  }, 30, 1, nullptr);

  //When the initialization is complete, turn on the backlight
  ttgo->openBL();
}

void loop()
{
  bool  rlst;
  uint8_t data;
  //! Fast response wake-up interrupt
  EventBits_t  bits = xEventGroupGetBits(isr_group);
  if (bits & WATCH_FLAG_SLEEP_EXIT) {
    if (lenergy) {
      lenergy = false;
      rtc_clk_cpu_freq_set(RTC_CPU_FREQ_160M);
    }

    low_energy();

    if (bits & WATCH_FLAG_BMA_IRQ) {
      do {
        rlst =  ttgo->bma->readInterrupt();
      } while (!rlst);
      xEventGroupClearBits(isr_group, WATCH_FLAG_BMA_IRQ);
    }
    if (bits & WATCH_FLAG_AXP_IRQ) {
      ttgo->power->readIRQ();
      ttgo->power->clearIRQ();
      //TODO: Only accept axp power pek key short press
      xEventGroupClearBits(isr_group, WATCH_FLAG_AXP_IRQ);
    }
    xEventGroupClearBits(isr_group, WATCH_FLAG_SLEEP_EXIT);
    xEventGroupClearBits(isr_group, WATCH_FLAG_SLEEP_MODE);
  }
  if ((bits & WATCH_FLAG_SLEEP_MODE)) {
    //! No event processing after entering the information screen
    return;
  }

  //! Normal polling
  if (xQueueReceive(g_event_queue_handle, &data, 5 / portTICK_RATE_MS) == pdPASS) {
    switch (data) {
      case Q_EVENT_BMA_INT:
        do {
          rlst =  ttgo->bma->readInterrupt();
        } while (!rlst);

        //! setp counter
        if (ttgo->bma->isStepCounter()) {
          updateStepCounter(ttgo->bma->getCounter());
        }
        break;
      case Q_EVENT_AXP_INT:
        ttgo->power->readIRQ();
        if (ttgo->power->isVbusPlugInIRQ()) {
          updateBatteryIcon(LV_ICON_CHARGE);
        }
        if (ttgo->power->isVbusRemoveIRQ()) {
          updateBatteryIcon(LV_ICON_CALCULATION);
        }
        if (ttgo->power->isChargingDoneIRQ()) {
          updateBatteryIcon(LV_ICON_CALCULATION);
        }
        if (ttgo->power->isPEKShortPressIRQ()) {
          ttgo->power->clearIRQ();
          low_energy();
          return;
        }
        ttgo->power->clearIRQ();
        break;
      case Q_EVENT_WIFI_SCAN_DONE: {
          int16_t len =  WiFi.scanComplete();
          for (int i = 0; i < len; ++i) {
            wifi_list_add(WiFi.SSID(i).c_str());
          }
          break;
        }
      default:
        break;
    }

  }
  if (pwr_mode != 2) {
    // We don't want to run either item in pwr_mode 2 as the screen is off already
    // and it was only reached via low_energy() in the first place.
    if (lv_disp_get_inactive_time(NULL) < DEFAULT_SCREEN_TIMEOUT) {
      lv_task_handler();
    } else {
      Serial.println("Entering low energy via screen timeout");
      low_energy();
    }
  }

  /*if (pwr_mode >0){
    Serial.printf("Pwr Mode: %u | Millis: %d\n", pwr_mode, millis());
    }*/

  // Timer stuff
  /*  This is muy shonky. I should've used a hardware timer but between
      The PCF8653 Guru'ing, AXP Alarm being for a minute within an hour
      and the ESP32 timers hanging for $reasons, I've gone with something
      simple to get this done. If I ever build a full watch OS, I'm doing
      this differently.
  */
  if (timer_left > 0 && timer_active) {
    time_t now;
    struct tm  info;
    char buf[64];
    char dbuf[64];
    char tbuf[64];
    char sbuf[64];
    time(&now);
    localtime_r(&now, &info);
    if (last_sec != info.tm_sec) {
      timer_left--;
      last_sec = info.tm_sec;
      Serial.printf("Timer: %u\n", timer_left);
    }
    if (mod_mode == 0 && (timer_left % 60 == 0)){
      sprintf(sbuf,"You have %u mihn its left.", timer_left/60, timer_left % 60);
      sam->Say(out, sbuf);
    }
  }

  if (speech_active){
    sam->Say(out, saytext);
    sam->Say(out, ".");
    speech_active = false;
  }

  if (pwr_mode == 2 && timer_left == 0 && timer_active){
    low_energy();
  }

  // mod_mode
  if (mod_mode == 1) {
    Serial.println("Playing mod");
    ttgo->enableLDO3();

  //s0 = new AudioFileSourcePROGMEM( ELYSIUM_MOD, sizeof(ELYSIUM_MOD) );
  //s1 = new AudioFileSourcePROGMEM( Chaos_Engine_k8_mod, sizeof(Chaos_Engine_k8_mod) );
  //s2 = new AudioFileSourcePROGMEM( Project_X_RE_pxloader_mod, sizeof(Project_X_RE_pxloader_mod) );  

         
    switch(song_index){
      case 0:
        file = new AudioFileSourcePROGMEM(ELYSIUM_MOD, sizeof(ELYSIUM_MOD) );
        mod->begin(file, out);
        break;
      case 1:
        file = new AudioFileSourcePROGMEM(Chaos_Engine_k8_mod, sizeof(Chaos_Engine_k8_mod) );
        mod->begin(file, out);
        break;
      case 2: 
        file = new AudioFileSourcePROGMEM(Project_X_RE_pxloader_mod, sizeof(Project_X_RE_pxloader_mod) );  
        mod->begin(file, out);
        break;
      default:
        break;
    }
    mod_mode = 2;
  }
  if (mod_mode == 2) {
    if (mod->isRunning()) {
      if (!mod->loop()) {
        mod->stop();
        mod_mode = 0;
      }
    }
  }
  if (mod_mode == 0) {
    //Serial.println("Stopping mod");
    if (mod->isRunning()) {
      mod->stop();
      delete file;
      //ttgo->disableLD03();
      //ttgo->power->setPowerOutPut(AXP202_LDO3, AXP202_OFF);
    }
  }

  /*if (ticks % 10000){
    Serial.printf("Mod mode: %u\n", mod_mode);
    }*/

}
