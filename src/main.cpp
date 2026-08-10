#include "Display.h"
#include "WifiManager.h"
#include "Config.h"
#include <Arduino.h>

#include "TransportClient.h"

Display display;
WifiManager wifiManager;
Config config;
TransportClient transport;

void setup() {
    Serial.begin(115200);
#if CORE_DEBUG_LEVEL > 0
    while (!Serial && millis() < 3000) {}
#endif
    log_i("boot");
    config.load();
    display.init();
    wifiManager.init();
    transport.begin(&config);
}

void loop() {
    display.update();
    wifiManager.update();
    transport.update();
}