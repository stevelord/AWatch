/*
  Sketch to demonstrate using the print class with smooth fonts

  Sketch is writtent for a 240 x 320 display

  Load the font file into SPIFFS first by using the Arduino IDE
  Sketch Data Upload menu option. Font files must be stored in the
  sketch data folder (Ctrl+k to view).
  https://github.com/esp8266/arduino-esp8266fs-plugin
  https://github.com/me-no-dev/arduino-esp32fs-plugin

  New font files in the .vlw format can be created using the Processing
  sketch in the library Tools folder. The Processing sketch can convert
  TrueType fonts in *.ttf or *.otf files.

  Note: SPIFFS does not accept an underscore _ in filenames!

  The library supports 16 bit unicode characters:
  https://en.wikipedia.org/wiki/Unicode_font

  The characters supported are in the in the Basic Multilingal Plane:
  https://en.wikipedia.org/wiki/Plane_(Unicode)#Basic_Multilingual_Plane

  Make sure all the display driver and pin connenctions are correct by
  editting the User_Setup.h file in the TFT_eSPI library folder.

  #########################################################################
  ###### DON'T FORGET TO UPDATE THE User_Setup.h FILE IN THE LIBRARY ######
  #########################################################################
*/

// Font file is stored in SPIFFS
#define FS_NO_GLOBALS
#include <FS.h>

#include <TTGO.h>

TTGOClass *ttgo;

unsigned long drawTime = 0;

void setup(void)
{
    Serial.begin(115200); // Used for messages
    ttgo = TTGOClass::getWatch();
    ttgo->begin();
    ttgo->openBL();
    ttgo->eTFT->setTextFont(2);
    if (!SPIFFS.begin()) {
      Serial.println("SPIFFS initialisation failed!");
      while (1) yield(); // Stay here twiddling thumbs waiting
    }
    Serial.println("\r\nInitialisation done.");

    listFiles(); // Lists the files so you can see what is in the SPIFFS
}

void loop()
{
    String fileName = "Topaza500";
    ttgo->eTFT->fillScreen(TFT_BLUE);
    ttgo->eTFT->setTextColor(TFT_WHITE, TFT_BLUE);
    ttgo->eTFT->setTextWrap(true, true);
    ttgo->eTFT->loadFont(fileName);
    ttgo->eTFT->showFont(2000);
    ttgo->eTFT->setCursor(0,0);
    ttgo->eTFT->println("Hello World!");

    ttgo->eTFT->unloadFont(); // Unload font to recover used RAM

    delay(10000);

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
