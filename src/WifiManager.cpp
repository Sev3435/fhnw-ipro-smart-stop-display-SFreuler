#include <Arduino.h>
#include <WiFi.h>
#include "project.h"
#include "secrets.h"

static const uint32_t RETRY_INTERVAL_MS = 5000;
static uint32_t lastAttemptMs = 0;
static bool wasConnected = false;

void WifiManager_init() {
    WiFi.mode(WIFI_STA);
    WiFi.setMinSecurity(WIFI_AUTH_WPA2_PSK);
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    lastAttemptMs = millis();
}

void WifiManager_update() {
    bool isConnected = (WiFi.status() == WL_CONNECTED);

    if (isConnected && !wasConnected) {
        Serial.print("WiFi connected, IP: ");
        Serial.println(WiFi.localIP());
    }
    if (!isConnected && wasConnected) {
        Serial.println("WiFi lost");
        lastAttemptMs = millis();
    }

    if (!isConnected && millis() - lastAttemptMs >= RETRY_INTERVAL_MS) {
        WiFi.disconnect();
        WiFi.begin(WIFI_SSID, WIFI_PASS);
        lastAttemptMs = millis();
    }

    wasConnected = isConnected;
}
