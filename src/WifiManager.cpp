#include <Arduino.h>
#include <WiFi.h>
#include "WifiManager.h"
#include "secrets.h"

void WifiManager::init() {
    WiFi.mode(WIFI_STA);
    WiFi.setSleep(false);
    WiFi.setMinSecurity(WIFI_AUTH_WPA2_PSK);
    WiFi.onEvent([](WiFiEvent_t event, WiFiEventInfo_t info) {
        log_w("disconnect reason=%d", info.wifi_sta_disconnected.reason);
    }, WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_DISCONNECTED);
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    lastAttemptMs = millis();
}

void WifiManager::update() {
    bool isConnected = (WiFi.status() == WL_CONNECTED);

    if (isConnected && !wasConnected) {
        log_i("connected, IP: %s", WiFi.localIP().toString().c_str());
        configTime(0, 0, "pool.ntp.org");
        log_i("ntp sync started");
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
