#include <Arduino.h>
#include "net/WifiService.h"
#include "net/WifiRoutes.h"
#include "hardware/Display.h"

void WifiService::attachRoutes(AsyncWebServer& server) {
    WifiRoutes::attach(server, &store);
}

void WifiService::begin(Display* display) {
    this->display = display;
    store.load();
    if (store.hasCredentials()) {
        wifiManager.begin(&store);
    } else {
        log_w("no credentials stored");
        enterProvisioning();
    }
}

void WifiService::update() {
    if (WifiRoutes::restartPending()) {
        delay(500);          // let the response flush
        ESP.restart();
    }

    if (mode == Mode::Provisioning) return;

    if (wifiManager.update() == WifiManager::Status::GaveUp) {
        log_w("could not connect, falling back to setup AP");
        wifiManager.end();
        enterProvisioning();
    }
}

void WifiService::enterProvisioning() {
    mode = Mode::Provisioning;
    provisioner.begin();
    display->showTitle("WiFi setup:");
    display->showMessage(provisioner.apIp());
}