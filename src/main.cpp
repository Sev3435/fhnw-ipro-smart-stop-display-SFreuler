#include "project.h"
#include <Arduino.h>

void setup() {
    Serial.begin(115200);
#if CORE_DEBUG_LEVEL > 0
    while (!Serial && millis() < 3000) {}
#endif
    log_i("boot");
    display_init();
    WifiManager_init();
}

void loop() {
    display_update();
    WifiManager_update();
}