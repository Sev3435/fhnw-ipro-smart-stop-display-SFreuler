#include <Arduino.h>
#include <WiFi.h>
#include "net/Provisioner.h"

static const char* AP_SSID = "SmartStop-Setup";
static const char* AP_PASSWORD = "smartstop";   // WPA2 needs >= 8 chars
static const IPAddress AP_IP(192, 168, 4, 1);

void Provisioner::begin() {
    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(AP_IP, AP_IP, IPAddress(255, 255, 255, 0));
    WiFi.softAP(AP_SSID, AP_PASSWORD);
    running = true;
    log_i("AP up: ssid=%s ip=%s", AP_SSID, apIp().c_str());
}

void Provisioner::end() {
    if (!running) return;
    WiFi.softAPdisconnect(true);
    WiFi.mode(WIFI_OFF);
    running = false;
}

String Provisioner::apIp() const {
    return WiFi.softAPIP().toString();
}