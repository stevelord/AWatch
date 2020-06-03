/*=====================================================================
 * Open Vega+ Emulator. Handheld ESP32 based hardware with 
 * ZX Spectrum emulation
 * 
 * (C) 2019 Alvaro Alea Fernandez
 *
 * This program is free software; redistributable under the terms of 
 * the GNU General Public License Version 2
 * 
 * Based on the Aspectrum emulator Copyright (c) 2000 Santiago Romero Iglesias
 * Use Adafruit's IL9341 and GFX libraries.
 * Compile as ESP32 Wrover Module
 *======================================================================
 */
//#define USE_DUAL_CORE
#include <TTGO.h>
#include "hardware.h"
#include "snaps.h"
#include "spectrum.h"
#include "z80.h"

/* Definimos unos objetos
 *  spectrumZ80 es el procesador en si
 *  mem es la memoria ROM/RAM del ordenador
 *  hwopt es la configuracion de la maquina a emular esto se guarda en los snapshots
 *  emuopt es la configuracion del emulador en si, no se guarda con el snapshot
 */

Z80Regs spectrumZ80;
tipo_mem mem;
tipo_hwopt hwopt;
tipo_emuopt emuopt;
uint8_t *lastpix;
/*FIXME: para una buena orientacion a objetos, mem y hwopts deberian pasarse como puntero a
 *cada funcion que lo necesite, igual que hacemos con spectrumZ80
 */

TTGOClass *watch = nullptr;
 
#ifdef USE_DUAL_CORE
#include "soc/timer_group_struct.h"
#include "soc/timer_group_reg.h"
TaskHandle_t Ula_Task;
#endif 

void show_splash(void){

  //gui_draw_window(270,170, "Version 0.0 alpha");
  watch->eTFT->setCursor(0, 65);
  watch->eTFT->setTextColor(TFT_BLACK);  
  watch->eTFT->setTextSize(3);
  watch->eTFT->println("    OpenVEGA+");
  watch->eTFT->setTextColor(TFT_GREEN);  
  watch->eTFT->setTextSize(2);
  watch->eTFT->println("\n     By Alvaro Alea F.");
  watch->eTFT->setTextSize(1);
  watch->eTFT->println("");
  watch->eTFT->setTextSize(2);
  watch->eTFT->println("          (C) 2019");
  watch->eTFT->setTextSize(1);
  watch->eTFT->setTextColor(TFT_BLUE);  
  watch->eTFT->println("\n\n\n       A Opensource Portable Spectrum Emulator");
}

void setup(void)
{
  Serial.begin(115200);
  Serial.print("OpenVega+ Boot!\n");


  watch->begin();
  watch->openBL();
  Serial.print("Watch initialized\n");
  /*
  // read diagnostics (optional but can help debug problems)
  uint8_t x = watch->eTFT->readcommand8(TFT_RDMODE);
  AS_printf("Display Power Mode: 0x"); AS_print(x, HEX);AS_printf("\n");
  x = watch->eTFT->readcommand8(TFT_RDMADCTL);
  AS_printf("MADCTL Mode: 0x"); AS_print(x, HEX);AS_printf("\n");
  x = watch->eTFT->readcommand8(TFT_RDPIXFMT);
  AS_printf("Pixel Format: 0x"); AS_print(x, HEX);AS_printf("\n");
  x = watch->eTFT->readcommand8(TFT_RDIMGFMT);
  AS_printf("Image Format: 0x"); AS_print(x, HEX);AS_printf("\n");
  x = watch->eTFT->readcommand8(TFT_RDSELFDIAG);
  AS_printf("Self Diagnostic: 0x"); AS_print(x, HEX); AS_printf("\n");
  watch->eTFT->setRotation(3);
  */
  watch->eTFT->fillScreen(TFT_BLACK);
  Serial.print("Black Screen Fill complete\n");

  show_splash();

  Serial.print("Splash Screen complete\n");

  /*lastpix = (uint8_t*) malloc(320*240 * sizeof(uint8_t));
  if(lastpix == NULL)                     
    {
        AS_printf("Error! memory not allocated for screenbuffer.\n");
        delay(10000);
    }



#ifdef USE_DUAL_CORE
  xTaskCreatePinnedToCore(
                    ula_do_ticks,/* Task function. */
                    //"ULA",       /* name of task. */
                    //16384,       /* Stack size of task */
                    //NULL,        /* parameter of the task */
                    //1,           /* priority of the task */
                    //&Ula_Task,   /* Task handle to keep track of created task */
                    //0);          /* pin task to core 0 */
//#endif
  /*
  //FIXME porque 69888??
  Z80Reset (&spectrumZ80, 69888);
  Z80FlagTables ();
  AS_printf("Z80 Initialization completed\n");
  
  init_spectrum(SPECMDL_48K,"/48.rom");
  reset_spectrum(&spectrumZ80);
  Load_SNA(&spectrumZ80,"/manic.sna");
//  Load_SNA(&spectrumZ80,"/t1.sna");
  
  delay (2000);
  AS_printf("Entrando en el loop\n");*/
}

long pend_ula_ticks=0;

void loop (void){ 
  //draw_scanline();
}

const uint8_t SoundTable[4]={0,1,0,1};

