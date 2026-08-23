#include <Arduino.h>

#include "TransportClient.h"
#include "Display.h"
#include "WifiManager.h"
#include "Config.h"
#include "LightSensor.h"
#include "WebServer.h"

Display display;
WifiManager wifiManager;
Config config;
TransportClient transport;
LightSensor lightSensor;
WebServer webServer;

void setup() {
    Serial.begin(115200);
#if CORE_DEBUG_LEVEL > 0
    while (!Serial && millis() < 3000) {}
#endif
    log_i("boot");
    config.load();
    display.init();
    wifiManager.init();
    webServer.begin(&config);
    transport.begin(&config, &display);
}

void loop() {
    wifiManager.update();
    transport.update();
    if (lightSensor.update()) {
        display.setBrightness(lightSensor.brightness());
    }
}