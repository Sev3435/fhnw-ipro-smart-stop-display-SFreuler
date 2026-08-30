#include <Arduino.h>

#include "Config.h"
#include "hardware/Display.h"
#include "hardware/LightSensor.h"
#include "net/WebServer.h"
#include "net/WifiManager.h"
#include "transport/TimeService.h"
#include "transport/TransportClient.h"
#include "net/ConfigRoutes.h"

Display display;
WifiManager wifiManager;
Config config;
TimeService timeService;
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
    if (webServer.mount()) {
        ConfigRoutes::attach(webServer.http(), &config);
        webServer.start();
    }
    webServer.begin(&config);
    transport.begin(&config, &display, &timeService);
}

void loop() {
    wifiManager.update();
    timeService.update();
    transport.update();
    if (lightSensor.update()) {
        display.setBrightness(lightSensor.brightness());
    }
}
