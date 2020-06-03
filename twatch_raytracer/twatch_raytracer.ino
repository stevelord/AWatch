
bool hasPsram = true;

#include <TTGO.h>

TTGOClass *ttgo;
#include "tinyraytracer.h" // a modified version of https://github.com/ssloy/tinyraytracer
#include "tiny_jpeg_encoder.h" // a modified version of https://github.com/serge-rgb/TinyJPEG

struct point {
  float initialx;
  float initialy;
  float initialz;
  float x;
  float y;
  float z;
};

struct color {
  float r;
  float g;
  float b;
};

point ivorySphereCoords = { 0, -1.5, -14 };
color ivoryColor =  {0.4, 0.4, 0.3 };

point glassSphereCoorsd = { 0, -1.5, -14 };

void raytrace(uint16_t x, uint16_t y, uint16_t width, uint16_t height, float fov) {
  Material      ivory(1.0, Vec4f(0.6,  0.3, 0.1, 0.0), Vec3f(ivoryColor.r, ivoryColor.g, ivoryColor.b),   50.);
  Material      glass(1.5, Vec4f(0.0,  0.5, 0.1, 0.8), Vec3f(0.6, 0.7, 0.8),  125.);
  //Material red_rubber(1.0, Vec4f(0.9,  0.1, 0.0, 0.0), Vec3f(0.3, 0.1, 0.1),   10.);
  Material     mirror(1.0, Vec4f(0.0, 10.0, 0.8, 0.0), Vec3f(1.0, 1.0, 1.0), 1425.);

  std::vector<Sphere> spheres;
  spheres.push_back(Sphere(Vec3f(ivorySphereCoords.x, ivorySphereCoords.y, ivorySphereCoords.z), 2, ivory));
  spheres.push_back(Sphere(Vec3f(glassSphereCoorsd.x, glassSphereCoorsd.y, glassSphereCoorsd.z), 2, glass));
  //spheres.push_back(Sphere(Vec3f( 1.5, -0.5, -18), 3, red_rubber));
  spheres.push_back(Sphere(Vec3f( 7,    5,   -18), 4,     mirror));

  std::vector<Light>  lights;
  lights.push_back(Light(Vec3f(-20, 20,  20), 1.5));
  lights.push_back(Light(Vec3f( 30, 50, -25), 1.8));
  lights.push_back(Light(Vec3f( 30, 20,  30), 1.7));

  render(x, y, width, height, spheres, lights, fov);
}

void setup() {

  Serial.begin(115200);
  ttgo = TTGOClass::getWatch();
  ttgo->begin();
  ttgo->openBL();  

  if( !psramInit() ) {
    Serial.println("PSRAM FAIL");
    /*
    while(1) {
      ;
    }*/
  } else {
    Serial.println("PSRAM FOUND");
    hasPsram = true;
  }

  ttgo->eTFT->setTextDatum(MC_DATUM);
  ttgo->eTFT->setTextColor(TFT_GREEN, TFT_BLACK);
  ttgo->eTFT->fillScreen(TFT_BLACK);

  while (1) {
      if (ttgo->sdcard_begin()) {
          Serial.println("sd begin pass");
          break;
      }
      Serial.println("sd begin fail,wait 1 sec");
      delay(1000);
  }

  uint8_t cardType = SD.cardType();

  if (cardType == CARD_NONE) {
      Serial.println("No SD card attached");
      while(1);
  }
  Serial.print("SD Card Type: ");
  if (cardType == CARD_MMC) {
      Serial.println("MMC");
  } else if (cardType == CARD_SD) {
      Serial.println("SDSC");
  } else if (cardType == CARD_SDHC) {
      Serial.println("SDHC");
  } else {
      Serial.println("UNKNOWN");
  }
  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  Serial.printf("SD Card Size: %lluMB\n", cardSize);

  if(!SD.exists("/jpg")) {
    SD.mkdir("/jpg");
  }

  tinyRayTracerInit();
  tinyJpegEncoderInit();

}

bool rendered = false;

void loop() {

  uint16_t width = TFT_WIDTH;
  uint16_t height = 216;

  /*if( !hasPsram ) {
    if(width>128)  width  = 128;
    if(height>128) height = 128;
  }*/

  uint16_t x = 0; //(TFT_WIDTH - width) / 2;
  uint16_t y = 24; //(TFT_HEIGHT - height) / 2;

  char * fName = NULL;
  fName = (char*)malloc(32);

  byte looplength = 60;

  if(!rendered) {

    ttgo->eTFT->setCursor(0, 0);
    ttgo->eTFT->println("Rendering while n0x00 licks door knobs.");
    ttgo->eTFT->print("TTGO T-Watch Raytracer v0.1.");
    unsigned long started = millis();

    glassSphereCoorsd.x = glassSphereCoorsd.initialx;
    glassSphereCoorsd.z = glassSphereCoorsd.initialz;
    glassSphereCoorsd.y = glassSphereCoorsd.initialy;

    for(byte framenum=0; framenum<looplength;framenum++) {

      sprintf(fName, "/jpg/out%d.jpg", framenum);
      const char* jpegFileName = fName;
      float myfov = 0.5 + (float)framenum / looplength;

      ivorySphereCoords.x = ivorySphereCoords.initialx + (4*sin( ((float)framenum/looplength)*PI*2 ));
      ivorySphereCoords.z = ivorySphereCoords.initialz + (2*cos( ((float)framenum/looplength)*PI*2 ));
      ivorySphereCoords.y = ivorySphereCoords.initialy + fabs(2.75*cos( ((float)((framenum*2)%looplength)/looplength)*PI*2 ));

      //ivoryColor.r = fabs(.1*sin( ((float)framenum/looplength)*PI*2 )) + .3;
      //ivoryColor.g = ivoryColor.r;
      //ivoryColor.b = ivoryColor.r - 0.1;

      raytrace(x, y, width, height, 0.6);

      if ( !tje_encode_to_file(jpegFileName, width, height, 3 /*3=RGB,4=RGBA*/, rgbBuffer) ) {
        Serial.println("Could not write JPEG\n");
      } else {
        Serial.printf("[%d / %d] Rendering saved jpeg %s with fov %f\n", ESP.getFreeHeap(), ESP.getFreePsram(), jpegFileName, myfov);
        ttgo->eTFT->setCursor(0,8);
        ttgo->eTFT->fillRect(0,8,TFT_WIDTH, 20, 0);

        ttgo->eTFT->printf("Rendered frame %d out of %d", framenum+1, looplength);
        ttgo->eTFT->setCursor(0,16);

        float framelen = ( (millis() - started) / (framenum+1) ) / 1000;
        int remaining = (looplength - framenum) * framelen;

        ttgo->eTFT->printf("Estimated time remaining: %d seconds", remaining);
        //M5.Lcd.drawJpgFile(SD, jpegFileName, x, y, width, height, 0, 0, JPEG_DIV_NONE);
      }
    }
    rendered = true;
    unsigned long ended = (millis() - started)/1000;
    Serial.printf("Rendered animation in %d seconds\n", ended);
    ttgo->eTFT->fillRect(0,0,TFT_WIDTH, 30, 0);

  }

  for(byte framenum=0; framenum<looplength; framenum++) {
    sprintf(fName, "/jpg/out%d.jpg", framenum);
    const char* jpegFileName = fName;
    //M5.Lcd.drawJpgFile(SD, jpegFileName, x, y, width, height, 0, 0, JPEG_DIV_NONE);
  }


}
