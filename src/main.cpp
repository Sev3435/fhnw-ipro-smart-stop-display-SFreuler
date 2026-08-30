#include <Arduino.h>

#include "Config.h"
#include "hardware/Display.h"
#include "hardware/LightSensor.h"
#include "net/ConfigRoutes.h"
#include "net/WebServer.h"
#include "net/WifiService.h"
#include "transport/TimeService.h"
#include "transport/TransportClient.h"

Display display;
Config config;
WifiService wifi;
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
        wifi.attachRoutes(webServer.http());
        webServer.start();
    }

    wifi.begin(&display);
    transport.begin(&config, &display, &timeService);
}

void loop() {
    wifi.update();
    if (wifi.isProvisioning()) return;

    timeService.update();
    transport.update();
    if (lightSensor.update()) {
        display.setBrightness(lightSensor.brightness());
    }
}