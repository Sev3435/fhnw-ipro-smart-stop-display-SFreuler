#include "project.h"

void setup() {
    Serial.begin(115200);
    display_init();
    WifiManager_init();
}

void loop() {
    display_update();
    WifiManager_update();
}