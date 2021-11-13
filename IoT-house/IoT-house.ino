#include "settings.h"
#define DEBUG 1
void setup() {
    pinMode(button_up, INPUT_PULLUP);
    pinMode(button_confirm, INPUT_PULLUP);
    pinMode(button_down, INPUT_PULLUP);
    pinMode(READY, INPUT);
    Serial.begin(1000000);
    Serial.setDebugOutput(true);
    Serial.println("--------------------------------");

    //Wire.begin(D1, D2, I2C_MASTER);
    EEPROM.begin(EEPROM_length);
    inputString.reserve(200);
    display.init();
    display.setFont(ArialMT_Plain_10);
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    loadCheckpoints();
    eepromPar(0);
    history_interface[0] = menuInter;
}

void loop() {
    if (ota_initialised) {
        ArduinoOTA.handle();
    }

  interfaceSelector();

#ifdef DEBUG
  serialEvent();
  if (stringComplete) {
    stringComplete = false;
    loadSerialCommands(inputString);
    executeSerialCommands();
  }
#endif

  if (!digitalRead(button_up) && !digitalRead(button_confirm) && !digitalRead(button_down)) {
    demoSectors();
  }
}