void draw_scanline(){
  uint16_t c=0; 
// dividimos el scanline en la parte central, y los bordes y retrazo, para la emulacion del puerto FF  

  pend_ula_ticks+=256;
  c=Z80Run (&spectrumZ80, 128) ;
  while (pend_ula_ticks>0) {
#ifdef USE_DUAL_CORE
   delay(1); 
#else
   pend_ula_ticks--;
   ula_tick();
#endif
    }
    
  pend_ula_ticks+=192;
  c=Z80Run (&spectrumZ80, 96) ;
  while (pend_ula_ticks>0) {
#ifdef USE_DUAL_CORE
   delay(1); 
#else
   pend_ula_ticks--;
   ula_tick();
#endif
    }

//  AS_printf("PC=%i\n",c);
  // Sound on each scanline means 15.6Khz, not bad...
  //dac_output_voltage(DAC_CHANNEL_1, SoundTable[hwopt.SoundBits]);
}

#ifdef USE_DUAL_CORE    
void ula_do_ticks(void * pvParameters ){
  for(;;){ 
    if (pend_ula_ticks>0) {
      pend_ula_ticks--;
      ula_tick();
    }
  TIMERG0.wdt_wprotect=TIMG_WDT_WKEY_VALUE;
  TIMERG0.wdt_feed=1;
  TIMERG0.wdt_wprotect=0;
  }
}
#endif  


void ula_tick(void){

  const int specpal565[16]={
    0x0000, 0x001B, 0xB800, 0xB817,0x05E0,0x05F7,0xBDE0,0xC618, 0x0000, 0x001F,0xF800,0xF81F,0x07E0,0x07FF,0xFFE0,0xFFFF}; 

  uint8_t color;
  uint8_t pixel;
  int col,fil,scan,inkOpap;
  static int px=31; // emulator hardware pixel to be paint, x coordinate
  static int py=24; // emulator hardware pixel to be paint, y coordinate
  static int ch=447; // 0-447 is the horizontal bean position
  static int cv=312; // 0-312 is the vertical bean position
  static int cf=0;  // 0-32 counter for flash
//  static int cf2=0;
//  static int cf3=0;
  static uint8_t attr; //last attrib memory read



 ch++;
 if (ch>=448) ch=0;
 if (ch==416) px=0;
 if ((ch<=288) or (ch>416)) px++;

 if (ch==0) { 
  cv++;
  if (cv>=313) {
    cv=0;
    leebotones();
  }
  if (cv==288) { 
    py=0;
    cf++;  if (cf>=32) cf=0;
  //    leebotones();
  //  cf2++; if (cf2>=50) cf2=0;
  //  cf3++; if (cf3>=2) cf3=0;
  }
  if ((cv<218) or (cv>288)) py++;
 }
 if ((ch==0) and (cv==248)) spectrumZ80.petint=1;


// Read the first ATTR of each col in advance. FIXME
/*
 if (cv=312 and ch==447) {
  attr=z80_peek(0x5800); 
 }
 if (cv<192 and ch==447) {
  fil=cv>>3;
  attr=z80_peek(0x5800 + 32*cv>>3  +0); 
 }
*/
 if ((cv>=192) or (ch>=256)) {
  hwopt.portFF = 0xFF;
  color = hwopt.BorderColor;
 } else {
  pixel=7-(ch & B111);
  col=(ch & B11111000)>>3;
  fil=cv>>3;
  scan = (cv & B11000000) + ((cv & B111)<<3) + ((cv & B111000)>>3) ;  
  //FIXME: Two acces to mem in same tick, really ATTR is Access a pixel early
  //       so a reading must be done when cv<192 and ch=447 for 0x5800 + 32*fil
  //       later attr for col+1 on ch & B111 == 0b111
  //       deberia ir en un if separado para no leer 33 valores, el ultimo no hace falta asi que ch<250
  if (( ch & B111 ) == 0b000 ) {
    attr=readvmem(0x1800 + 32*fil  +col,hwopt.videopage);
  }
  if (( ch & B111 ) == 0b000 ) {
    hwopt.portFF=readvmem(0x0000 + 32*scan +col,hwopt.videopage);
  }
  inkOpap=(hwopt.portFF>>pixel) & 1;
  // FLASH
  if  ( (cf>=16) && ((attr & B10000000)!=0) ) inkOpap=!inkOpap;
  // INK or PAPER
  if (inkOpap!=0) {
   color=attr & B000111;
  } else {
   color=(attr & B111000) >>3;
  }
  // BRIGHT
  if  ((attr & B01000000)!=0) {
   color=color+8;
  }
 }
 // Paint the real screen
 if ((px<320) and (py<240)) { // and (cf3==0)) {
  if (  *(lastpix+px+320*py) != color ){
    watch->eTFT->drawPixel(px,py,specpal565[color]);
    *(lastpix+px+320*py)=color;
  } 
 }
/*
 // Frame indication
 if ((px==0) and (py==16)) {
  watch->eTFT->fillRect(306,0,14,10,watch->eTFT->color565(0,0,0));
  watch->eTFT->setTextSize(1);
  watch->eTFT->setCursor(307, 1);
  watch->eTFT->setTextColor(TFT_WHITE);  
  watch->eTFT->print(cf2);   
 }
*/
}
