#include <Arduino.h>

#include "Config.h"
#include "hardware/Display.h"
#include "hardware/LightSensor.h"
#include "net/WebServer.h"
#include "net/WifiManager.h"
#include "transport/TimeService.h"
#include "transport/TransportClient.h"
#include "net/ConfigRoutes.h"
#include "secrets.h"
#include "net/WifiStore.h"

Display display;
WifiManager wifiManager;
Config config;
TimeService timeService;
TransportClient transport;
LightSensor lightSensor;
WebServer webServer;
WifiStore wifiStore;

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
    wifiStore.load();
    if (!wifiStore.hasCredentials()) {      // scaffolding, removed next commit
        wifiStore.ssid = WIFI_SSID;
        wifiStore.pass = WIFI_PASS;
        wifiStore.save();
    }
    wifiManager.begin(&wifiStore);
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
