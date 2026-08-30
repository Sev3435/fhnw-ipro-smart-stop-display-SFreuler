#include <Arduino.h>

#include "Config.h"
#include "hardware/Display.h"
#include "hardware/LightSensor.h"
#include "net/WebServer.h"
#include "net/WifiManager.h"
#include "transport/TimeService.h"
#include "transport/TransportClient.h"
#include "net/ConfigRoutes.h"
#include "net/WifiStore.h"
#include "net/Provisioner.h"

Display display;
WifiManager wifiManager;
Config config;
TimeService timeService;
TransportClient transport;
LightSensor lightSensor;
WebServer webServer;
WifiStore wifiStore;
Provisioner provisioner;

enum class NetworkMode { Provisioning, Normal };
static NetworkMode mode = NetworkMode::Normal;


static void enterProvisioning() {
    mode = NetworkMode::Provisioning;
    provisioner.begin();
    display.showTitle("WiFi setup:");
    display.showMessage(provisioner.apIp());
}

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
    if (wifiStore.hasCredentials()) {
        wifiManager.begin(&wifiStore);
        transport.begin(&config, &display, &timeService);
    } else {
        log_w("no credentials stored");
        enterProvisioning();
    }
    wifiManager.begin(&wifiStore);
    transport.begin(&config, &display, &timeService);
}

void loop() {

    if (mode == NetworkMode::Provisioning) return;

    if (wifiManager.update() == WifiManager::Status::GaveUp) {
        log_w("could not connect, falling back to setup AP");
        wifiManager.end();
        enterProvisioning();
        return;
    }
    wifiManager.update();
    timeService.update();
    transport.update();
    if (lightSensor.update()) {
        display.setBrightness(lightSensor.brightness());
    }
}
