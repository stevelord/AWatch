// This sketch draws BMP images pulled from SPIFFS onto the TFT. It is an
// an example from this library: https://github.com/Bodmer/TFT_eSPI

// Images in SPIFFS must be put in the root folder (top level) to be found
// Use the SPIFFS library example to verify SPIFFS works!

// The example image used to test this sketch can be found in the sketch
// Data folder, press Ctrl+K to see this folder. Use the IDE "Tools" menu
// option to upload the sketches data folder to the SPIFFS

// This sketch has been tested on the ESP32 and ESP8266

//----------------------------------------------------------------------------------------------------

//====================================================================================
//                                  Libraries
//====================================================================================
// Call up the SPIFFS FLASH filing system this is part of the ESP Core
#define FS_NO_GLOBALS
#include <FS.h>

/*#ifdef ESP32
  #include "SPIFFS.h"  // For ESP32 only
#endif*/

#include <TTGO.h>

// Invoke TFT library
TTGOClass *ttgo;

//====================================================================================
//                                    Setup
//====================================================================================
void setup()
{
  String fileName = "Topaza500";
  Serial.begin(115200);
  ttgo = TTGOClass::getWatch();
  ttgo->begin();
  ttgo->openBL();

  if (!SPIFFS.begin()) {
    Serial.println("SPIFFS initialisation failed!");
    while (1) yield(); // Stay here twiddling thumbs waiting
  }
  Serial.println("\r\nSPIFFS initialised.");
  listFiles(); // Lists the files so you can see what is in the SPIFFS

  ttgo->eTFT->fillScreen(TFT_WHITE);
  ttgo->eTFT->setTextColor(TFT_BLUE, TFT_WHITE);
  ttgo->eTFT->setTextWrap(true, true);
  ttgo->eTFT->loadFont(fileName);
  
  drawBmp("/ks.bmp", 0,0);
}

//====================================================================================
//                                    Loop
//====================================================================================
void loop()
{

  delay(1000);
}

// -------------------------------------------------------------------------
// Guru Meditation error display
// -------------------------------------------------------------------------
void dbgerr(String err){
    int tx = (err.length()/2)*8;
    ttgo->eTFT->fillScreen(TFT_BLACK);
    ttgo->eTFT->setTextColor(TFT_RED, TFT_BLACK);
    ttgo->eTFT->fillRect(0, 0, 240, 42, TFT_BLACK);
    ttgo->eTFT->setCursor(56,8);
    ttgo->eTFT->print("Software Failure");
    ttgo->eTFT->setCursor(120-tx,24);
    ttgo->eTFT->print(err);
    while(1){
      ttgo->eTFT->fillRect(0, 0, 240, 4, TFT_RED);
      ttgo->eTFT->fillRect(236, 0, 4, 42, TFT_RED);
      ttgo->eTFT->fillRect(0, 0, 4, 42, TFT_RED);
      ttgo->eTFT->fillRect(0, 42, 240, 4, TFT_RED);
      delay(1000);
      ttgo->eTFT->fillRect(0, 0, 240, 4, TFT_BLACK);
      ttgo->eTFT->fillRect(236, 0, 4, 42, TFT_BLACK);
      ttgo->eTFT->fillRect(0, 0, 4, 42, TFT_BLACK);
      ttgo->eTFT->fillRect(0, 42, 240, 4, TFT_BLACK);
      delay(1000);
    }
}

// -------------------------------------------------------------------------
// List files in ESP8266 or ESP32 SPIFFS memory
// -------------------------------------------------------------------------
void listFiles(void) {
  Serial.println();
  Serial.println("SPIFFS files found:");

#ifdef ESP32
  listDir(SPIFFS, "/", true);
#else
  fs::Dir dir = SPIFFS.openDir("/"); // Root directory
  String  line = "=====================================";

  Serial.println(line);
  Serial.println("  File name               Size");
  Serial.println(line);

  while (dir.next()) {
    String fileName = dir.fileName();
    Serial.print(fileName);
    int spaces = 25 - fileName.length(); // Tabulate nicely
    if (spaces < 0) spaces = 1;
    while (spaces--) Serial.print(" ");
    fs::File f = dir.openFile("r");
    Serial.print(f.size()); Serial.println(" bytes");
    yield();
  }

  Serial.println(line);
#endif
  Serial.println();
  delay(1000);
}

#ifdef ESP32
void listDir(fs::FS &fs, const char * dirname, uint8_t levels) {
  Serial.printf("Listing directory: %s\n", dirname);

  fs::File root = fs.open(dirname);
  if (!root) {
    Serial.println("Failed to open directory");
    return;
  }
  if (!root.isDirectory()) {
    Serial.println("Not a directory");
    return;
  }

  fs::File file = root.openNextFile();
  while (file) {

    if (file.isDirectory()) {
      Serial.print("DIR : ");
      String fileName = file.name();
      Serial.print(fileName);
      if (levels) {
        listDir(fs, file.name(), levels - 1);
      }
    } else {
      String fileName = file.name();
      Serial.print("  " + fileName);
      int spaces = 32 - fileName.length(); // Tabulate nicely
      if (spaces < 1) spaces = 1;
      while (spaces--) Serial.print(" ");
      String fileSize = (String) file.size();
      spaces = 8 - fileSize.length(); // Tabulate nicely
      if (spaces < 1) spaces = 1;
      while (spaces--) Serial.print(" ");
      Serial.println(fileSize + " bytes");
    }

    file = root.openNextFile();
  }
}
#endif
// -------------------------------------------------------------------------
//====================================================================================
