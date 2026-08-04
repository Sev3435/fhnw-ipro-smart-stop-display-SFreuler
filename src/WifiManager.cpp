#include <Arduino.h>
#include <WiFi.h>
#include "project.h"
#include "secrets.h"

static const uint32_t RETRY_INTERVAL_MS = 30000;
static uint32_t lastAttemptMs = 0;
static bool wasConnected = false;

void WifiManager_init() {
    WiFi.mode(WIFI_STA);
    WiFi.setSleep(false);
    WiFi.setMinSecurity(WIFI_AUTH_WPA2_PSK);
    WiFi.onEvent([](WiFiEvent_t event, WiFiEventInfo_t info) {
        log_w("disconnect reason=%d", info.wifi_sta_disconnected.reason);
    }, WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_DISCONNECTED);
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    lastAttemptMs = millis();
}

void WifiManager_update() {
    bool isConnected = (WiFi.status() == WL_CONNECTED);

    if (isConnected && !wasConnected) {
        log_i("connected, IP: %s", WiFi.localIP().toString().c_str());
    }
    if (!isConnected && wasConnected) {
        log_w("connection lost");
        lastAttemptMs = millis();
    }

    if (!isConnected && millis() - lastAttemptMs >= RETRY_INTERVAL_MS) {
        log_d("retry nudge");
        WiFi.reconnect();
        lastAttemptMs = millis();
    }

    wasConnected = isConnected;
}
