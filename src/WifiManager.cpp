#include <Arduino.h>
#include <WiFi.h>
#include "WifiManager.h"
#include "secrets.h"
#include <ESPmDNS.h>
#include "lwip/dns.h"

void WifiManager::init() {
    WiFi.mode(WIFI_STA);
    WiFi.setAutoReconnect(false);
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
        log_i("gw=%s dns=%s", WiFi.gatewayIP().toString().c_str(), WiFi.dnsIP().toString().c_str());
        configTime(0, 0, "pool.ntp.org");
        log_i("ntp sync started");
         if (MDNS.begin("smartstop")) {
             MDNS.addService("http", "tcp", 80);
             log_i("mDNS: http://smartstop.local");
         } else {
             log_e("mDNS start failed");
        }
    }
    if (!isConnected && wasConnected) {
        log_w("connection lost");
        lastAttemptMs = millis();
    }

    // plain reconnect doesn't always recover, so tear the whole thing down and start over
    if (!isConnected && millis() - lastAttemptMs >= RETRY_INTERVAL_MS) {
        log_d("retry: full re-begin");
        WiFi.disconnect(true, true);
        WiFi.mode(WIFI_OFF);
        WiFi.mode(WIFI_STA);
        WiFi.begin(WIFI_SSID, WIFI_PASS);
        lastAttemptMs = millis();
    }

    wasConnected = isConnected;
}
