#include "Display.h"
#include "WifiManager.h"
#include <Arduino.h>

Display display;
WifiManager wifiManager;

void setup() {
    Serial.begin(115200);
#if CORE_DEBUG_LEVEL > 0
    while (!Serial && millis() < 3000) {}
#endif
    log_i("boot");
    display.init();
    wifiManager.init();
}

void loop() {
    display.update();
    wifiManager.update();
}